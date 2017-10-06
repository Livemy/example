
	/* File: option.c */
	//Runit: XENVIRONMENT=Option.ad ./option
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/RowColumn.h>
	#include <Xm/PushB.h>
	#include <Xm/DrawingA.h>

	void callback(Widget w, char *command, 
		XmAnyCallbackStruct *cbs)
	{
		printf("%s\n", command);
	}

	Widget make_menu_item(Widget menu, char *label, char *command)
	{
		Widget button;

		button = XmCreatePushButton(menu, label, NULL, 0);
		XtManageChild(button);
		XtAddCallback(button, XmNactivateCallback,
			(XtCallbackProc) callback, command);
		return button;
	}

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel;
		Widget mymenu, optmenu;
		WidgetList entries;

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "Option", NULL, 0,
			&argc, argv, NULL, NULL);

		//����ѡ��˵�
		mymenu = XmCreatePulldownMenu(toplevel, "�ļ�", NULL, 0);
		make_menu_item(mymenu, "Ӳ��", "Hard Disk");
		make_menu_item(mymenu, "���", "Mouse");
		make_menu_item(mymenu, "����", "Keyboard");
		make_menu_item(mymenu, "��ʾ��", "Monitor");

		n = 0;
		XtSetArg(args[n], XmNsubMenuId, mymenu);	n++;
		optmenu = XmCreateOptionMenu(toplevel, "�����: ", args, n);
		XtManageChild(optmenu);

		//����Ϊ������
		XtVaGetValues(mymenu,
			XmNchildren,	&entries,
			NULL);
		XtVaSetValues(mymenu,
			XmNmenuHistory, entries[2],
			NULL);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
