
	/* File: wmhint.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>

	#include <stdio.h>
	#include "icon.xbm"

	int main(int argc, char **argv)
	{
		int i;
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
		Colormap default_cmap;
		XColor color;
		int rc;			//��������ֵ

		//wm
		//����������
		XTextProperty window_name_property;
		//ͼ��������
		XTextProperty icon_name_property;
		//�ߴ簵ʾ�ṹָ��
		XSizeHints* win_size_hints;
		//���ڰ�ʾ�ṹָ��
		XWMHints* win_hints;
		//ͼ����ʹ�õ�ͼ��(xbm)
		Pixmap icon_pixmap;

		//��������ͼ����
		char* window_name = "Hello World!";
		char* icon_name = "Another World!";


		printf("This program has been iconified.\n");

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

		//��ȡȱʡ����ɫ��
		default_cmap = DefaultColormap(display, screen_num);
	
		//ָ�����������ڵĿ�Ⱥ͸߶�
		width = 400;
		height = 300;

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
		gc = XCreateGC(display, win, valuemask, &values);


		//��ʾ����
		XMapWindow(display, win);

		//�Ѵ�����ת��ΪX����(Property)
		rc = XStringListToTextProperty(&window_name, 
			1, &window_name_property);

		if (rc == 0) {
			printf("XStringListToTextProperty - out of memory\n");
			exit(1);
		}

		//��ͼ����ת��ΪX����(Property)
		rc = XStringListToTextProperty(&icon_name, 
			1, &icon_name_property);
		if (rc == 0) {
			printf("XStringListToTextProperty - out of memory\n");
			exit(1);
		}

		//���ô�������ͼ����
		XSetWMName(display, win, &window_name_property);
		XSetWMIconName(display, win, &icon_name_property);

		//Ϊ���ڳߴ簵ʾ����ṹ
		win_size_hints = XAllocSizeHints();
		if (!win_size_hints) {
			printf("XAllocSizeHints - out of memory\n");
			exit(1);
		}
		//���ƴ��ڵ���С�ߴ�
		win_size_hints->flags = PSize | PMinSize | PMaxSize;
		win_size_hints->min_width = 320;
		win_size_hints->min_height = 200;
		win_size_hints->max_width = 640;
		win_size_hints->max_height = 480;
		win_size_hints->base_width = width;
		win_size_hints->base_height = height;

		//���ߴ��ڹ�����
		XSetWMNormalHints(display, win, win_size_hints);
		XFree(win_size_hints);

		//����λͼ
		icon_pixmap = XCreateBitmapFromData(display, 
			win, icon_bits, icon_width, icon_height);
		if (!icon_pixmap) {
			printf("XCreateBitmapFromData - error creating\n");
			exit(1);
		}

		//Ϊ���ڹ�������ʾ�����ڴ�
		win_hints = XAllocWMHints();
		if (!win_hints) {
			printf("XAllocWMHints - out of memory\n");
			exit(1);
		}

		//����ͼ���ͼ��, ״̬��λ��
		win_hints->flags = IconPixmapHint|StateHint|IconPositionHint;
		win_hints->icon_pixmap = icon_pixmap;
		win_hints->initial_state = IconicState;
		win_hints->icon_x = 0;
		win_hints->icon_y = 0;

		//���ٴ��ڹ�����
		XSetWMHints(display, win, win_hints);
		XFree(win_hints);


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
				width = report.xconfigure.width;
				height = report.xconfigure.height;
				break;

			//��������а���, �ͷ���Դ���˳�
			case ButtonPress:
			case KeyPress:
				XFreeGC(display, gc);
				exit(1);
			default:
				
				break;
			}
		}
	}

