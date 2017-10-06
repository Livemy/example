
	/* File: imlib.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/extensions/shape.h>
	#include <Imlib.h>

	int main(int argc, char **argv)
	{
		Display *display;
		Window win;
		XSetWindowAttributes attr;

		//Imlib ������
		ImlibData *id;
		ImlibImage *im;
		Pixmap p,m;
		int w,h;
     
		display = XOpenDisplay(NULL);

		//��ʼ��
		id = Imlib_init(display);

		//����ͼ��
		im = Imlib_load_image(id, "penguin.xpm");

		//ȡ��ͼ��ĳߴ�
		w = im->rgb_width;
		h = im->rgb_height;

		//��������
		win = XCreateWindow(display,DefaultRootWindow(display),
			0,0,w,h,0,id->x.depth, InputOutput,
			id->x.visual,0,&attr);

		//ѡ���¼�
		XSelectInput(display,win,StructureNotifyMask);

		//�ڻ������ڻ�ͼ��
		Imlib_render(id, im, w, h);

		//��ȡͼ���ͼ������
		p = Imlib_move_image(id, im);

		//���ͼ���Ƿ�͸��������Ӧ����0
		m = Imlib_move_mask(id, im);

		//���ô��ڵı���ͼ��
		XSetWindowBackgroundPixmap(display, win, p);

		//�����ͼ������, ʹ������
		if (m) XShapeCombineMask(display, win,
			ShapeBounding, 0, 0, m, ShapeSet);

		//��ʾ����
		XMapWindow(display,win);

		//ͬ��X Server
		XSync(display,False);

		while(1){
			XEvent ev;
      
			XNextEvent(display,&ev);

			if (ev.type==ConfigureNotify){
				w = ev.xconfigure.width;
				h = ev.xconfigure.height;

				Imlib_render(id, im, w, h);
				Imlib_free_pixmap(id, p);
				p = Imlib_move_image(id, im);
				m = Imlib_move_mask(id, im);
				XSetWindowBackgroundPixmap(display, win, p);
				if (m) XShapeCombineMask(display, win,
					ShapeBounding, 0, 0, m, ShapeSet);
				XClearWindow(display,win);
				XSync(display,False);
			}
		}
	}
