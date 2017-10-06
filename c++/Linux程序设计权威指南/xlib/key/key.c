
	/* File: key.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>
	#include <X11/keysym.h>

	#include <stdio.h>

	char *getenv();

	void draw(Display *display, Window win, GC gc, int w, int h,
		int count, int code, unsigned int state, char *str, char *sym)
	{
		char buf[128];
		XClearArea(display, win, 0, 0, w, h, False);

		sprintf(buf, "Keycode: %d", code);
		XDrawImageString(display, win, gc, 20, 100, buf, strlen(buf));

		sprintf(buf, "XLookupString return  count: %d", count);
		XDrawImageString(display, win, gc, 20, 140, buf, strlen(buf));

		sprintf(buf, "XLookupString return keysym: %s", sym);
		XDrawImageString(display, win, gc, 20, 180, buf, strlen(buf));

		//state
		sprintf(buf, "Modifiers: Control: %s Shift: %s Alt: %s",
			(state & ControlMask) ? "*" : " ",
			(state & ShiftMask) ? "*" : " ",
			(state & Mod1Mask) ? "*" : " ");
		XDrawImageString(display, win, gc, 20, 220, buf, strlen(buf));


		if(count > 0){
			sprintf(buf, "XLookupString return buffer: %s", str);
			XDrawImageString(display, win, gc, 20, 260, 
				buf, strlen(buf));
		}

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
		XEvent report;
		GC gc;
		unsigned long valuemask = 0;
		XGCValues values;

		//�������¼��ı���
		char buffer[1024] = "";
		KeySym keysym;			//��������
		int count;			//���ص�buffer�����ݵĳ���
		XComposeStatus compose;		//Compose״̬

		// ��X ����������
		if ( (display=XOpenDisplay(getenv("DISPLAY"))) == NULL ){
			printf("Cannot connect to X server\n");
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
			ExposureMask | KeyPressMask | 
			ButtonPressMask | StructureNotifyMask);

		//����GC
		//gc = XCreateGC(display, win, valuemask, &values);
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

			//�����¼�
			case KeyPress:
				//���� keysym, ���ؼ���ASCIIֵ
				count = XLookupString(&report.xkey,buffer, 1024,
					&keysym, &compose);
				//��ʾ��Ϣ
				draw(display, win, gc, width, height,
					count, report.xkey.keycode, 
					report.xkey.state,
					buffer, XKeysymToString(keysym));
				//һЩ����Ȥ�ļ�
				if(keysym == XK_Return)
					printf("KeySym:XK_Return\n");
				else if(keysym == XK_Up)
					printf("KeySym:XK_Up\n");
				else if(keysym == XK_Down)
					printf("KeySym:XK_Down\n");
				else if(keysym == XK_Left)
					printf("KeySym:XK_Left\n");
				else if(keysym == XK_Right)
					printf("KeySym:XK_Right\n");
				else if(keysym >= XK_KP_0 &&
					keysym <= XK_KP_9)
					printf("Keypad: 0-9\n");
				else if(keysym >= XK_F1 &&
					keysym <= XK_F12)
					printf("Function keys\n"); 
				else if(keysym == XK_BackSpace)
					printf("KeySym: XK_BackSpace\n");
				else if(keysym == XK_Delete)
					printf("KeySym: XK_Delete\n");
				else if(keysym >= XK_space &&
					keysym <= XK_asciitilde)
					printf("Normal keys\n");
				else {
					XBell(display, 100);
					printf("I am not interested in it\n");
				}

				break;


			//���ڳߴ�ı�, ����ȡ�ô��ڵĿ�Ⱥ͸߶�
			case ConfigureNotify:
				width = report.xconfigure.width;
				height = report.xconfigure.height;
				break;

			//��������а���, �ͷ���Դ���˳�
			case ButtonPress:
				XFreeGC(display, gc);
				exit(1);
			default:
				
				break;
			}
		}
	}

