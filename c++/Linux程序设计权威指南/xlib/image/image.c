
	/* File: image.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>

	#include <stdio.h>

	#define COLORS  8
	#define IMAGE_WIDTH   320
	#define IMAGE_HEIGHT   200
	#define MAXDEPTH 200

	typedef struct {
		double real, imag;
	} complex;

	static void complexInit(complex *z, double r, double i)
	{
		z->real = r; z->imag = i;
		return;
	}

	static void complexAdd(complex *z, complex u)
	{
		z->real += u.real;
		z->imag += u.imag;
	}
	static void complexSub(complex *z, complex u)
	{
		z->real -= u.real;
		z->imag -= u.imag;
	}
	static void complexMult(complex *z, complex u)
	{
		double tmp;
		tmp = z->real*u.real - z->imag*u.imag;
		z->imag = z->real*u.imag + z->imag*u.real;
		z->real = tmp;
	}

	static double complexReal(complex *z)
	{
		return z->real;
	}

	static double complexImag(complex *z)
	{
		return z->imag;
	}

	static void complexPrint(complex *z)
	{
		printf("%.2g+%.2gi", complexReal(z), complexImag(z));
	}

	static double complexAbsSquare(complex *z)
	{
		return z->real*z->real+ z->imag*z->imag;
	}


	static int julia(complex z, complex c)
	{
		int n;
		/* f(z) := z*z - c */

		for(n=0; n<MAXDEPTH; n++){
			complexMult(&z, z);
			complexSub(&z, c);
			/* if(complexAbs(&z)>2.0) */
			if(complexAbsSquare(&z)>4.0)
				return n;
		}

		return 0;
	}


	void draw(Display *display, Window win, GC gc,
		XImage *img, XColor rgb[], int colors)
	{
		complex initial, point;
		int i, j;
		int w = IMAGE_WIDTH, h = IMAGE_HEIGHT;
		complexInit(&initial, 0.0, 0.0);
		printf("Rendering [%3d,%3d] fractal, please wait.\n", w, h);

		for(j=0; j<h; j++)
		for(i=0; i<w; i++) {
			int c;
			complexInit(&point, 2.5*(i-w/3)/w, 2.1*(j-h/2)/h);
			c = julia(initial, point);
			if(i%25==0) {
				printf("[%4d,%4d] = %4d\r", i, j, c);
			}
			img->f.put_pixel(img, i, j, rgb[c%colors].pixel);
		}
	}

	void reverse_image(XImage *img)
	{
		unsigned long pixelvalue1, pixelvalue2;
		int y;
		int left_x, right_x;

		for (left_x=0 ; left_x<IMAGE_WIDTH/2 ; left_x++){
			for (y=0 ; y<IMAGE_HEIGHT ; y++){
                		pixelvalue1 = XGetPixel(img, left_x, y);
				right_x = IMAGE_WIDTH - left_x;
				if (left_x != right_x){
					pixelvalue2 = XGetPixel(img,right_x, y);
					XPutPixel(img, left_x, y, pixelvalue2);
				}
				XPutPixel(img, right_x, y, pixelvalue1);
			}
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
		int count;
		XEvent report;
		char *display_name = NULL;
		GC gc;
		//��ɫ��
		Colormap default_cmap;
		XColor rgb[COLORS];
		//ͼ��
		XImage *img, *cimg = NULL;	//ͼ�����������ͼ��
		XVisualInfo vis, *vlist;	//Visual ��Ϣ
		Visual *visual;			//Visual
		int depth;
		int match;
		int temp;
		int w, h;
		unsigned char *bit_data, *bitp, *datap;
		unsigned char *tmpdata;
		int bytes_per_line;		//ÿ���ֽ���

		// ��X ����������
		if ( (display=XOpenDisplay(display_name)) == NULL )
		{
			printf("Cannot connect to X server %s\n", 
					XDisplayName(display_name));
			exit(-1);
		}

		//���ȱʡ�� screen_num
		screen_num = DefaultScreen(display);
		//����GC
		gc = DefaultGC(display, screen_num);
		//�����ɫ���
		depth = DefaultDepthOfScreen(DefaultScreenOfDisplay(display));
		//�����Ļ�Ŀ�Ⱥ͸߶�
		display_width = DisplayWidth(display, screen_num);
		display_height = DisplayHeight(display, screen_num);

		//��ȡȱʡ����ɫ��
		default_cmap = DefaultColormap(display, screen_num);

		//���Visual��Ϣ
		vis.screen = screen_num;
		vlist = XGetVisualInfo(display, 
			VisualScreenMask, 		//����
			&vis, 				//����visual
			&match);			//�����ϵ�Visual�ṹ
		if(!vlist){
			printf("No matched visuals\n");
			exit(1);
		}
		vis = vlist[0];
		XFree(vlist);

		//�ж���ɫ���С�Ƿ����
		if(vis.colormap_size<COLORS){
			printf("Colormap is too small.\n");
			exit(1);
		}

		//���ûҶȼ���ɫ��
		for(i=0; i<COLORS; i++){
			rgb[i].red = 65535 * (1.0-1.0*i/COLORS);
			rgb[i].green = 65535 * (1.0-1.0*i/COLORS);;
			rgb[i].blue = 65535 * (1.0*i/COLORS);;
			rgb[i].flags = DoRed|DoGreen|DoBlue;
		}
		//����class, �ض�����ɫ
		if(vis.class%2==1){
			unsigned long color[COLORS];
			//������ɫ��Ԫ
			if(XAllocColorCells(display, default_cmap, 1, NULL, 0,
				color, COLORS)==0){
				printf("Cannot allocate enough colors cells.\n");
				exit(1);
			}
			//�޸���ɫ��Ԫ
			for(i=0; i<COLORS; i++) rgb[i].pixel = color[i];
			XStoreColors(display, default_cmap, rgb, COLORS);
		} else if(vis.class == TrueColor){
			//������ɫ
			for(i=0; i<COLORS; i++)
				XAllocColor(display, default_cmap, rgb + i);
		} else {
			printf("No content with visual class %d.\n",
				vis.class);
			exit(1);
		}

		switch(depth){
		case 6:
		case 8:
			img = XCreateImage(display,
				vis.visual,
				depth,
				ZPixmap,
				0,
				(char *)malloc(IMAGE_WIDTH*IMAGE_HEIGHT),
				IMAGE_WIDTH, IMAGE_HEIGHT,
				8,
				IMAGE_WIDTH);
			break;
		case 16:
                	bit_data = (unsigned char *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT * 2);
			img = XCreateImage(display, 
				vis.visual, 
				vis.depth, 
				ZPixmap, 
				0, 
				bit_data, 
				IMAGE_WIDTH, IMAGE_HEIGHT,
				16, 
				0);
			break;
		case 24:
			bit_data = (unsigned char *)malloc(IMAGE_WIDTH * IMAGE_HEIGHT * 4);
			img = XCreateImage(display,
				vis.visual,
				depth,
				ZPixmap,
				0,
				(char *)bit_data,
				IMAGE_WIDTH, IMAGE_HEIGHT, 
				32, 
				0);
			break;
		default:
			exit(1);
		}
		//ָ�����������ڵĿ�Ⱥ͸߶�
		//width = display_width/2;
		//height = display_height/2;
		width = 600;
		height = 400;

		//��������
		draw(display, win, gc, img, rgb, COLORS);



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


		//��ʾ����
		XMapWindow(display, win);

		//��ͼ��ŵ�������
		XPutImage(display, win, gc, img, 0, 0, 0, 0,
			IMAGE_WIDTH,IMAGE_HEIGHT);

		//ȡ��ͼ��
		cimg = XGetImage(display, win, 0, 0, 
			IMAGE_WIDTH, IMAGE_HEIGHT, AllPlanes, ZPixmap);

		reverse_image(cimg);


		//�����¼�ѭ��
		while (1)  {

			//ȡ�ö����е��¼�
			XNextEvent(display, &report);
			switch  (report.type) {

			//�ع��¼�, ����Ӧ�ػ�
			case Expose:
				//ȡ�����һ���ع��¼�
				if (report.xexpose.count != 0) break;

				//��ͼ��
				XPutImage(display, win, gc, img, 
					0, 0, 0, 0, IMAGE_WIDTH,IMAGE_HEIGHT);

				//����ͼ��
				XPutImage(display, win, gc, cimg, 
					0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, 
					IMAGE_WIDTH, IMAGE_HEIGHT);

				break;

			//���ڳߴ�ı�, ����ȡ�ô��ڵĿ�Ⱥ͸߶�
			case ConfigureNotify:
				width = report.xconfigure.width;
				height = report.xconfigure.height;
				break;

			//��������а���, �ͷ���Դ���˳�
			case ButtonPress:
			case KeyPress:
				XDestroyImage(img);
				XDestroyImage(cimg);
				XFreeGC(display, gc);
				//XCloseDisplay(display);
				exit(1);
			default:
				
				break;
			}
		}
	}

