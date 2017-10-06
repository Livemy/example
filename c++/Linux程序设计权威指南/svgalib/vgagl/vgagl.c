
	/* File: vgagl.c */
	#include <stdlib.h>
	#include <stdio.h>
	#include <vga.h>
	#include <vgagl.h>

	#define CAPTURE

	int VGAMODE;
	GraphicsContext *backscreen;
	GraphicsContext *physicalscreen;

	void draw(void)
	{
		int i, j, b, y=0;
		int color = 64;

		//�ı���ɫ��
		for (i = 0; i < 64; i++) {
			b = 63 - i;
			gl_setpalettecolor(color, 0, 0, b);
			for (j = 0; j < 3; j++){
				//����
				gl_hline(0, y, WIDTH-1, color);
				y++;
			}
			color++;
		}

		//��ͼԪ
		gl_fillbox(30, 30, 30, 20, 2);
		gl_circle(100, 80, 30, 3);

		//���������������ɫ
		gl_setfont(8, 8, gl_font8x8);
		gl_setwritemode(FONT_COMPRESSED + WRITEMODE_OVERWRITE);
		gl_setfontcolors(0, vga_white());

		//д�ַ���
		gl_write(20, 180, "Press any key to exit...");

	}


	int main(int argc, char *argv[])
	{
		//��ʼ��
		vga_init();
		VGAMODE = vga_getdefaultmode();
		if (VGAMODE == -1) VGAMODE = G320x200x256;
		if (!vga_hasmode(VGAMODE)) {
			printf("Mode not available.\n");
			exit(-1);
		}

		//����ģʽ
		vga_setmode(VGAMODE);

		//����GraphicsContext
		gl_setcontextvga(VGAMODE);
		physicalscreen = gl_allocatecontext();
		gl_getcontext(physicalscreen);

		//�����Ļ
		gl_clearscreen(0);

		//��ͼ
		draw();

		//ץȡ��Ļ
		#ifdef CAPTURE
		capture();
		#endif

		//��ԭ
		getchar();
		vga_setmode(TEXT);
		return 0;
	}
