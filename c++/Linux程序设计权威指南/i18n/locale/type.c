
	/* file type.c */
	#include <stdio.h>
	#include <locale.h>
	#include <stdlib.h>
	#include <wctype.h>

	int main(int argc, char *argv[])
	{
		unsigned char *mbc = "��";
		wchar_t wcc;
		unsigned char buf[100];

		//���� locale
		setlocale(LC_ALL, "");

		//�Ѷ��ֽ��ַ���ת��Ϊ���ַ�
		mbtowc(&wcc, mbc, 2);
		printf("wc = %x\n", wcc);

		//ת���ض��ֽ��ַ�
		wctomb(buf, wcc);
		printf("mb = %s\n", buf);

		printf("���н�����ϰ汾��glibc�¿��ܲ���ȷ:\n");
		printf("iswalpnum: %d\n", iswalnum(wcc));
		printf("iswdigit : %d\n", iswdigit(wcc));
		printf("iswpunct : %d\n", iswpunct(wcc));

	}

