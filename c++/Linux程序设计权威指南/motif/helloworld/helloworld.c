
	/* File: helloworld.c */
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
		Arg args[3];
		XtAppContext app;
		Widget toplevel, button;
		XmString label;


		//������������
		toplevel = XtVaAppInitialize(&app, "HelloWorld", NULL, 0,
			&argc, argv, NULL, NULL);

		//������ť�ϱ�ǩ���ַ���
		label = XmStringCreateSimple("Hello World!");

		//������ť
		n = 0;
		XtSetArg(args[n], XmNlabelString, label);       n++;
		button = XmCreatePushButton(toplevel, "pushbutton", args, n);
		XtManageChild(button);
		XmStringFree(label);

		//���ûص�����
		XtAddCallback(button, 
			XmNactivateCallback,	(XtCallbackProc)callback,
			NULL);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
