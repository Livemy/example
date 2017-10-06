
	/* File: pushbutton.c */
	#include <Xm/Xm.h>
	#include <Xm/PushB.h>


	void callback(Widget w, XtPointer client_data,
		XmPushButtonCallbackStruct *cbs)
	{
		if(cbs->reason == XmCR_ACTIVATE)
			printf("button activated.\n");
		else if(cbs->reason == XmCR_ARM)
			printf("button armed.\n");
		else if(cbs->reason == XmCR_DISARM)
			printf("button disarmed.\n");
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
		toplevel = XtVaAppInitialize(&app, "Demo", NULL, 0,
			&argc, argv, NULL, NULL);

		//������ť�ϱ�ǩ���ַ���
		label = XmStringCreateSimple("Arm/Disarm/Activate Test");

		n = 0;
		XtSetArg(args[n], XmNlabelString, label); 	n++;
		button = XmCreatePushButton(toplevel, "pushbutton", args, n);
		XtManageChild(button);

		XmStringFree(label);

		//���ûص�����
		XtAddCallback(button, 
			XmNactivateCallback,	callback,
			NULL);
		XtAddCallback(button, 
			XmNarmCallback,		callback,
			NULL);
		XtAddCallback(button, 
			XmNdisarmCallback,	callback,
			NULL);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
