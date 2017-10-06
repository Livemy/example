
	/* File: ctrl-c.c */
	#include <stdio.h> 
	#include <unistd.h>
	#include <signal.h>

	void catch_int(int sig_num)
	{
		// �������� SIGINT �� handler
		signal(SIGINT, catch_int);

		printf("Control-C is ignored, please don't waste time.\n");
		fflush(stdout);
	}

	int main(int argc, char* argv[])
	{
		//����Control-C�Ļص�
		printf("Want to try Control-C ?\n");

		signal(SIGINT, catch_int);
 
		//����ѭ��
		while(1) pause();
	}
