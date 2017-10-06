	/* File: keyboard.c */

	#include <unistd.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <signal.h>
	#include <vga.h>
	#include <vgakeyboard.h>

	int main(int argc, char *argv[])
	{
		//x, y ��ǰλ��, w, h ��Ļ�ߴ�
		int x, y, w, h;

		printf("Arrow keys to draw, 'q' or ESC key to quit.\n");
		printf("press any key to start...\n");
		while(!vga_getkey());

		//��ʼ��
		vga_init();

		vga_setmode(G320x200x256);

		//���̳�ʼ��
		if (keyboard_init()) {
			printf("Could not initialize keyboard.\n");
			exit(1);
		}

		//С����������
		keyboard_translatekeys(TRANSLATE_CURSORKEYS|TRANSLATE_DIAGONAL);

		//ȡ����Ļ�ߴ�,��ʼ��λ��
		w = vga_getxdim();
		h = vga_getydim();
		x = w / 2;
		y = h / 2;
    		//������ɫ 
		vga_setcolor(3);

		for (;;) { 

			//����
			vga_drawpixel(x, y);

			usleep(10000);

			keyboard_update();

			//����ͷ���Ƿ���, �ƶ�����
			if (keyboard_keypressed(SCANCODE_CURSORLEFT)) x--;
			if (keyboard_keypressed(SCANCODE_CURSORRIGHT)) x++;
			if (keyboard_keypressed(SCANCODE_CURSORUP)) y--;
			if (keyboard_keypressed(SCANCODE_CURSORDOWN)) y++;

			//����Ƿ񳬳��߽�
			if (x < 0) x = 0;
			if (x >= w) x = w - 1;
			if (y < 1) y = 1;
			if (y >= h) y = h - 1;

			//Q �� ESC ���˳�
			if (keyboard_keypressed(SCANCODE_Q) ||
				keyboard_keypressed(SCANCODE_ESCAPE)) break;
		}

		//��ԭ
		keyboard_close();
		vga_setmode(TEXT);
		exit(0);
	}

