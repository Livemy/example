#include <stdio.h>       /* �����׼�� I/O ����         */
#include <pthread.h>     /* ���� pthread ���������ݽṹ */

/* ������ȫ�ֵ� mutex���ø�ֵ�ķ�������ʼ���� */
pthread_mutex_t a_mutex = PTHREAD_MUTEX_INITIALIZER;

/* ��Ź�Ա��Ϣ�Ľṹ */
struct employee {
    int number;
    int id;
    char first_name[20];
    char last_name[30];
    char department[30];
    int room_number;
};

/* ȫ�ֱ�����2 λ��Ա�����ݣ��ֱ���Ϊ 1 �� 2 */
struct employee employees[] = {
    { 1, 12345678, "danny", "cohen", "Accounting", 101},
    { 2, 87654321, "moshe", "levy", "Programmers", 202}
};

/* ȫ�ֱ��������չ�Ա */
struct employee employee_of_the_day;

/* ��һ����Ա��Ϣ�ṹ�����ݿ�������һ����Ա��Ϣ�ṹ�� */
void
copy_employee(struct employee* from, struct employee* to)
{
    int rc;	/* ���� mutex ����/�������̵Ľ�� */

    /* ���� mutex���Ա�֤�� from �� to �������Է��� */
    rc = pthread_mutex_lock(&a_mutex);

    /* �������� */
    to->number = from->number;
    to->id = from->id;
    strcpy(to->first_name, from->first_name);
    strcpy(to->last_name, from->last_name);
    strcpy(to->department, from->department);
    to->room_number = from->room_number;

    /* ���� mutex */
    rc = pthread_mutex_unlock(&a_mutex);
}

/* ���ñ��չ�Ա�ĺ��� */
void*
do_loop(void* data)
{
    int my_num = *((int*)data);   /* �̵߳Ĺ�Ա��� */

    while (1) {
        /* ���ñ��չ�ԱΪ��� my_num �Ĺ�Ա */
	copy_employee(&employees[my_num-1], &employee_of_the_day);
    }
}

/* �����򣬻����߳� */
int
main(int argc, char* argv[])
{
    int        i;                      /* ѭ��������           */
    int        ret1;
    int        ret2;
    pthread_t  p_thread1;              /* ��һ���߳̽ṹ       */
    pthread_t  p_thread2;              /* �ڶ����߳̽ṹ       */
    int        num1      = 1;          /* ��һ���̵߳Ĺ�Ա��� */
    int        num2      = 2;          /* �ڶ����̵߳Ĺ�Ա��� */
    struct employee eotd;              /* ���չ�Ա�ı��ؿ���   */
    struct employee* worker;           /* ָ�����ڼ��Ĺ�Ա   */

    /* ��ʼ�����չ�ԱΪ��һ����Ա */
    copy_employee(&employees[0], &employee_of_the_day);

    /* ����һ�����̣߳������� 1 ִ�� do_loop()�������� 1 �Ź�ԱΪ���չ�Ա */
    ret1 = pthread_create(&p_thread1, NULL, do_loop, (void*)&num1);
    /* �����ڶ������̣߳������� 2 ִ�� do_loop()�������� 2 �Ź�ԱΪ���չ�Ա */
    ret2 = pthread_create(&p_thread2, NULL, do_loop, (void*)&num2);

    /* ����һ��ѭ������鱾�չ�Ա�������Ƿ�һ�£����Ƿ�����ͬһλ��Ա */
    for (i=0; i<60000; i++) {
        /* ���汾�չ�Ա���� */
        copy_employee(&employee_of_the_day, &eotd);
        /* ȡ�����չ�Ա��ԭʼ����*/
	worker = &employees[eotd.number-1];

        /* �Ƚ����� */
	if (eotd.id != worker->id) {
	    printf("mismatching 'id' , %d != %d (loop '%d')\n",
		   eotd.id, worker->id, i);
	    exit(0);
	}
	if (strcmp(eotd.first_name, worker->first_name) != 0) {
	    printf("mismatching 'first_name' , %s != %s (loop '%d')\n",
		   eotd.first_name, worker->first_name, i);
	    exit(0);
	}
	if (strcmp(eotd.last_name, worker->last_name) != 0) {
	    printf("mismatching 'last_name' , %s != %s (loop '%d')\n",
		   eotd.last_name, worker->last_name, i);
	    exit(0);
	}
	if (strcmp(eotd.department, worker->department) != 0) {
	    printf("mismatching 'department' , %s != %s (loop '%d')\n",
		   eotd.department, worker->department, i);
	    exit(0);
	}
	if (eotd.room_number != worker->room_number) {
	    printf("mismatching 'room_number' , %d != %d (loop '%d')\n",
		   eotd.room_number, worker->room_number, i);
	    exit(0);
	}
    }

    /* ȫ�����ݶ�һ�� */
    printf("Glory, employees contents was always consistent\n");
    
    return 0;
}
