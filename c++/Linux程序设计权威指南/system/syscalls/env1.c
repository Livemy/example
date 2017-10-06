
	/* File: env1.c */
	int main(int argc, char **argv)
	{
		//��ӡ�������� LC_ALL ��ֵ
		if(getenv("LC_ALL"))
			printf("LC_ALL is %s\n", getenv("LC_ALL"));

		//�ѻ�����������Ϊ������ֵ
		setenv("LC_ALL", "de_DE", 1);
		printf("Now LC_ALL is %s\n", getenv("LC_ALL"));

		//ȡ����������
		unsetenv("LC_ALL");
		printf("Now LC_ALL is %s\n", getenv("LC_ALL"));

		return 0;
	}
