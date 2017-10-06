
	/* File: scale.c */
	//Runit: XENVIRONMENT=Scale.ad ./scale
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/Scale.h>

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, scale;
		XmString str;

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "Scale", NULL, 0,
			&argc, argv, NULL, NULL);

		//����scale
		n = 0;
		XtSetArg(args[n], XmNshowValue, True); 		n++;
		XtSetArg(args[n], XmNminimum, 0); 		n++;
		XtSetArg(args[n], XmNmaximum, 200); 		n++;
		XtSetArg(args[n], XmNdecimalPoints, 2);		n++;
		XtSetArg(args[n], XmNvalue, 150); 		n++;
		scale = XmCreateScale(toplevel,"scale",args, n);
		XtManageChild(scale);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
