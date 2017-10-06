
	/* File: pixel.c */

	#include "color.h"

	#include <unistd.h>
	#include <stdio.h>
	#include <fcntl.h>
	#include <linux/fb.h>		//����FB��Ϣ�Ľṹ
	#include <sys/mman.h>

	int main(int argc, char *argv[])
	{
		int i;

		//FB�豸���ļ�������
		int fd;

		//�ṹ
		struct fb_fix_screeninfo finfo;
		struct fb_var_screeninfo vinfo;

		//���豸
		fd = open("/dev/fb0", O_RDWR);
		if (!fd) {
			printf("Cannot open framebuffer device.\n");
			exit(1);
		}
		printf("The framebuffer device was opened successfully.\n");

		//ȡ�ù̶���Ϣ
		if (ioctl(fd, FBIOGET_FSCREENINFO, &finfo)) {
			printf("Error reading fixed information.\n");
			exit(1);
		}
		//ȡ�ÿɱ���Ϣ
		if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo)) {
			printf("Error reading variable information.\n");
			exit(1);
		}

		//VGA16 ��ʼ��
		vga16_init(fd, &finfo, &vinfo);
		
		//����Ļ
		vga16_clear();

		//����
		for(i=0; i<200; i++)
			vga16_set_pixel(i, i, COLOR_HI_GREEN);
		
		

		close(fd);
		return 0;
	}
        
