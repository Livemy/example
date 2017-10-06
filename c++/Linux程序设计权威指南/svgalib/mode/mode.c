
	#include <vga.h>

	int main(int argc, char *argv[])
	{
		
		int oldmode;
		int mode = G320x200x256;

		//��õ�ǰ��ģʽ
		oldmode = vga_getcurrentmode();

		//��ʼ��
		vga_init();

		//�ж��Ƿ�֧�ָ�ģʽ
		if(vga_hasmode(mode)) 
			vga_setmode(mode);
		else {
			printf("No such mode\n");
			exit(1);
		}

		mode = vga_getcurrentmode();

		//�ָ�ԭ����ģʽ 
		vga_setmode(oldmode);

		//��ӡ��ǰģʽ��
		printf("Current mode:%s\n", vga_getmodename(mode));

		return 0;
	}
