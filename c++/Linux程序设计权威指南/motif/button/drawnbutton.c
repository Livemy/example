
	/* File: drawnbutton.c */
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/DrawnB.h>
	#include <X11/xpm.h>
	#include "smile.xpm"

	void callback(Widget w, XtPointer client_data,
		XmDrawnButtonCallbackStruct *cbs)
	{
		if(cbs->reason == XmCR_ACTIVATE)
			printf("drawn button activated.\n");
		else if(cbs->reason == XmCR_EXPOSE)
			printf("drawn button exposed.\n");
		else if(cbs->reason == XmCR_RESIZE)
			printf("drawn button resized.\n");
	}

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, drawn;
		Pixmap pixmap, mask;
		XpmAttributes attr;

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "DrawnButton", NULL, 0,
			&argc, argv, NULL, NULL);
		XtVaSetValues(toplevel,
			XmNborderWidth,		200,
			NULL);
		
		//����ͼ��
		XpmCreatePixmapFromData(XtDisplay(toplevel),
			XRootWindowOfScreen(XtScreen(toplevel)), 
			xpm_smile, &pixmap, NULL, NULL);

		//������ť
		n = 0;
		XtSetArg(args[n], XmNlabelType, XmPIXMAP);	n++;
		XtSetArg(args[n], XmNlabelPixmap, pixmap);	n++;
		drawn = XmCreateDrawnButton(toplevel, "drawnbutton", args, n);
		XtManageChild(drawn);

		//���ûص�
		XtAddCallback(drawn, XmNactivateCallback, 
			(XtCallbackProc)callback, NULL);
		XtAddCallback(drawn, XmNexposeCallback, 
			(XtCallbackProc)callback, NULL);
		XtAddCallback(drawn, XmNresizeCallback, 
			(XtCallbackProc)callback, NULL);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
