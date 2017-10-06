
	/* File: label.c */
	#include <Xm/Xm.h>
	#include <Xm/Label.h>

	int main(int argc, char *argv[])
	{
		int n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, label;
		XmString str;

		//������������
		toplevel = XtVaAppInitialize(&app, "Label", NULL, 0,
			&argc, argv, NULL, NULL);

		//������ť�ϱ�ǩ���ַ���
		str = XmStringCreateLtoR("A Simple\n Label",
			XmFONTLIST_DEFAULT_TAG);
		n = 0;
		XtSetArg(args[n], XmNlabelString, str);		n++;
		label = XmCreateLabel(toplevel, "pushbutton", args, n);
		XtManageChild(label);

		XmStringFree(str);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
