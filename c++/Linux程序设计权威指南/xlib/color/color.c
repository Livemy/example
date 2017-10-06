
	/* File: color.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>

	#include <stdio.h>

	void setcolor(Display *display, Colormap cmap, GC gc, char *name)
	{
		XColor color;

		//������ɫ��
		if(!XParseColor(display, cmap, name, &color)){
			printf("Cannot parse color name:%s\n", name);
			exit(1);
		}
		//������ɫ
		if(!XAllocColor(display, cmap, &color)){
			printf("Cannot allocate color\n");
			exit(1);
		}
		//����GC��ǰ��ɫ
		XSetForeground(display, gc, color.pixel);
	}


	void draw(Display *display, Colormap cmap, Window win, GC gc)
	{
		char *str1 = "Hello World!";
		
		setcolor(display, cmap, gc, "red");
		XDrawLine(display, win, gc, 20, 100, 300, 100);
		XDrawString(display, win, gc, 20, 100, str1, strlen(str1));

		setcolor(display, cmap, gc, "#0000FF");
		XFillRectangle(display, win, gc, 20, 200, 200, 150);
		
	}

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
		//width = display_width/2;
		//height = display_height/2;
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
		XSelectInput(display, win, 
			ExposureMask | KeyPressMask | 
			ButtonPressMask | StructureNotifyMask);

		//����GC
		gc = XCreateGC(display, win, valuemask, &values);


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
				draw(display, default_cmap, win, gc);
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
				XCloseDisplay(display);
				exit(1);
			default:
				
				break;
			}
		}
	}

