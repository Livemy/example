
	/* File: attrib.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>

	#include <stdio.h>



	int main(int argc, char **argv)
	{
		static char *string = "Hello World!";
		Display *display;
		int screen_num;
		Window win;			//����ID
		unsigned int width, height;	//���ڳߴ�
		unsigned int border_width = 4;	//�߽�հ�
		unsigned int display_width, display_height;//��Ļ�ߴ�
		int count;
		XEvent report;
		GC gc;
		unsigned long valuemask = 0;
		XGCValues values;
		char *display_name = NULL;
	
		// ��X ����������
		if ( (display=XOpenDisplay(display_name)) == NULL )
		{
			printf("Cannot connect to X server %s\n", 
					XDisplayName(display_name));
			exit(-1);
		}

		//���ȱʡ�� screen_num
		screen_num = DefaultScreen(display);

		//�����Ļ�Ŀ�Ⱥ͸߶�
		display_width = DisplayWidth(display, screen_num);
		display_height = DisplayHeight(display, screen_num);
	
		//ָ�����������ڵĿ�Ⱥ͸߶�
		width = display_width/3;
		height = display_height/4;
	
		//��������
		win = XCreateSimpleWindow(display, 	//display
			RootWindow(display,screen_num), //������
			0, 0, width, height, 		//λ�úʹ�С
			border_width, 			//�߽���
			BlackPixel(display,screen_num), //ǰ��ɫ
			WhitePixel(display,screen_num));//����ɫ
	
		//ѡ�񴰿ڸ���Ȥ���¼�����
		XSelectInput(display, win, 
			ExposureMask | KeyPressMask | 
			ButtonPressMask | StructureNotifyMask);

		//����GC
		gc = DefaultGC(display, screen_num);

		//��ʾ����
		XMapWindow(display, win);

		//�����¼�ѭ��
		while (1)  {

			//ȡ�ö����е��¼�
			XNextEvent(display, &report);
			switch  (report.type) {

			//�ع��¼�, ����Ӧ�ػ�
			case Expose:
				//ȡ�����һ���ع��¼�
				if (report.xexpose.count != 0) break;
				break;

			//���ڳߴ�ı�, ����ȡ�ô��ڵĿ�Ⱥ͸߶�
			case ConfigureNotify:
				break;

			//�������ʾ���ڵ�ĳЩ����
			case ButtonPress:
				{
				XWindowAttributes xa;
				Window root;
				int x, y;
				unsigned int w, h, border, depth;
					
				XGetWindowAttributes(display,win,&xa);
				printf("geometry:%d %d %d %d\n",
					xa.x,xa.y, xa.width, xa.height);
				printf("override redirect:%d\n", 
					xa.override_redirect);
				XGetGeometry(display,win,&root, &x, &y,
					&w, &h, &border, &depth);
				printf("attrib: x:%d y:%d w:%d h:%d "
					"border:%d depth: %d\n",
					x, y, w, h, border, depth);
				}
				break;
			case KeyPress:
				XFreeGC(display, gc);
				exit(1);
			default:
				
				break;
			}
		}
	}
