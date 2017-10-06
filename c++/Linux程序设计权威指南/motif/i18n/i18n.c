
	/* File: i18n.c */
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/PushB.h>

	void callback(Widget w, XtPointer client_data,
		XmPushButtonCallbackStruct *cbs)
	{
		printf("Hello World!\n");
	}

	int main(int argc, char *argv[])
	{
		int n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, button;
		//XmString label;

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "I18N", NULL, 0,
			&argc, argv, NULL, NULL);

		//������ť�ϱ�ǩ���ַ���
		//label = XmStringCreateSimple("Hello World!");
		n = 0;
		button = XmCreatePushButton(toplevel, "pushbutton", args, n);
		XtManageChild(button);
		//XmStringFree(label);

		//���ûص�����
		XtAddCallback(button, 
			XmNactivateCallback,	(XtCallbackProc)callback,
			NULL);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
