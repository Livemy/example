
	/* File: pad.c */

	#include <curses.h>

	int main(int argc, char *argv[])
	{
		int i, j;
		int w, h;
		WINDOW *pad;

		//��ʼ��
		initscr();

		//�����Ļ�ߴ�
		getmaxyx(stdscr, h,  w);

		//������
		for(i=0; i<h; i++)
		for(j=0; j<w; j++){
			mvaddch(i, j, ACS_CKBOARD);
		}
		refresh();

		//��������
		pad = newpad(80, 128);
		for(i=0; i<80; i++){
			char line[128];
			sprintf(line, "This line in pad is numbered %d\n", i);
			mvwprintw(pad, i, 0, line);
		}


		//ˢ����Ļ
		refresh();
		prefresh(pad, 0, 1, 5, 10, 20, 45);
		
		for(i=0; i<50; i++){
			prefresh(pad, i+1, 1, 5, 10, 20, 45);
			usleep(30000);
		}

		//�ȴ�����
		getch();

		//����
		delwin(pad);
		endwin();

		return 0;
	}
