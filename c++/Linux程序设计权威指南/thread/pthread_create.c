#include <stdio.h>       /* �����׼�� I/O ����         */
#include <pthread.h>     /* ���� pthread ���������ݽṹ */

/* ���߳̽�ִ�еĺ��� */
void*
do_loop(void* data)
{
    int i;                      /* ��������Ҫ��ӡ������ */
    int j;                      /* ���������ӳ�         */
    int me = *((int*)data);     /* �̱߳��             */

    for (i=0; i<10; i++) {
        for (j=0; j<500000; j++) /* �ӳ�ѭ�� */
            ;
        printf("'%d' - Got '%d'\n", me, i);
    }

    /* �˳��߳� */
    pthread_exit(NULL);
}

/* ����� main ������ʼִ�� */
int
main(int argc, char* argv[])
{
    int        ret;            /* �̴߳��������ķ���ֵ */
    pthread_t  p_thread;       /* �̵߳� ID ��         */
    int        a         = 1;  /* �̱߳��             */
    int        b         = 2;  /* �̱߳��             */

    /* ����һ�����̣߳�����ִ�� do_loop() */
    ret = pthread_create(&p_thread, NULL, do_loop, (void*)&a);
    /* �����߳���Ҳͬ��ִ�� do_loop() */
    do_loop((void*)&b);

    /* ����ִ�е���һ�� */
    return 0;
}

