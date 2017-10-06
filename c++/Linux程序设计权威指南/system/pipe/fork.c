
	/* File: fork.c */

	#include <sys/types.h>
	#include <sys/wait.h>

	int main(int argc, char **argv)
	{
		pid_t child_pid;
		int child_status;

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
				//�ȴ��ӽ����˳�
				printf("parent: I am waiting child process\n");
				wait(&child_status);
		}
	}
