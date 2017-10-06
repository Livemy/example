

	/* File: menu.c */
	#include <curses.h>
	#include <menu.h>
	#include <stdlib.h>
	#include <ctype.h>


	static const char *months[] = {
		"January", "Febrary", "March", "April", "May", "June", "July",
		"August", "September", "October", "November", "December", NULL
	};

	#define N_ITEMS sizeof(months)/sizeof(months[0])

	int main(int argc, char *argv[])
	{
		int i;
		int ch;
		int mrows, mcols;
		WINDOW  *win, *subwin;

		ITEM *items[N_ITEMS];
		MENU *mymenu;

		//��ʼ��
		if(initscr() == NULL) {
			perror("initcurs");
			exit(EXIT_FAILURE);
		}
		cbreak();
		noecho();
		keypad(stdscr, TRUE);

		//�����˵���
		for(i=0; i<N_ITEMS; i++){
			items[i] = new_item(months[i], "");
		}

		//�����˵�
		mymenu = new_menu(items);

		//����Ϊ5�е��еĲ˵�
		set_menu_format(mymenu, 5, 1);
		set_menu_mark(mymenu, "*");

		//��ò˵�������������
		scale_menu(mymenu, &mrows, &mcols);

		//�������ں��Ӵ���
		win = newwin(mrows + 2, mcols + 2, 3, 30);
		keypad(win, TRUE);
		box(win, 0, 0);
		subwin = derwin(win, 0, 0, 1, 1);

		//���ò˵��Ĵ���
		set_menu_sub(mymenu, subwin);

		//���Ӵ����Ϸ��ò˵�
		post_menu(mymenu);

		refresh();
		wrefresh(win);

		//�������
		while(toupper(ch = wgetch(win)) != '\n') {
			if(ch == KEY_DOWN)
				menu_driver(mymenu, REQ_DOWN_ITEM);
			else if(ch == KEY_RIGHT)
				menu_driver(mymenu, REQ_RIGHT_ITEM);
			else if(ch == KEY_UP)
				menu_driver(mymenu, REQ_UP_ITEM);
			else if(ch == KEY_LEFT)
				menu_driver(mymenu, REQ_LEFT_ITEM);
		}

		mvprintw(LINES - 2, 0, "You chose: %s\n", 
			item_name(current_item(mymenu)));

		refresh();
		unpost_menu(mymenu);
		getch();

		//�ͷ��ڴ�
		free_menu(mymenu);
		for(i=0; i<N_ITEMS; i++)free_item(items[i]);
		endwin();
		exit(0);
	}
