
	/* File: producer-consumer.c */

	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <time.h>
	#include <sys/types.h>
	#include <linux/sem.h>

	#define NUM_LOOPS       20

	int main(int argc, char* argv[])
	{
		int sem_set_id;           //�źŵƼ���ID
		union semun sem_val;      //�źŵƵ���ֵ
		int child_pid;            //�ӽ��̵�PID
		struct sembuf sem_op;     //�źŵƲ����ṹ
		int i;
		int rc;                   //����ֵ
		struct timespec delay;    //�ӳ�ʱ��

		//�����źŵƼ�, ����ֻ����һ���źŵ�
		sem_set_id = semget(IPC_PRIVATE, 1, 0600);
		if (sem_set_id == -1) {
			perror("main: semget");
			exit(1);
		}
		printf("semaphore set created, semaphore set id '%d'.\n", 
			sem_set_id);

		//�źŵ���ֵ����Ϊ0
		sem_val.val = 0;
		rc = semctl(sem_set_id, 0, SETVAL, sem_val);

		//�����ӽ���
		child_pid = fork();
		switch (child_pid) {
			case -1:	//ʧ��
				perror("fork");
				exit(1);
			case 0:		//�ӽ���
				for (i=0; i<NUM_LOOPS; i++) {
					//������, ֱ���źŵƵ���ֵ��Ϊ�Ǹ���
					sem_op.sem_num = 0;
					sem_op.sem_op = -1;
					sem_op.sem_flg = 0;
					semop(sem_set_id, &sem_op, 1);
					printf("consumer: '%d'\n", i);
					fflush(stdout);
				}
				break;
			default:	//������
				for (i=0; i<NUM_LOOPS; i++) {
					printf("producer: '%d'\n", i);
					fflush(stdout);
					//���źŵƵ���ֵ����1
					sem_op.sem_num = 0;
					sem_op.sem_op = 1;
					sem_op.sem_flg = 0;
					semop(sem_set_id, &sem_op, 1);

					//�ȴ�һ��ʱ��
					if (rand() > 3*(RAND_MAX/4)) {
						delay.tv_sec = 0;
						delay.tv_nsec = 10;
						nanosleep(&delay, NULL);
					}
				}
				break;
		}
		return 0;
	}
