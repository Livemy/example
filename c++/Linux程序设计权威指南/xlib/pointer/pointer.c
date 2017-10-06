
	/* File: pointer.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>

	#include <stdio.h>

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
		char *getenv();

		//draw
		int x1, y1, x2, y2;
	
		// ��X ����������
		if ( (display=XOpenDisplay(getenv("DISPLAY"))) == NULL ){
			printf("Cannot connect to X server %s");
			exit(-1);
		}

		//���ȱʡ�� screen_num
		screen_num = DefaultScreen(display);

		//�����Ļ�Ŀ�Ⱥ͸߶�
		display_width = DisplayWidth(display, screen_num);
		display_height = DisplayHeight(display, screen_num);
	
		//ָ�����������ڵĿ�Ⱥ͸߶�
		width = display_width/2;
		height = display_height/2;
	
		//��������
		win = XCreateSimpleWindow(display, 	//display
			RootWindow(display,screen_num), //������
			0, 0, width, height, 		//λ�úʹ�С
			border_width, 			//�߽���
			BlackPixel(display,screen_num), //ǰ��ɫ
			WhitePixel(display,screen_num));//����ɫ
	
		//ѡ�񴰿ڸ���Ȥ���¼�����
		XSelectInput(display, win, 
			ExposureMask | 
			ButtonPressMask |		//����
			ButtonReleaseMask |		//̧��
			ButtonMotionMask | 		//�ƶ�
			KeyPressMask |
			StructureNotifyMask);

		//����GC
		gc = XCreateGC(display, win, valuemask, &values);
               	XSetLineAttributes(display, gc, 3, 
			LineSolid, CapRound, JoinRound);

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
				XClearArea(display, win, 0, 0, 
					width, height, False);
				break;

			//���ڳߴ�ı�, ����ȡ�ô��ڵĿ�Ⱥ͸߶�
			case ConfigureNotify:
				width = report.xconfigure.width;
				height = report.xconfigure.height;
				break;

			//��������ʼ��ͼ.
			case ButtonPress:
				if(report.xbutton.button == Button1){
					x1 = report.xbutton.x;
					y1 = report.xbutton.y;
					XDrawPoint(display, win, gc, x1, y1);
				} else if(report.xbutton.button == Button3){
					XFreeGC(display, gc);
					exit(1);
				}
				break;
			case ButtonRelease:
				if(report.xbutton.button == Button1){
					x2 = report.xbutton.x;
					y2 = report.xbutton.y;
					XDrawLine(display, win, gc, 
						x1, y1, x2, y2);
				}
				break;
			case MotionNotify:
				if(report.xmotion.state & Button1Mask){
					x2 = report.xmotion.x;
					y2 = report.xmotion.y;
					XDrawLine(display, win, gc,
						x1, y1, x2, y2);
					x1 = x2;
					y1 = y2;
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

