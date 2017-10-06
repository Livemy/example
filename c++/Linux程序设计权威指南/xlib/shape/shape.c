
	/* File: shape.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>
	#include <X11/keysym.h>
	#include <X11/extensions/shape.h>
	#include <X11/cursorfont.h>
	#include <X11/xpm.h>


	#include <stdio.h>

	int main(int argc, char **argv)
	{
		int i;
		Display *display;
		int screen_num;
		Window win;			//����ID
		unsigned int width, height;	//���ڳߴ�
		unsigned int border_width = 4;	//�߽�հ�
		unsigned int display_width, display_height,display_depth;
		int count;
		XEvent report;
		GC gc;
		unsigned long valuemask = 0;
		XGCValues values;
		XSetWindowAttributes setwinattr;
		char *display_name = NULL;
		Colormap default_cmap;
		Visual *default_visual;
		XpmAttributes xpmattributes;	//xpm
		XVisualInfo *visual_info, vinfo_template;
		int nmatches;
		XColor color;
		Cursor cursor;
		Window root, child;
		int root_x, root_y, win_x, win_y, orig_x, orig_y;
		unsigned int mask_return;

		//pixmap
		Pixmap background_pixmap, shape_pixmap;
		char *pixmap, *mask;
		unsigned char *mask_bits;
		int xhot, yhot;

		// ��X ����������
		if ( (display=XOpenDisplay(display_name)) == NULL )
		{
			printf("Cannot connect to X server %s\n", 
					XDisplayName(display_name));
			exit(-1);
		}

		//���ȱʡ�� screen_num
		screen_num = DefaultScreen(display);

		//�����Ϣ
		display_width = DisplayWidth(display, screen_num);
		display_height = DisplayHeight(display, screen_num);
		display_depth = DefaultDepth(display, screen_num);

		//����ͼ��, ��ø߶ȺͿ��, �Խ�������
		XReadBitmapFileData("penguin.xbm", &width, &height,
			&mask_bits, &xhot, &yhot);

	
		//��������
		win = XCreateSimpleWindow(display, 	//display
			RootWindow(display,screen_num), //������
			0, 0, width, height, 		//λ�úʹ�С
			border_width, 			//�߽���
			BlackPixel(display,screen_num), //ǰ��ɫ
			WhitePixel(display,screen_num));//����ɫ

		//
		default_visual = DefaultVisual(display, screen_num);
		default_cmap = DefaultColormap(display, screen_num);
		//���Visual����
		vinfo_template.visualid = XVisualIDFromVisual(default_visual);
		visual_info = XGetVisualInfo(display, VisualIDMask,
                               &vinfo_template, &nmatches);

		xpmattributes.visual = default_visual;
		xpmattributes.colormap = default_cmap;
		xpmattributes.depth = display_depth;
		xpmattributes.valuemask = XpmVisual | XpmColormap | XpmDepth;
		XpmReadFileToPixmap(display, win, "penguin.xpm",
			&background_pixmap, &shape_pixmap,
			&xpmattributes);
		XFree(visual_info);

		setwinattr.background_pixmap = background_pixmap;
		setwinattr.override_redirect = True;
		cursor = XCreateFontCursor(display, XC_heart);
		setwinattr.cursor = cursor;
		valuemask = CWBackPixmap | CWOverrideRedirect | CWCursor;
		XChangeWindowAttributes(display, win, valuemask, &setwinattr);

		//����pixmap��Ϊͼ�񱳾�
		shape_pixmap = XCreateBitmapFromData(display, win, mask_bits,
			width, height);
		XShapeCombineMask(display, win, ShapeBounding, 
			0, 0, shape_pixmap, ShapeSet);
	
		//ѡ�񴰿ڸ���Ȥ���¼�����
		XSelectInput(display, win, 
			ExposureMask | KeyPressMask | ButtonPressMask |
			ButtonReleaseMask | StructureNotifyMask | 
			ButtonMotionMask | PointerMotionHintMask | 
			EnterWindowMask | LeaveWindowMask);

		//����GC
		//gc = XCreateGC(display, win, valuemask, &values);


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
				width = report.xconfigure.width;
				height = report.xconfigure.height;
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
					&mask_return);
				orig_x = root_x - win_x;
				orig_y = root_y - win_y;
				break;
			case MotionNotify:
				{
				int rx, ry, winx, winy;
				//ȡ��ָ������ڸ����ڵ�λ�úʹ��ڵ�λ��
				XQueryPointer(display,win,&root,&child,
                                        &rx, &ry, &winx, &winy, &mask_return);
				//�ƶ�����
				XMoveWindow(display, win, 
					rx - root_x + orig_x,
					ry - root_y + orig_y);
				}
				break;
			case ButtonRelease:
				break;
			case KeyPress:
				exit(0);
				break;
			default:
				break;
			}
		}
	}
