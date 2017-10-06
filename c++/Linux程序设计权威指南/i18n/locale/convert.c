
	/* file convert.c */
	#include <stdio.h>
	#include <locale.h>
	#include <stdlib.h>
	#include <wctype.h>

	int main(int argc, char *argv[])
	{
		unsigned char *mbs = "����Mixed�ַ���.";
		wchar_t wcs[100];
		unsigned char buf[100];
		int n;

		//���� locale
		setlocale(LC_ALL, "");

		//�Ѷ��ֽ��ַ���ת��Ϊ���ַ�
		printf("mbs:%s\n", mbs);
		n = mbstowcs(wcs, mbs, strlen(mbs));
		printf("wcslen = %d\n", wcslen(wcs));
		printf("return by mbstowcs():%d\n\n", n);

		//ת���ض��ֽ��ַ���
		n = wcstombs(buf, wcs, 100);
		printf("Number of multibyte chars:%d\n", n);
		printf("mbs =%s\n\n", buf);

		//�����ж��ַ����ĳ��ȵĺ���
		n = mbstowcs(NULL, mbs, 0);
		printf("mbstowcs(NULL, mbs, 0): %d\n", n);
		n = wcstombs(NULL, wcs, 0);
		printf("wcstombs(NULL, wcs, 0): %d\n", n);



	}

