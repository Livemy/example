
	/* File: sharedmem.c */
	#include <stdio.h>
	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/shm.h>

	//�����ŵ����ݽṹ
	struct country {
		char name[30];
		char capital_city[30];
		char currency[30];
		int population;
	};

	int main(int argc, char* argv[])
	{
	
		int shm_id;               //�����ڴ��ID
		char *shm_addr;           //�����ڴ�ĵ�ַ
		int *countries_num;       //���ݽṹ������
		struct country *countries;//����
		struct shmid_ds shm_desc;
 		int i;

		//���乲���ڴ�, 2048���ֽ�
		shm_id = shmget(100, 2048, IPC_CREAT | IPC_EXCL | 0600);
		if (shm_id == -1) {
			perror("main: shmget: ");
			exit(1);
		}

		//Attach �����ڴ�, ȡ�ý����еĹ����ڴ�ĵ�ַ
		shm_addr = shmat(shm_id, NULL, 0);
		if (!shm_addr) { 	//ʧ��
			perror("main: shmat: ");
			exit(1);
		}

		//�������ݲ����
		countries_num = (int*) shm_addr;
		*countries_num = 0;
		countries = (struct country*) ((void*)shm_addr+sizeof(int));
		
		strcpy(countries[0].capital_city, "U.S.A");
		strcpy(countries[0].capital_city, "Washington");
		strcpy(countries[0].currency, "U.S. Dollar");
		countries[0].population = 250000000;
		(*countries_num)++;

		strcpy(countries[1].capital_city, "Israel");
		strcpy(countries[1].capital_city, "Jerusalem");
		strcpy(countries[1].currency, "New Israeli Shekel");
		countries[1].population = 6000000;
		(*countries_num)++;

		strcpy(countries[1].capital_city, "France");
		strcpy(countries[1].capital_city, "Paris");
		strcpy(countries[1].currency, "Frank");
		countries[1].population = 60000000;
		(*countries_num)++;

		//��ӡ����
		for (i=0; i < (*countries_num); i++) {
			printf("Countery %d:\n", i+1);
			printf("  name: %s:\n", countries[i].name);
			printf("  capital city: %s:\n", countries[i].capital_city);
			printf("  currency: %s:\n", countries[i].currency);
			printf("  population: %d:\n", countries[i].population);
		}

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
