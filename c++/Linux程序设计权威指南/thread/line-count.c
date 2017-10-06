#include <stdio.h>             /* ��׼ I/O ����          */
#include <pthread.h>           /* pthread ���������ݽṹ */

#define DATA_FILE "very_large_data_file"

/* �����ȫ�� mutex����ֵ��ʼ���� */
pthread_mutex_t action_mutex = PTHREAD_MUTEX_INITIALIZER;

/* �����ȫ��������������ֵ��ʼ���� */
pthread_cond_t  action_cond   = PTHREAD_COND_INITIALIZER;

/* �û��Ƿ���;ȡ�������ı�־ */
int cancel_operation = 0;

/*
 * restore_coocked_mode - �ָ�ͨ������Ļģʽ
 * �㷨: ʹ�� stty ����ָ�ͨ������Ļģʽ�����û������̵߳�������
 */

void
restore_coocked_mode(void* dummy)
{
    system("stty -raw echo");
}

/*
 * read_user_input - �ڳ��Ĳ����ڼ��ȡ�û�����
 * �㷨��������ĻΪ raw ģʽ�������ԣ�����һ������ѭ����ȡ�û����롣
 *            ����û����� e���������������źŲ���ֹ�߳�
 */
void*
read_user_input(void* data)
{
    int c;

    /* �Ǽ������� */
    pthread_cleanup_push(restore_coocked_mode, NULL);

    /* ѡ����������ȡ��ģʽ�����������ڶ�ȡ��������ʱҲ���Ա���ֹ */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    /* ������ĻΪ raw ģʽ */
    system("stty raw -echo");

    /* ��һ������ѭ����ȡ�û����롣               */
    /* ����û����� e���������������źŲ���ֹ�߳� */
    while ((c = getchar()) != EOF) {
	if (c == 'e') {
	    /* �û���ȡ������ */
	    cancel_operation = 1;
	    /* ���ߴ������Ҫ�˳��� */
	    pthread_cond_signal(&action_cond);
	    pthread_exit(NULL);
	}
    }

    /* ������������ͬʱִ�����Իָ�������Ļģʽ */
    pthread_cleanup_pop(1);
}

/*
 * file_line_count - ����ָ���ļ�������
 * �㷨���������ļ���һ���ַ�һ���ַ��ض������㻻�з�����Ŀ
 */
void*
file_line_count(void* data)
{
    char* data_file = (char*)data;
    FILE* f = fopen(data_file, "r");
    int wc = 0;
    int c;

    if (!f) {
	perror("fopen");
	exit(1);
    }

    /* ѡ����������ȡ��ģʽ�����������ڶ�ȡ��������ʱҲ���Ա���ֹ */
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    while ((c = getc(f)) != EOF) {
	if (c == '\n')
	    wc++;
    }

    fclose(f);

    /* ���ߴ������Ҫ�˳��� */
    pthread_cond_signal(&action_cond);

    return (void*)wc;
}

/* ���߳� */
int
main(int argc, char* argv[])
{
    pthread_t thread_line_count; /* ���������߳�           */
    pthread_t thread_user_input; /* �û������߳�       */
    void* line_count;		 /* ���������̵߳ķ������� */

    printf("Checking file size (press 'e' to cancel operation)...");
    fflush(stdout);

    /* �������������߳� */
    pthread_create(&thread_line_count,
		   NULL,
		   file_line_count,
		   (void*)DATA_FILE);
    /* �����û������߳� */
    pthread_create(&thread_user_input,
		   NULL,
		   read_user_input,
		   (void*)DATA_FILE);

    /* ���� mutex���غ�����������ֱ������һ���߳���ɲ������ź� */
    pthread_mutex_lock(&action_mutex);
    pthread_cond_wait(&action_cond, &action_mutex);
    pthread_mutex_unlock(&action_mutex);

    /* �����յ��ź����ĸ��̷߳����� */
    if (cancel_operation) {
	/* �����û������߳��Ա�֤�������Ǵ�ӡ֮ǰ�ָ���Ļģʽ */
        pthread_join(thread_user_input, NULL);
	printf("operation canceled\n");
	fflush(stdout);
        /* ȡ�����������߳� */
        pthread_cancel(thread_line_count);
    }
    else {
        /* ������������̣߳��Եõ����� */
        pthread_join(thread_line_count, &line_count);

        /* ȡ���������û������߳��Ա�֤�������Ǵ�ӡ֮ǰ�ָ���Ļģʽ */
        pthread_cancel(thread_user_input);
        pthread_join(thread_user_input, NULL);

	/* ��ӡ��� */
        printf("'%d' lines.\n", (int)line_count);
    }

    return 0;
}
