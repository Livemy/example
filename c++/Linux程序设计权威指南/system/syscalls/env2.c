

	/* File: env2.c */
	int main(int argc, char **argv)
	{
		extern char **environ;

		char **env = environ;

		//��ӡ��������
		while(*env){
			printf("%s\n", *env);
			env++;
		}

		return 0;
	}
