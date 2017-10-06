
	/* File: fbinfo.c */

	#include <unistd.h>
	#include <stdio.h>
	#include <fcntl.h>
	#include <linux/fb.h>		//����FB��Ϣ�Ľṹ
	#include <sys/mman.h>

	int main(int argc, char *argv[])
	{
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
		//��ӡ��Ϣ
		printf("fix info - card id       :%s\n", finfo.id);
		printf("fix info - smem start    :0x%x\n", finfo.smem_start);
		printf("fix info - smem len      :0x%x\n", finfo.smem_len);
		printf("fix info - type          :%d\n", finfo.type);
		printf("fix info - visual        :%d\n", finfo.visual);
		printf("fix info - line length   :%d\n\n", finfo.line_length);

		if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo)) {
			printf("Error reading variable information.\n");
			exit(1);
		}
		printf("var info - xres          :%d\n", vinfo.xres);
		printf("var info - yres          :%d\n", vinfo.yres);
		printf("var info - xres virtual  :%d\n", vinfo.xres_virtual);
		printf("var info - yres virtual  :%d\n", vinfo.yres_virtual);
		printf("var info - x offset      :%d\n", vinfo.xoffset);
		printf("var info - y offset      :%d\n", vinfo.yoffset);
		printf("var info - bits_per_pixel:%d\n", vinfo.bits_per_pixel);
		printf("var info - width         :%d\n", vinfo.width);
		printf("var info - height        :%d\n", vinfo.height);

		close(fd);
		return 0;
	}
        
