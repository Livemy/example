
	/* File: helloworld.c */

	#include <curses.h>

	int main(int argc, char *argv[])
	{

		//��ʼ��
		initscr();

		//���߿�
		box(stdscr, ACS_VLINE, ACS_HLINE);

		//�ڵ�11��, ��30��д�ַ���
		mvaddstr(11, 30, "Hello World!");

		//ˢ����Ļ
		refresh();

		//�ȴ�����
		getch();

		//����
		endwin();

		return 0;
	}
