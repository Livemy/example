
	/* File: cursor.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>
	#include <X11/cursorfont.h>

	#include <stdio.h>

	void draw(Display *display, Window win, GC gc)
	{

		XDrawLine(display, win, gc, 0, 0, 200, 200);
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
		XEvent report;			//X �¼�
		GC gc;				//GC
		unsigned long valuemask = 0;
		XGCValues values;
		char *display_name = NULL;
		Colormap default_cmap;		//ȱʡ��ɫ��
		Cursor cursor;			//���
		Pixmap bitmap;			//����pixmap
		unsigned int bitmap_width, bitmap_height;
		int hotspot_x, hotspot_y;	//�����ȵ�λ��
		int rc;				//����ֵ
		XColor cursor_fg, cursor_bg;	//������ɫ

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

		//����λͼ
		rc = XReadBitmapFile(display, win,
                             "icon.xbm",		//λͼ�ļ���
                             &bitmap_width, &bitmap_height,//����λͼ�ߴ�
                             &bitmap,			//λͼͼ��
                             &hotspot_x, &hotspot_y);	//�ȵ�
		switch (rc) {
        		case BitmapOpenFailed:
				printf("Cannot open file icon.xbm\n");
				exit(1);
			case BitmapFileInvalid:
				printf("bitmap file is not valid.\n");
				exit(1);
			case BitmapNoMemory:
				printf("No enough memory.\n");
			exit(1);
		}

		//������ɫ
		rc = XAllocNamedColor(display, default_cmap, 
			"red", &cursor_fg, &cursor_fg);
		if (rc == 0) { 
			printf("Canot allocate color.\n");
			exit(1);
		}
		rc = XAllocNamedColor(display, default_cmap,
                            "white", &cursor_bg, &cursor_bg);
		if (rc == 0) {
			printf("Canot allocate color\n");
			exit(1);
		}

		//�������
		cursor = XCreatePixmapCursor(display, 
			bitmap, 	//�����״
			bitmap,		//������״
			&cursor_fg, 	//ǰ��ɫ
			&cursor_bg,	//����ɫ
			5, 4);		//�ȵ�λ��, �������Ϸ�



                //�� window ʹ�ù��
                XDefineCursor(display, win, cursor);

		XSync(display, False);

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
				draw(display, win, gc);
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

