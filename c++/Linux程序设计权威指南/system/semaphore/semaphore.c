
	/* File: semaphore.c */
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <time.h>
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <linux/sem.h>

	#define NUM_PROCS  5
	#define SEM_ID    250
	#define FILE_NAME "/tmp/sem_mutex"
	#define DELAY     400000


	void update_file(int sem_set_id, char* file_path, int number)
	{
		struct sembuf sem_op;
		FILE* file;

		//�ȴ��źŵƵ���ֵ��Ϊ�Ǹ���
		sem_op.sem_num = 0;
		sem_op.sem_op = -1;
		sem_op.sem_flg = 0;
		semop(sem_set_id, &sem_op, 1);

		//д���ļ�, д�����ֵ�ǵ�ǰ���̵Ľ��̺�
		file = fopen(file_path, "w");
		if (file) {
			fprintf(file, "%d\n", number);
			printf("%d\n", number);
			fclose(file);
		}

		//�����ź�, ���źŵƵ���ֵ��1
		sem_op.sem_num = 0;
		sem_op.sem_op = 1;
		sem_op.sem_flg = 0;
		semop(sem_set_id, &sem_op, 1);
	}

	//�ӽ���д�ļ�
	void do_child_loop(int sem_set_id, char* file_name)
	{
		pid_t pid = getpid();
		int i, j;

		for (i=0; i<3; i++) {
			update_file(sem_set_id, file_name, pid);
			for (j=0; j<400000; j++) ;
		}
	}

	int main(int argc, char **argv)
	{
		int sem_set_id;           //�źŵƼ���ID
		union semun sem_val;      //�źŵƵ���ֵ, ���� semctl()
		int child_pid;            //�ӽ��̵Ľ��̺�
		int i;
		int rc;

		//�����źŵƼ�, ID��250, ����ֻ��һ���źŵ�
		sem_set_id = semget(SEM_ID, 1, IPC_CREAT | 0600);
		if (sem_set_id == -1) {
			perror("main: semget");
			exit(1);
		}

		//�ѵ�һ���źŵƵ���ֵ����Ϊ1
		sem_val.val = 1;
		rc = semctl(sem_set_id, 0, SETVAL, sem_val);
		if (rc == -1) {
			perror("main: semctl");
			exit(1);
		}

		//����һЩ�ӽ���, ʹ���ǿ���ͬʱ�Ծ����ķ�ʽ�����źŵ�
		for (i=0; i<NUM_PROCS; i++) {
			child_pid = fork();
			switch(child_pid) {
				case -1:
					perror("fork");
					exit(1);
				case 0:		//�ӽ���
					do_child_loop(sem_set_id, FILE_NAME);
					exit(0);
				default:	//�����̽�������
					break;
			}
		}

		//�ȴ��ӽ��̽���
		for (i=0; i<NUM_PROCS; i++) {
			int child_status;
			wait(&child_status);
		}

		printf("main: we're done\n");
		fflush(stdout);
		return 0;
	}


