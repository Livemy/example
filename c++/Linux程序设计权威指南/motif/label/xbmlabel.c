
	/* File: xbmlabel.c */
	#include <Xm/Xm.h>
	#include <Xm/Label.h>

	int main(int argc, char *argv[])
	{
		int n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, xbmlabel;
		Pixmap pixmap;

		//������������
		toplevel = XtVaAppInitialize(&app, "Label", NULL, 0,
			&argc, argv, NULL, NULL);

		//������ť�ϵ�ͼ��
		pixmap = XmGetPixmap(XtScreen(toplevel), "opencjk.xbm", 
			BlackPixelOfScreen(XtScreen(toplevel)),
			WhitePixelOfScreen(XtScreen(toplevel)));
		if(pixmap == XmUNSPECIFIED_PIXMAP){
			printf("Pixmap Error loading\n");
			exit(1);
		}
		n = 0;
		XtSetArg(args[n], XmNlabelType, XmPIXMAP);	n++;
		XtSetArg(args[n], XmNlabelPixmap, pixmap);	n++;
		xbmlabel = XmCreateLabel(toplevel, "label", args, n);
		XtManageChild(xbmlabel);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
