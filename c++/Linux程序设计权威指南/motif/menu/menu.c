
	/* File: menu.c */
	//Runit: XENVIRONMENT=Menu.ad ./menu
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/MainW.h>
	#include <Xm/RowColumn.h>
	#include <Xm/CascadeB.h>
	#include <Xm/PushB.h>
	#include <Xm/Separator.h>

	void callback(Widget w, char *command, 
		XmAnyCallbackStruct *cbs)
	{
		printf("%s\n", command);
	}

	Widget make_menu(Widget menubar, char *label, char mnemonic,
		char *acce, char *acce_text)
	{
		int n;
		Arg args[10];
		XmString str, text;
		Widget menu, button;
	
		menu = XmCreatePulldownMenu(menubar, label, NULL, 0);
		str = XmStringCreateSimple(label);
		text = XmStringCreateSimple(acce_text);
		n = 0;
		XtSetArg(args[n], XmNlabelString, str);		n++;
		XtSetArg(args[n], XmNmnemonic, mnemonic);	n++;
		XtSetArg(args[n], XmNsubMenuId, menu);		n++;
		XtSetArg(args[n], XmNaccelerator, acce);	n++;
		XtSetArg(args[n], XmNacceleratorText, text);	n++;
		button = XmCreateCascadeButton(menubar, label, args, n);
		XtManageChild(button);
		XmStringFree(str);
		XmStringFree(text);
		return menu;
	}

	Widget make_help_menu(Widget menubar, char *label, char mnemonic,
		char *acce, char *acce_text)
	{
		int n;
		Arg args[10];
		XmString str, text;
		Widget menu, button;
	
		menu = XmCreatePulldownMenu(menubar, label, NULL, 0);
		str = XmStringCreateSimple(label);
		text = XmStringCreateSimple(acce_text);
		n = 0;
		XtSetArg(args[n], XmNlabelString, str);		n++;
		XtSetArg(args[n], XmNmnemonic, mnemonic);	n++;
		XtSetArg(args[n], XmNsubMenuId, menu);		n++;
		XtSetArg(args[n], XmNaccelerator, acce);	n++;
		XtSetArg(args[n], XmNacceleratorText, text);	n++;
		button = XmCreateCascadeButton(menubar, label, args, n);
		XtManageChild(button);
		XmStringFree(str);
		XmStringFree(text);

		//���ð����˵�
		n = 0;
		XtSetArg(args[n], XmNmenuHelpWidget, button);	n++;
		XtSetValues(menubar, args, n);
		return menu;
	}

	Widget make_menu_item(Widget menu, char *label, char mnemonic, 
		char *acce, char *acce_text, char *command)
	{
		int n;
		Arg args[10];
		XmString str, text;
		Widget button;

		str = XmStringCreateSimple(label);
		text = XmStringCreateSimple(acce_text);
		n = 0;
		XtSetArg(args[n], XmNlabelString, str);		n++;
		XtSetArg(args[n], XmNmnemonic, mnemonic);	n++;
		XtSetArg(args[n], XmNaccelerator, acce);	n++;
		XtSetArg(args[n], XmNacceleratorText, text);	n++;
		button = XmCreatePushButton(menu, label, args, n);
		XtManageChild(button);
		XtAddCallback(button, XmNactivateCallback,
			(XtCallbackProc) callback, command);
		XmStringFree(str);
		XmStringFree(text);
		return button;
	}

	void make_menu_item_separator(Widget menu)
	{
		Widget sep;
		sep = XmCreateSeparator(menu, "sep", NULL, 0);
		XtManageChild(sep);
	}

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, mainw, menubar, w;
		Widget filemenu, editmenu, helpmenu;

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "Menu", NULL, 0,
			&argc, argv, NULL, NULL);
		n = 0;
		XtSetArg(args[n], XmNwidth, 320);	n++;
		XtSetArg(args[n], XmNheight, 320);	n++;
		XtSetValues(toplevel, args, n);

		//����������
		mainw = XmCreateMainWindow(toplevel, "mainw", NULL, 0);
		XtManageChild(mainw);
		
		//�����˵���
		menubar = XmCreateMenuBar(mainw, "menubar", NULL, 0);
		XtManageChild(menubar);

		//�����ļ��˵�
		filemenu = make_menu(menubar, "�ļ�(F)", 'F', "Meta<key>F", "Alt-F");
		make_menu_item(filemenu, "�½�(N)", 'N', "Meta<key>N", "Meta+N", "Create New File");
		make_menu_item(filemenu, "��(O)", 'O', "Meta<key>O", "Meta+O", "Open File");
		make_menu_item(filemenu, "����(S)", 'S', "Meta<key>S", "Meta+S", "Save File");
		make_menu_item_separator(filemenu);
		make_menu_item(filemenu, "�˳�(Q)", 'Q', "Meta<key>Q", "Meta+Q", "Quit Application");

		//�����༭�˵�
		editmenu = make_menu(menubar, "�༭(E)", 'E', "Meta<key>E", "Alt-E");
		make_menu_item(editmenu, "ȡ��(U)", 'U', "Meta<key>U", "Meta+U", "Undo last operation");
		make_menu_item(editmenu, "�ظ�(R)", 'R', "Meta<key>R", "Meta+R", "Redo last operation");
		make_menu_item_separator(editmenu);
		//�����Ӽ����˵�
		w = make_menu(editmenu, "�༭����(o)", 'o', "Meta<key>o", "Alt-o");
		make_menu_item(w, "����(o)", 'o', "Meta<key>o", "Meta+o", "Copy to clipboard");
		make_menu_item(w, "����(u)", 'u', "Meta<key>u", "Meta+u", "Cut to clipboard");
		make_menu_item(w, "ճ��(P)", 'P',"Meta<key>P", "Meta+P", "Paste from clipboard");

		//���������˵�
		helpmenu = make_help_menu(menubar, "����(H)", 'H', "Meta<key>H", "Alt-H");
		make_menu_item(helpmenu, "����(h)", 'h', "Meta<key>h", "Meta+h", "Help Contents");
		make_menu_item(helpmenu, "����(A)...", 'A',"Meta<key>A", "Meta+A",  "About this application");

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
