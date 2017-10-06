
	/* File: dblclick.c */
	#include <Xm/Xm.h>
	#include <Xm/PushB.h>

	XtAppContext app;
	int timeout;

	void clicks(int click)
	{
		if(click) printf("double click.\n");
		else printf("single click.\n");
	}

	void callback(Widget w, XtPointer client_data,
		XmPushButtonCallbackStruct *cbs)
	{
		static XtIntervalId id;
		if(cbs->click_count == 1){
			id = XtAppAddTimeOut(app, timeout, 
				(XtTimerCallbackProc)clicks, False);
		} else if(cbs->click_count == 2){
			XtRemoveTimeOut(id);
			clicks(True);
		}
	}

	int main(int argc, char *argv[])
	{
		int n;
		Arg args[10];
		Widget toplevel, button;
		XmString label;
		void callback();

		//������������
		toplevel = XtVaAppInitialize(&app, "Demo", NULL, 0,
			&argc, argv, NULL, NULL);

		//���˫��ʱ��
		timeout = XtGetMultiClickTime(XtDisplay(toplevel));
		printf("double click time:%d ms\n", timeout);

		//������ť�ϱ�ǩ���ַ���
		label = XmStringCreateSimple("Double Click Test");
		n = 0;
		XtSetArg(args[n], XmNlabelString, label);	n++;
		button = XmCreatePushButton(toplevel, "pushbutton", args, n);
		XtManageChild(button);
		XmStringFree(label);

		//���ûص�����
		XtAddCallback(button, 
			XmNactivateCallback,	callback,
			(XtPointer)timeout);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
