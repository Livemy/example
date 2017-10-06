
	/* File: pipes.c */
	#include <stdio.h>
	#include <sys/types.h>
	#include <unistd.h>
	#include <ctype.h>

	//�����̴ӿ���̨������, ����ܵ���д����
	void user_handler(int input_pipe[], int output_pipe[])
	{
		int c;
		int rc;

		//�رղ���Ҫ���ļ�������
		close(input_pipe[1]);
		close(output_pipe[0]);

		while ((c = getchar()) > 0) {	//���ַ�

			//��ܵ���д�ַ�
			rc = write(output_pipe[1], &c, 1);
			if (rc == -1) {
				perror("user_handler: write");
				close(input_pipe[0]);
				close(output_pipe[1]);
				exit(1);
			}

			//�ӹܵ��ж��ַ�
			rc = read(input_pipe[0], &c, 1);
			if (rc <= 0) {
				perror("user_handler: read");
				close(input_pipe[0]);
				close(output_pipe[1]);
				exit(1);
			}

			//�����ַ�
			putchar(c);
		}

		//�˳�ʱ�رչܵ�
		close(input_pipe[0]);
		close(output_pipe[1]);
		exit(0);
	}


	void translator(int input_pipe[], int output_pipe[])
	{
		int c;
		int rc;
		char ch;

		//�رղ���Ҫ���ļ�������
		close(input_pipe[1]);
		close(output_pipe[0]);

		//�ӹܵ��ж��ַ�
		while (read(input_pipe[0], &c, 1) > 0) {
			//��Сдת��
			ch = (char) c;
			if(isascii(ch) && isupper(ch)) c = tolower(ch);
			else if(isascii(ch) && islower(ch)) c = toupper(ch);
			//��ܵ���д�ַ�
			rc = write(output_pipe[1], &c, 1);
			if (rc == -1) {
				perror("translator: write");
				close(input_pipe[0]);
				close(output_pipe[1]);
				exit(1);
			}
		}

		//�˳�ʱ�رչܵ�
		close(input_pipe[0]);
		close(output_pipe[1]);
		exit(0);
	}

	int main(int argc, char* argv[])
	{
		//�����ܵ�
		int user_to_translator[2];
		int translator_to_user[2];
		int pid;
		int rc;

		//���������ܵ�
		rc = pipe(user_to_translator);
		if (rc == -1) {
			perror("main: pipe user_to_translator");
			exit(1);
		}
		rc = pipe(translator_to_user);
		if (rc == -1) {
			perror("main: pipe translator_to_user");
			exit(1);
		}

		//�����ӽ���
		pid = fork();

		switch (pid) {
			case -1:	//����
				perror("main: fork");
				exit(1);
			case 0:		//�ӽ���
				translator(user_to_translator, 
					translator_to_user);
			default:
				user_handler(translator_to_user, 
					user_to_translator);
		}
		return 0;
	}


