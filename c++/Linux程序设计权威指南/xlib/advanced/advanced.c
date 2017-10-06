
	/* File: advanced.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>

	#include <stdio.h>

	//globals for simplicity
	int screen_num;
	Colormap cmap;
	GC gc;
	GC dimgc, lightgc, panelgc;

	typedef struct _button {
		Window  win;
		int x, y, w, h;
		char *label;
	} button;


	button buttons[4] = {
		{0, 0, 0, 0, 0, "black"},
		{0, 0, 0, 0, 0, "red"},
		{0, 0, 0, 0, 0, "green"},
		{0, 0, 0, 0, 0, "blue"}
	};

	void create_button(int n, Display *display, Window parent,
		int x, int y, int w, int h)
	{

		buttons[n].x = x;
		buttons[n].y = y;
		buttons[n].w = w;
		buttons[n].h = h;
		buttons[n].win = XCreateSimpleWindow(display, 	//display
			parent, 			//������
			x, y, w, h, 		//λ�úʹ�С
			0, 			//�߽���
			BlackPixel(display,DefaultScreen(display)), //ǰ��ɫ
			WhitePixel(display,DefaultScreen(display)));//����ɫ
		//ѡ�񴰿ڸ���Ȥ���¼�����
		XSelectInput(display, buttons[n].win, 
			ExposureMask | 
			ButtonPressMask |		//����
			ButtonReleaseMask |		//̧��
			ButtonMotionMask | 		//�ƶ�
			KeyPressMask |
			StructureNotifyMask);
		XMapWindow(display, buttons[n].win);

        }

	void wait_button_release(Display *display)
	{
        	XEvent ev;
        	XGrabServer(display);
        	while(1){
                	XNextEvent(display, &ev);
                	switch  (ev.type) {
                	        case ButtonRelease:
                                	XUngrabServer(display);
                                	return;
                        	default:
                                	break;
                	}
        	}
	}

	void process_button(int n, Display *display)
	{
		XColor color;
		int w = buttons[n].w;
		int h = buttons[n].h;

		//border
		XDrawLine(display, buttons[n].win, dimgc, 0, 0, w, 0);
		XDrawLine(display, buttons[n].win, dimgc, 0, 1, w, 1);
		XDrawLine(display, buttons[n].win, dimgc, 0, 1, 0, h-1);
		XDrawLine(display, buttons[n].win, dimgc, 1, 1, 1, h-2);
		XDrawLine(display, buttons[n].win, lightgc, 0, h-1, w-1, h-1);
		XDrawLine(display, buttons[n].win, lightgc, 1, h-2, w-2, h-2);
		XDrawLine(display, buttons[n].win, lightgc, w-1, 0, w-1, h-1);
		XDrawLine(display, buttons[n].win, lightgc, w-2, 1, w-2, h-1);

		wait_button_release(display);

		//border
		XDrawLine(display, buttons[n].win, lightgc, 0, 0, w, 0);
		XDrawLine(display, buttons[n].win, lightgc, 0, 1, w, 1);
		XDrawLine(display, buttons[n].win, lightgc, 0, 1, 0, h-1);
		XDrawLine(display, buttons[n].win, lightgc, 1, 1, 1, h-2);
		XDrawLine(display, buttons[n].win, dimgc, 0, h-1, w-1, h-1);
		XDrawLine(display, buttons[n].win, dimgc, 1, h-2, w-2, h-2);
		XDrawLine(display, buttons[n].win, dimgc, w-1, 0, w-1, h-1);
		XDrawLine(display, buttons[n].win, dimgc, w-2, 1, w-2, h-1);

		//set color
		if(!XParseColor(display, cmap, buttons[n].label, &color)){
                        printf("Cannot parse color name\n");
                        exit(1);
                }
                if(!XAllocColor(display, cmap, &color)){
                        printf("Cannot allocate color\n");
                        exit(1);
                }
                XSetForeground(display, gc, color.pixel);
	}

	void button_flush(int n, Display *display)
	{
		int w = buttons[n].w;
		int h = buttons[n].h;

		//fill
		XFillRectangle(display, buttons[n].win, panelgc, 0, 0, w, h);
		//border
		XDrawLine(display, buttons[n].win, lightgc, 0, 0, w, 0);
		XDrawLine(display, buttons[n].win, lightgc, 0, 1, w, 1);
		XDrawLine(display, buttons[n].win, lightgc, 0, 1, 0, h-1);
		XDrawLine(display, buttons[n].win, lightgc, 1, 1, 1, h-2);
		XDrawLine(display, buttons[n].win, dimgc, 0, h-1, w-1, h-1);
		XDrawLine(display, buttons[n].win, dimgc, 1, h-2, w-2, h-2);
		XDrawLine(display, buttons[n].win, dimgc, w-1, 0, w-1, h-1);
		XDrawLine(display, buttons[n].win, dimgc, w-2, 1, w-2, h-1);
		//label
		XDrawString(display, buttons[n].win, gc, 10, 16,
			buttons[n].label, strlen(buttons[n].label));
	}

	GC create_gc(Display *display, Window win, char *rgb)
	{
		XColor color;
		GC mygc;
		unsigned long valuemask = 0;
		XGCValues values;

		mygc = XCreateGC(display, win, valuemask, &values);

		if(!XParseColor(display, cmap, rgb, &color)){
                        printf("Cannot parse color name:%s\n", rgb);
                        exit(1);
                }
                if(!XAllocColor(display, cmap, &color)){
                        printf("Cannot allocate color\n");
                        exit(1);
                }
                XSetForeground(display, mygc, color.pixel);

		return mygc;
	}

	int main(int argc, char **argv)
	{
		Display *display;
		Window win;			//����ID
		Window win_draw;
		unsigned int width, height;	//���ڳߴ�
		unsigned int border_width = 4;	//�߽�հ�
		unsigned int display_width, display_height;//��Ļ�ߴ�
		int i;
		int count;
		XEvent report;
		unsigned long valuemask = 0;
		XGCValues values;
		char *getenv();
		XColor color;

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
		cmap = DefaultColormap(display, screen_num);
	
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

		panelgc = create_gc(display, win, "#C0C0C0");
		dimgc = create_gc(display, win, "#666666");
		lightgc = create_gc(display, win, "#F5F5F5");

		//������ͼ����
		win_draw = XCreateSimpleWindow(display, //display
			win, 				//������
			10, 10, width - 140,height - 40,//λ�úʹ�С
			border_width, 			//�߽���
			BlackPixel(display,screen_num), //ǰ��ɫ
			WhitePixel(display,screen_num));//����ɫ
		//ѡ�񴰿ڸ���Ȥ���¼�����
		XSelectInput(display, win_draw, 
			ExposureMask | 
			ButtonPressMask |		//����
			ButtonReleaseMask |		//̧��
			ButtonMotionMask | 		//�ƶ�
			KeyPressMask |
			StructureNotifyMask);

		//������ť����
		for(i=0; i<4; i++)
			create_button(i, display, win,
				width - 100, i * 30 + 30, 80, 20);


		//��ʾ����
		XMapWindow(display, win);
		XMapWindow(display, win_draw);

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
				for(i=0;i<4;i++) button_flush(i, display);
				break;

			//���ڳߴ�ı�, ����ȡ�ô��ڵĿ�Ⱥ͸߶�
			case ConfigureNotify:
				width = report.xconfigure.width;
				height = report.xconfigure.height;
				break;

			//��������ʼ��ͼ.
			case ButtonPress:
				if(report.xbutton.button == Button1 &&
				   report.xbutton.window == win_draw){
					x1 = report.xbutton.x;
					y1 = report.xbutton.y;
					XDrawPoint(display, win_draw, gc,x1,y1);
				} else if(report.xbutton.button == Button1 &&
                                    report.xbutton.window == buttons[0].win){
					process_button(0, display);
				} else if(report.xbutton.button == Button1 &&
                                    report.xbutton.window == buttons[1].win){
					process_button(1, display);
				} else if(report.xbutton.button == Button1 &&
                                    report.xbutton.window == buttons[2].win){
					process_button(2, display);
				} else if(report.xbutton.button == Button1 &&
                                    report.xbutton.window == buttons[3].win){
					process_button(3, display);
				} else if(report.xbutton.button == Button3){
					XFreeGC(display, gc);
					exit(1);
				}
				break;
			case ButtonRelease:
				if(report.xbutton.button == Button1 &&
				   report.xbutton.window == win_draw){
					x2 = report.xbutton.x;
					y2 = report.xbutton.y;
					XDrawLine(display, win_draw, gc, 
						x1, y1, x2, y2);
				}
				break;
			case MotionNotify:
				if(report.xmotion.state & Button1Mask &&
				   report.xmotion.window == win_draw){
					x2 = report.xmotion.x;
					y2 = report.xmotion.y;
					XDrawLine(display, win_draw, gc,
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

