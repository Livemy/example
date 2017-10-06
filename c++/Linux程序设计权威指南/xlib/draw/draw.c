
	/* File: draw.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>

	#include <stdio.h>


	void draw(Display *display, Window win, GC gc, int width, int height)
	{
		int i, x, y;
                unsigned int line_width = 0;
                int line_style = LineSolid;
                int cap_style  = CapRound;
                int join_style = JoinRound;
		XPoint points[5] = {
			{400, 200},
			{600, 200},
			{450, 300},
			{500, 150},
			{550, 300}};
			

		//����
		for(i = 0; i< width; i+=3)
			XDrawPoint(display, win, gc, i, 10);

		//����
		y = 30;
		for(i = 0; i< 10; i+=2){
                	XSetLineAttributes(display, gc, i, line_style,
                        	cap_style, join_style);
			XDrawLine(display, win, gc, 10, y, width-10, y);
			y += 20;
		}

               	XSetLineAttributes(display, gc, 2, line_style,
                        	cap_style, join_style);
		//������
		XDrawRectangle(display, win, gc, 10, y, 50, 30);
		
		//������
		//�ο����
		XDrawRectangle(display, win, gc, 100, y, 200, 200);
		//0�ȵ�90�ȵ�Բ��
		XDrawArc(display, win, gc, 100, y, 200, 200, 0, 90*64);
		//���90�ȵ�120�ȵ�Բ��
		XFillArc(display, win, gc, 100, y, 200, 200, 90*64, 120*64);

		//�������
		XFillPolygon(display, win, gc, points, 5, 
			Complex, EvenOddRule);


	}

	int main(int argc, char **argv)
	{
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
	
				//д�ַ���
				draw(display, win, gc, width, height);
	
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

