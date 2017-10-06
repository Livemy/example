
	/* File: signal.c */

	#include <stdio.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <signal.h>

	void signal_handler(int n)
	{
		//��ʱ�Ѿ���һ�� zombie ����
		int child_status;

		wait(&child_status);
		printf("child exited.\n");
	}


	int main(int argc, char **argv)
	{
		pid_t child_pid;
		int child_status;

		signal(SIGCHLD, signal_handler);

		//�����½���
		child_pid = fork();

		//���ݷ���ֵ�ж��Ƿ�ɹ�, ����ɹ��ж����ӽ��̻��Ǹ�����
		switch (child_pid) {
			case -1:	//ʧ��
				perror("fork");
				exit(1);
			case 0:		//�ӽ���
				printf("child: hello from child process\n");
				exit(0);
			default:	//�ɹ�, ��������

				//�ȴ�
				//��ʱ��������ն˿��Ƿ��� zombie ����?
				sleep(10);
		}
	}
