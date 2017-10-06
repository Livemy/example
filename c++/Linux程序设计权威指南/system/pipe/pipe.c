
	/* File: pipe.c */

	#include <stdio.h>
	#include <sys/types.h>
	#include <unistd.h>

	//�ӽ��̶�����
	void read_data(int pipes[]) {
		int c;
		int rc;

		//�ر�д��һ��
		close(pipes[1]);

		//�����ݲ���ӡ 
		while ((rc = read(pipes[0], &c, 1)) > 0){
			putchar(c);
		}

		exit(0);
	}

	//������д����
	void write_data(int pipes[])
	{
		int c;
		int rc;

		//�رն�����һ��
		close(pipes[0]);

		//�ӿ���̨�����ݲ���ܵ�д����
		while ((c = getchar()) > 0) {
			rc = write(pipes[1], &c, 1);
			if (rc == -1) {
				perror("Parent: write");
				close(pipes[1]);
				exit(1);
			}
		}

		//�ر�дһ��
		close(pipes[1]);
		exit(0);
	}

	int main(int argc, char*argv[])
	{
		int pipes[2];
		pid_t pid;		//fork���صĽ��̺�
		int rc;			//����ֵ

		//�����ܵ�
		rc = pipe(pipes);
		if (rc == -1) {
			perror("pipe");
			exit(1);
		}

		//�����ӽ���
		pid = fork();

		switch(pid) {
			//ʧ��
			case -1:
				perror("fork");
				exit(1);
			//�ӽ���
			case 0:
				read_data(pipes);
				//���ܵ�����
			//������
			default:
				write_data(pipes);
				//���ܵ�����/
		}
		return 0;
	}


