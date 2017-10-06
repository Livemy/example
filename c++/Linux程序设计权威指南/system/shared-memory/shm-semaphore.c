
	/* File: shm-semaphore.c */
	#include <stdio.h>
	#include <linux/types.h>
	#include <linux/shm.h>
	#include <linux/sem.h>
	#include <unistd.h>
	#include <wait.h>
	#include <time.h>
	#include <stdlib.h>

	#define SEM_ID    250

	struct country {
		char name[30];
		char capital_city[30];
		char currency[30];
		int population;
	};

	//ʱ���ӳٺ���
	void random_delay()
	{
		static int initialized = 0;
		int random_num;
		struct timespec delay;

		if (!initialized) {
			srand(time(NULL));
			initialized = 1;
		}

		random_num = rand() % 10;
		delay.tv_sec = 0;
		delay.tv_nsec = 10*random_num;
		nanosleep(&delay, NULL);
	}

	//�����źŵ�
	void sem_lock(int sem_set_id)
	{
		struct sembuf sem_op;

		//�ȴ��źŵ�, ֱ��������ֵ�Ǹ���
		sem_op.sem_num = 0;
		sem_op.sem_op = -1;
		sem_op.sem_flg = 0;
		semop(sem_set_id, &sem_op, 1);
	}

	//�źŵƽ���
	void sem_unlock(int sem_set_id)
	{
		struct sembuf sem_op;

		//�����źŵƵ���ֵ
		sem_op.sem_num = 0;
		sem_op.sem_op = 1;
		sem_op.sem_flg = 0;
		semop(sem_set_id, &sem_op, 1);
	}

	//д����
	void add_country(int sem_set_id, int* countries_num, 
		struct country* countries, char* country_name, 
		char* capital_city, char* currency, int population)
	{
		sem_lock(sem_set_id);
		strcpy(countries[*countries_num].name, country_name);
		strcpy(countries[*countries_num].capital_city, capital_city);
		strcpy(countries[*countries_num].currency, currency);
		countries[*countries_num].population = population;
		(*countries_num)++;
		sem_unlock(sem_set_id);
	}

	//�ӽ���д����
	void do_child(int sem_set_id, int* countries_num, 
		struct country* counties)
	{
		add_country(sem_set_id, countries_num, counties,
			"U.S.A", "Washington", "U.S. Dollar", 250000000);
		random_delay();
		add_country(sem_set_id, countries_num, counties,
			"Israel", "Jerusalem", "New Israeli Shekel", 6000000);
		random_delay();
		add_country(sem_set_id, countries_num, counties,
			"France", "Paris", "Frank", 60000000);
		random_delay();
		add_country(sem_set_id, countries_num, counties,
			"Great Britain", "London", "Pound", 55000000);
	}

	//�����̷��ʹ����ڴ�, ����ӡ���
	void do_parent(int sem_set_id, int* countries_num, 
		struct country* countries)
	{
		int i, num_loops;

		for (num_loops=0; num_loops < 5; num_loops++) {
			sem_lock(sem_set_id);
			printf("------------------------------------------\n");
			printf("Number Of Countries: %d\n", *countries_num);
			for (i=0; i < (*countries_num); i++) {
				printf("Country %d:\n", i+1);
				printf("  name: %s:\n", countries[i].name);
				printf("  capital city: %s:\n", 
					countries[i].capital_city);
				printf("  currency: %s:\n", 
					countries[i].currency);
				printf("  population: %d:\n", 
					countries[i].population);
			}
			sem_unlock(sem_set_id);
			random_delay();
		}
	}

	int main(int argc, char* argv[])
	{
		int sem_set_id;            //�źŵƵ�ID
		union semun sem_val;       //�źŵ���ֵ
		int shm_id;                //�����ڴ��ID
		char *shm_addr;            //�����ڴ�ĵ�ַ
		int *countries_num;        //����������
		struct country* countries; //����
		struct shmid_ds shm_desc;
		int rc;
		pid_t pid;
		int child_status;

		//�����źŵ�
		sem_set_id = semget(SEM_ID, 1, IPC_CREAT | 0600);
		if (sem_set_id == -1) {
			perror("main: semget");
			exit(1);
		}

		//�����źŵƵ���ֵ�� 1
		sem_val.val = 1;
		rc = semctl(sem_set_id, 0, SETVAL, sem_val);
		if (rc == -1) {
			perror("main: semctl");
			exit(1);
		}

		//���������ڴ�
		shm_id = shmget(100, 2048, IPC_CREAT | IPC_EXCL | 0600);
		if (shm_id == -1) {
			perror("main: shmget: ");
			exit(1);
		}

		//attach �����ڴ�
		shm_addr = (char *)shmat(shm_id, NULL, 0);
		if (!shm_addr) {
			perror("main: shmat: ");
			exit(1);
		}

		//��ʼ������
		countries_num = (int*) shm_addr;
		*countries_num = 0;
		countries = (struct country*) ((void*)shm_addr+sizeof(int));

		//�����ӽ���
		pid = fork();
		switch (pid) {
			case -1:
				perror("fork: ");
				exit(1);
			case 0:
				do_child(sem_set_id, countries_num, countries);
				exit(0);
			default:
				do_parent(sem_set_id, countries_num, countries);
				break;
		}

		//�ȴ��ӽ����˳�
		wait(&child_status);

		//���빲���ڴ�
		if (shmdt(shm_addr) == -1) {
			perror("main: shmdt: ");
		}

		//���������ڴ�
		if (shmctl(shm_id, IPC_RMID, &shm_desc) == -1) {
			perror("main: shmctl: ");
		}

		return 0;
	}

