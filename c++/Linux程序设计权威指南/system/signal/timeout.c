
	/* File: timeout.c */
	#include <stdio.h>
	#include <unistd.h>
	#include <signal.h>

	char user[40];

	//alarm �Ĳ�׽����
	void catch_alarm(int sig_num)
	{
		//�����ʱ��
		alarm(0);

		printf("Sorry, time limit reached.\n");
		exit(0);
	}

	int main(int argc, char* argv[])
	{

		//�����źŻص�
		signal(SIGALRM, catch_alarm);

		//��ʾ�����û���
		printf("Your Username(10 seconds limit): ");
		fflush(stdout);

		//����10��ʱ��
		alarm(10);

		//�ȴ��û�����
		(char *)gets(user);

		printf("Your username is: '%s'\n", user);

		return 0;
	}


