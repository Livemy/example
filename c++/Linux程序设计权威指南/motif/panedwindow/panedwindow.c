
	/* File: panedwindow.c */
	//Runit: XENVIRONMENT=PanedWindow.ad ./panedwindow
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/PanedW.h>
	#include <Xm/Text.h>

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, paned, text;

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "PanedWindow", NULL, 0,
			&argc, argv, NULL, NULL);

		//����paned
		paned  = XmCreatePanedWindow(toplevel, "paned", NULL, 0);
		XtManageChild(paned);

		//����text
		n = 0;
		XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);	n++;
		text = XmCreateScrolledText(paned, "text", args, n);
		XtManageChild(text);

		n = 0;
		XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);	n++;
		XtSetArg(args[n], XmNpaneMinimum, 80);			n++;
		XtSetArg(args[n], XmNpaneMaximum, 200);			n++;
		text = XmCreateScrolledText(paned, "text", args, n);
		XtManageChild(text);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}

