
	/* file wchar.c */
	#include <stdio.h>
	#include <locale.h>
	#include <stdlib.h>
	#include <wctype.h>
	#include <wchar.h>

	int main(int argc, char *argv[])
	{
		unsigned char *mbs1 = "����Mixed�ַ���.";
		unsigned char *mbs2 = "������ַ���";
		unsigned char mbs[100];
		wchar_t wcs[100], wcs1[100], wcs2[100];
		unsigned char buf[100];
		int n;

		//���� locale
		setlocale(LC_ALL, "");

		//�Ѷ��ֽ��ַ���ת��Ϊ���ַ�
		printf("mbs1:%s\n", mbs1);
		printf("mbs2:%s\n", mbs2);
		strcpy(mbs, mbs1);
		strcat(mbs, mbs2);
		printf("mbs1+mbs2:%s\n\n", mbs);

		printf("ʹ�����ַ����任:\n");
		n = mbstowcs(wcs, mbs, strlen(mbs));
		printf("wcslen = %d\n", wcslen(wcs));
		n = wcstombs(buf, wcs, 100);
		printf("Number of multibyte chars:%d\n", n);
		printf("mbs=%s\n\n", buf);

		printf("ʹ�÷��ַ����任:\n");
		n = mbstowcs(wcs1, mbs1, strlen(mbs1));
		printf("wcslen of mbs1:%d\n", n);
		n = mbstowcs(wcs2, mbs2, strlen(mbs2));
		printf("wcslen of mbs2:%d\n", n);
		wcscpy(wcs, wcs1);
		wcscat(wcs, wcs2);
		printf("wcslen = %d\n", wcslen(wcs));
		n = wcstombs(buf, wcs, 100);
		printf("Number of multibyte chars:%d\n", n);
		printf("mbs=%s\n\n", buf);

	}

