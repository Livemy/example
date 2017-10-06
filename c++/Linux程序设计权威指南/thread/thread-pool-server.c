#include <stdio.h>       /* ��׼ I/O ����                     */
#include <pthread.h>     /* pthread ���������ݽṹ            */
#include <stdlib.h>      /* rand() and srand() ����           */

/* ����������߳��� */
#define NUM_HANDLER_THREADS 3

/* �����ȫ�� mutex����ֵ��ʼ���� */
/* ע������ʹ��һ���ݹ� mutex����Ϊһ�����ܻ��������������� */
pthread_mutex_t request_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

/* �����ȫ��������������ֵ��ʼ���� */
pthread_cond_t  got_request   = PTHREAD_COND_INITIALIZER;

int num_requests = 0;	/* �����������������ʼΪ 0 */

/* ��������ĸ�ʽ */
struct request {
    int number;		    /* ����ı�� */
    struct request* next;   /* ָ����һ�������ָ�룬NULL ��ʾû����һ�� */
};

struct request* requests = NULL;     /* ��������ͷ */
struct request* last_request = NULL; /* ָ�����һ�������ָ�� */

/*
 * add_request(): ��������������һ������
 * �㷨: ����һ������ṹ����ӵ������У����Ѵ�������������� 1
 */
void
add_request(int request_num,
	    pthread_mutex_t* p_mutex,
	    pthread_cond_t*  p_cond_var)
{
    int rc;	                    /* pthread �����ķ���ֵ */
    struct request* a_request;      /* ָ������ӵ�����     */

    /* �����µ�����ṹ */
    a_request = (struct request*)malloc(sizeof(struct request));
    if (!a_request) {
	fprintf(stderr, "add_request: out of memory\n");
	exit(1);
    }
    a_request->number = request_num;
    a_request->next = NULL;

    /* ���� mutex���Ա�֤�����Է������� */
    rc = pthread_mutex_lock(p_mutex);

    /* ����������ӵ�����β������Ҫ���������ָ�� */
    if (num_requests == 0) {
	requests = a_request;
	last_request = a_request;
    }
    else {
	last_request->next = a_request;
	last_request = a_request;
    }

    /* �ѵȴ������������� 1 */
    num_requests++;

    /* ���� mutex */
    rc = pthread_mutex_unlock(p_mutex);

    /* �������������źţ���ʾ��һ���µ������д����� */
    rc = pthread_cond_signal(p_cond_var);
}

/*
 * get_request(): ȡ�������е�һ������Ȼ���������ɾ����
 */
struct request*
get_request(pthread_mutex_t* p_mutex)
{
    int rc;	                    /* pthread �����ķ���ֵ  */
    struct request* a_request;      /* ����ָ��              */

    /* ���� mutex���Ա�֤�����Է������� */
    rc = pthread_mutex_lock(p_mutex);

    if (num_requests > 0) {
	a_request = requests;
	requests = a_request->next;
	if (requests == NULL) {
	    last_request = NULL;
	}
        /* �ѵȴ������������� 1 */
	num_requests--;
    }
    else {
	a_request = NULL;
    }

    /* ���� mutex */
    rc = pthread_mutex_unlock(p_mutex);

    /* ������߷���������� */
    return a_request;
}

/*
 * handle_request(): ����һ����
 * �㷨: ��ӡһ����Ϣ����ʾָ�������ѱ�ָ���̴߳���
 */
void
handle_request(struct request* a_request, int thread_id)
{
    struct timespec delay;			 /* �ӳ�ʱ�� */
    if (a_request) {
	printf("Thread '%d' handled request '%d'\n",
	       thread_id, a_request->number);
	fflush(stdout);
    }
}

/*
 * handle_requests_loop(): �������������ѭ��
 * �㷨�����������Ҫ����ȡ��һ������Ȼ���غ�ָ�������������յ��źź�
 *       ���¿�ʼѭ�������Ѵ�������������� 1��
 */
void*
handle_requests_loop(void* data)
{
    int rc;	                    /* pthread �����ķ���ֵ  */
    struct request* a_request;      /* ����ָ��              */
    int thread_id = *((int*)data);  /* �߳����              */

    /* ���� mutex���Ա�֤�����Է������� */
    rc = pthread_mutex_lock(&request_mutex);

    /* ����ѭ�� ... */
    while (1) {
	if (num_requests > 0) {
	    a_request = get_request(&request_mutex);
	    if (a_request) {
		handle_request(a_request, thread_id);
		free(a_request);
	    }
	}
	else {
            /* �ȴ�����ִ���������غ򡪡������������� */
	    rc = pthread_cond_wait(&got_request, &request_mutex);
	}
    }
}

/* ���߳� */
int
main(int argc, char* argv[])
{
    int        i;                                /* ѭ������ */
    int        thr_num[NUM_HANDLER_THREADS];      /* �߳���� */
    pthread_t  p_threads[NUM_HANDLER_THREADS];   /* �߳̽ṹ */
    struct timespec delay;			 /* �ӳ�ʱ�� */

    /* �����������߳� */
    for (i=0; i<NUM_HANDLER_THREADS; i++) {
	thr_num[i] = i;
	pthread_create(&p_threads[i], NULL, handle_requests_loop, (void*)&thr_num[i]);
    }

    /* ѭ���������� */
    for (i=0; i<600; i++) {
	add_request(i, &request_mutex, &got_request);
	/* ��ͣһ�ᣬ���������߳����в�����ĳЩ���� */
	if (rand() > 3*(RAND_MAX/4)) { /* ��Ҫ 25% ��ʱ�� */
	    delay.tv_sec = 0;
	    delay.tv_nsec = 10;
	    nanosleep(&delay, NULL);
	}
    }
    /* �ȴ���ֱ��û��ʣ���д���������� */
    sleep(5);

    printf("Glory,  we are done.\n");
    
    return 0;
}
