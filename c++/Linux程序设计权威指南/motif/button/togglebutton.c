
	/* File: togglebutton.c */
	#include <Xm/Xm.h>
	#include <Xm/ToggleB.h>


	void callback(Widget w, XtPointer client_data,
		XmAnyCallbackStruct *cbs)
	{
		Boolean status;

		status = XmToggleButtonGetState(w);
		/*
		XtVaGetValues(w,
			XmNset, 	&status,
			NULL);
		*/

		if(status) printf("Toggle is on\n");
		else printf("Toggle is off\n"); 
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
		label = XmStringCreateSimple("ToggleButton Test");
		n = 0;
		XtSetArg(args[n], XmNlabelString, label);	n++;
		button = XmCreateToggleButton(toplevel, "Demo", args, n);
		XtManageChild(button);

		XmStringFree(label);

		//�Ѱ�ťȱʡ��Ϊ����״̬
		XmToggleButtonSetState(button, True, False);
		/*
		XtVaSetValues(button,
			XmNset,		True,
			NULL);
		*/

		//���ûص�����
		XtAddCallback(button,
			XmNvalueChangedCallback,callback,
			NULL);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
