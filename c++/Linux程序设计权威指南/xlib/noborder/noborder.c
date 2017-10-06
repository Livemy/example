
	/* File: noborder.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>
	#include <X11/keysym.h>

	#include <stdio.h>


	void draw(Display *display, Window win, GC gc)
	{
		char *msg1 = "Buttons to move window";
		char *msg2 = "Arrow keys to resize window";
		char *msg3 = "Escape key to exit";

		XDrawString(display, win, gc, 20, 60, msg1, strlen(msg1));
		XDrawString(display, win, gc, 20, 80, msg2, strlen(msg2));
		XDrawString(display, win, gc, 20, 140, msg3, strlen(msg3));
	}

	int main(int argc, char **argv)
	{
		static char *string = "Hello World!";
		Display *display;
		int screen_num;
		Window win;			//����ID
		unsigned int width, height;	//���ڳߴ�
		unsigned int border_width = 0;	//�߽�հ�
		unsigned int display_width, display_height;//��Ļ�ߴ�
		int count;
		XEvent report;
		GC gc;
		unsigned long valuemask = 0;
		XGCValues values;
		char *display_name = NULL;
		//attribute vars
	        XSizeHints size_hints;
		XSetWindowAttributes attrib;
		unsigned long attribmask;
		//moving window
		Window root, child;
		unsigned int mask;
		int root_x, root_y, win_x, win_y, orig_x, orig_y;
	
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
			100, 100, width, height, 		//λ�úʹ�С
			border_width, 			//�߽���
			BlackPixel(display,screen_num), //ǰ��ɫ
			WhitePixel(display,screen_num));//����ɫ

		//��������
		attrib.override_redirect = True;
		attribmask = CWOverrideRedirect;
		XChangeWindowAttributes(display, win, attribmask, &attrib);


	
		//ѡ�񴰿ڸ���Ȥ���¼�����
		XSelectInput(display, win, 
			ExposureMask | KeyPressMask | 
			ButtonMotionMask | ButtonPressMask | ButtonReleaseMask
			| StructureNotifyMask);

		//����GC
		gc = DefaultGC(display, screen_num);

		//��ʾ����
		XMapWindow(display, win);

		//����Ϊ���̾۽�����
		XSetInputFocus(display, win, False, CurrentTime);

		//�����¼�ѭ��
		while (1)  {

			//ȡ�ö����е��¼�
			XNextEvent(display, &report);
			switch  (report.type) {

			//�ع��¼�, ����Ӧ�ػ�
			case Expose:
				//ȡ�����һ���ع��¼�
				if (report.xexpose.count != 0) break;
				draw(display, win, gc);
				break;

			//���ڳߴ�ı�, ����ȡ�ô��ڵĿ�Ⱥ͸߶�
			case ConfigureNotify:
				break;

			//ȡ��λ��
			case ButtonPress:
				//�Ѵ��ڸ��������Ϸ�
				XRaiseWindow(display, win);
				//���ü��̾۽�
				XSetInputFocus(display, win, False,CurrentTime);
				//ȡ��ָ������ڸ����ڵ�λ�úʹ��ڵ�λ��
				XQueryPointer(display,win,&root,&child,
					&root_x, &root_y, &win_x, &win_y,
					&mask);
				orig_x = root_x - win_x;
				orig_y = root_y - win_y;
				break;
			case MotionNotify:
				{
				int rx, ry, winx, winy;
				//ȡ��ָ������ڸ����ڵ�λ�úʹ��ڵ�λ��
				XQueryPointer(display,win,&root,&child,
                                        &rx, &ry, &winx, &winy, &mask);
				//�ƶ�����
				XMoveWindow(display, win, 
					rx - root_x + orig_x,
					ry - root_y + orig_y);
				}
				break;
			case ButtonRelease:
				break;
			case KeyPress:
				{
				char buffer[1024] = "";
				KeySym keysym;     //��������
				int count;         //���ص�buffer�����ݵĳ���
				XComposeStatus compose; //Compose״̬
                                XWindowAttributes xa;
                                unsigned int w, h;

                                XGetWindowAttributes(display,win,&xa);
				w = xa.width; h = xa.height;

				//��ͷ�ƶ�����
				count = XLookupString(&report.xkey,buffer, 1024,
                                        &keysym, &compose);
				if(keysym == XK_Up){
					if(h > 10) h -= 2;
					//�ı䴰�ڴ�С
					XResizeWindow(display, win, w, h);
				} else if(keysym == XK_Down) {
					h += 2;
					XResizeWindow(display, win, w, h);
				} else if(keysym == XK_Left) {
					if(w > 10) w -= 2;
					XResizeWindow(display, win, w, h);
				} else if(keysym == XK_Right) {
					w += 2;
					XResizeWindow(display, win, w, h);
				} else if(keysym == XK_Escape) {
					exit(0);
				}
				}
				break;
			default:
				
				break;
			}
		}
	}
