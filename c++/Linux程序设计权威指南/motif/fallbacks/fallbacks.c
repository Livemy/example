
	/* File: helloworld.c */
	#include <Xm/Xm.h>
	#include <Xm/PushB.h>

	String fallbacks[] = {
		"HelloWorld*background: red",
		"HelloWorld*fontList: -*-times-medium-r-*--24-*",
		NULL,
	};

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
		XmString label;
		void callback();

		//������������
		toplevel = XtVaAppInitialize(&app, "HelloWorld", NULL, 0,
			&argc, argv, fallbacks, NULL);

		//������ť�ϱ�ǩ���ַ���
		label = XmStringCreateSimple("Hello World!");
		n = 0;
		XtSetArg(args[n], XmNlabelString, label); 	n++;
		button = XmCreatePushButton(toplevel, "pushbutton", args, n);
		XtManageChild(button);
		XmStringFree(label);

		//���ûص�����
		XtAddCallback(button, 
			XmNactivateCallback,	callback,
			NULL);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
