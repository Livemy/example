
	/* File: i18n-output.c */

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xos.h>
	#include <X11/Xatom.h>

	#include <stdio.h>
	#include <locale.h>



	int main(int argc, char **argv)
	{
		char *string = "�������ĺ�English�Ļ���ַ���!";
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

		//���弯
		XFontSet fontset;
		char **missing_charsets;
		int num_missing_charsets;
		char *default_string;
                wchar_t wcstr[80];		//���ַ���
		int num;			//ת�����Ŀ��ַ�������.


		//����locale	
		if((setlocale(LC_ALL, "")) == NULL){
			printf("cannot set locale\n");
			exit(1);
		}

		//�ж�X�Ƿ�֧��locale
		if(!XSupportsLocale()){
			printf("X does not support current locale\n");
			exit(1);
		}

		//����locale����
		if(XSetLocaleModifiers(NULL)){
			printf("Cannot set locale modifiers\n");
			exit(1);
		}
	
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

		//�������弯
		fontset = XCreateFontSet(display, 
			"8x16,-*-song-medium-r-normal--16-*-*-*-*-*-gb2312.1980-0",
			&missing_charsets, &num_missing_charsets,
			&default_string);

		if(num_missing_charsets > 0){
			int i;
			printf("Following charsets are missing:\n");
			for(i=0; i<num_missing_charsets; i++){
				printf("Missing %d: %s\n", 
					i, missing_charsets[i]);
			}
			printf("\nDefault string:%s\n", default_string);
			XFreeStringList(missing_charsets);
		}

                num = mbstowcs(wcstr, string, strlen(string));

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
				XmbDrawString(display, win, fontset, gc, 
					50, 100,
					string, strlen(string));
				XwcDrawString(display, win, fontset, gc,
					50, 140,
					(wchar_t *)wcstr, num);
	
				break;

			//���ڳߴ�ı�, ����ȡ�ô��ڵĿ�Ⱥ͸߶�
			case ConfigureNotify:
				width = report.xconfigure.width;
				height = report.xconfigure.height;
				break;

			//��������а���, �ͷ���Դ���˳�
			case ButtonPress:
			case KeyPress:
				XFreeFontSet(display, fontset);
				XFreeGC(display, gc);
				exit(1);
			default:
				
				break;
			}
		}
	}
