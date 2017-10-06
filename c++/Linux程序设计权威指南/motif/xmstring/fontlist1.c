
	/* File: fontlist1.c */
	//runit: XENVIRONMENT=FontList1.ad ./fontlist1
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/PushB.h>


	int main(int argc, char *argv[])
	{
		int n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, button;
		XmString label, label1, label2;

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "FontList1", NULL, 0,
			&argc, argv, NULL, NULL);

		//������ť�ϱ�ǩ���ַ���
		label1 = XmStringCreate("�����ַ���Testing", "small");
		label2 = XmStringCreate("������Testing", "large");
		label = XmStringConcat(label1, label2);

		n = 0;
		XtSetArg(args[n], XmNlabelString, label); 	n++;
		button = XmCreatePushButton(toplevel, "pushbutton", args, n);
		XtManageChild(button);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
