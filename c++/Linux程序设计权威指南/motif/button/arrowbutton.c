
	/* File: arrowbutton.c */
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/ArrowB.h>

	void callback(Widget w, int n,
		XmAnyCallbackStruct *cbs)
	{
		printf("arrow button activated.\n");
	}

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, arrow;

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "ArrowButton", NULL, 0,
			&argc, argv, NULL, NULL);

		//������ѡ��ť�Ĳ������
		n = 0;
		XtSetArg(args[n], XmNarrowDirection, XmARROW_RIGHT);	n++;
		XtSetArg(args[n], XmNwidth, 100);		n++;
		XtSetArg(args[n], XmNheight, 100);		n++;
		arrow = XmCreateArrowButton(toplevel, "arrow", args, n);
		XtManageChild(arrow);

		//���ûص�
		XtAddCallback(arrow, XmNactivateCallback, 
			(XtCallbackProc)callback, NULL);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
