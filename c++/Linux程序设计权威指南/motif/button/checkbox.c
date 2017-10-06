
	/* File: checkbox.c */
	// Runit: XENVIRONMENT=CheckBox.ad ./checkbox
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/RowColumn.h>
	#include <Xm/ToggleB.h>
	#include <Xm/PushB.h>
	#include <Xm/Separator.h>

	Widget buttons[6];

	char *lists[] = {
		"����",	"���", "��ʾ��",
		"�ڴ�", "Ӳ��", "��Դ"
	};

	void checkit(Widget w, int n,
		XmAnyCallbackStruct *cbs)
	{
		int i;
		Boolean status;
		printf("Final results:\n");
		for(i=0; i<6; i++){
			status = XmToggleButtonGetState(buttons[i]);
			printf("button %s is %s\n",
				XtName(buttons[i]), status ? "on" : "off");
		}
	}
	void toggle(Widget w, int n,
		XmToggleButtonCallbackStruct *cbs)
	{
		printf("button %d is %s\n", n, cbs->set ? "on" : "off");
	}

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, rowcol, checkbox, w;
		XmString label;
		void callback();

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "CheckBox", NULL, 0,
			&argc, argv, NULL, NULL);

		//�����������
		rowcol = XmCreateRowColumn(toplevel, "rowcol", NULL, 0);
		XtManageChild(rowcol);

		//������ѡ��ť�Ĳ������
		n = 0;
		XtSetArg(args[n], XmNpacking, XmPACK_COLUMN);	n++;
		XtSetArg(args[n], XmNnumColumns, 2);		n++;
		checkbox = XmCreateRowColumn(rowcol, "rowcol", args, n);
		XtManageChild(checkbox);

		//������ť
		for(i=0; i<XtNumber(lists); i++){
			buttons[i] = XmCreateToggleButton(checkbox, lists[i],
				NULL, 0);
			XtManageChild(buttons[i]);
			XtAddCallback(buttons[i], XmNvalueChangedCallback, 
				(XtCallbackProc)toggle, (XtPointer)i);
		}

		//���ð�ť�ĳ�ʼ״̬
		XmToggleButtonSetState(buttons[2], True, False);
		XmToggleButtonSetState(buttons[4], True, False);

		//�����ָ���
		w = XmCreateSeparator(rowcol, "separator", NULL, 0);
		XtManageChild(w);

		//����һ����ͨ��ť
		w = XmCreatePushButton(rowcol, "��鰴ť����", NULL, 0);
		XtManageChild(w);
		XtAddCallback(w, XmNactivateCallback, 
			(XtCallbackProc)checkit, NULL);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
