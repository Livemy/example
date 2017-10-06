
	/* File: polling.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>

	#include <stdio.h>

	int main(int argc, char **argv)
	{
		int i;
		Display *display;
		int screen_num;
		Window win;			//����ID
		unsigned int width, height;	//���ڳߴ�
		unsigned int border_width = 4;	//�߽�հ�
		XEvent report;
		long mask = ExposureMask | KeyPressMask 
			| KeyReleaseMask | ButtonPressMask 
			| ButtonReleaseMask | EnterWindowMask
			| LeaveWindowMask | VisibilityChangeMask
			| StructureNotifyMask;

		// ��X ����������
		if ( (display=XOpenDisplay(NULL)) == NULL )
		{
			printf("Cannot connect to X server\n");
			exit(-1);
		}

		screen_num = DefaultScreen(display);
		width = 600;
		height = 400;

		//��������
		win = XCreateSimpleWindow(display, 	//display
			RootWindow(display,screen_num), //������
			0, 0, width, height, 		//λ�úʹ�С
			border_width, 			//�߽���
			BlackPixel(display,screen_num), //ǰ��ɫ
			WhitePixel(display,screen_num));//����ɫ
	
		//ѡ�񴰿ڸ���Ȥ���¼�����
		XSelectInput(display, win,  mask);

		//��ʾ����
		XMapWindow(display, win);

		//�����¼�ѭ��
		while (1)  {

			//�������е��¼�, ���ȴ�
			if(!XCheckWindowEvent(display, win, mask, &report)){
				printf(".");
				fflush(stdout);
				usleep(100000);
				continue;
			}
			printf("\n");
			fflush(stdout);

			switch  (report.type) {

			//�ع��¼�, ����Ӧ�ػ�
			case Expose: printf("Expose event\n"); break;


			//��ť�¼�
			case ButtonPress: 
				printf("ButtonPress event\n");break;
			case ButtonRelease: 
				printf("ButtonRelease event\n"); break;

			//���ָ���¼�
			case EnterNotify:
				printf("EnterNotify event\n"); break;
			case LeaveNotify:
				printf("LeaveNotify event\n"); break;

			//���̰����¼�
			case KeyPress:
				printf("KeyPress event\n"); break;
			case KeyRelease:
				printf("KeyRelease event\n"); break;


			//���ڵĳߴ�ı�, λ���ƶ�, ���ڶ�ջ�����仯, 
			//��߽��ȷ����仯
			case CirculateNotify:
				printf("CirculateNotify event\n"); break;
			case ConfigureNotify:
				printf("ConfigureNotify event\n"); break;

			//ѡ��(Selection)�¼�, �ͻ������ͨѶ
			case ClientMessage:
				printf("ClientMessage event\n"); break;

			default: break;
			}
		}
	}

