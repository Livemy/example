
	/* File: radiobox.c */
	//runit XENVIRONMENT=RadioBox.ad ./radiobox
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/RowColumn.h>
	#include <Xm/ToggleB.h>

	char *lists[] = {
		"����", "���", "��ʾ��"
	};

	void toggle(Widget w, int n,
		XmToggleButtonCallbackStruct *cbs)
	{
		printf("Button %s is %s\n", XtName(w), cbs->set ? "on" : "off"); 
	}

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, radiobox, buttons[3];
		XmString label;

		//
		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "RadioBox", NULL, 0,
			&argc, argv, NULL, NULL);

		//����RadioBox
		radiobox = XmCreateRadioBox(toplevel, "radiobox", NULL, 0);
		XtManageChild(radiobox);

		for(i=0; i<XtNumber(lists); i++){
			buttons[i] = XmCreateToggleButton(radiobox, 
				lists[i], NULL, 0);
			XtManageChild(buttons[i]);
			XtAddCallback(buttons[i], XmNvalueChangedCallback, 
				(XtCallbackProc)toggle, (XtPointer)i);
		}

		//���ó�ʼֵ
		XmToggleButtonSetState(buttons[1], True, False);
		

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
