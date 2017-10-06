
	/* File: combobox.c */
	//Runit: XENVIRONMENT=ComboBox.ad ./combobox
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/ComboBox.h>

	#define TOTAL 4

	char *computer[TOTAL] = {
		"����",
		"���",
		"��ʾ��",
		"Ӳ��"
	};

	void SelectionCallback(Widget w, XtPointer client_data, 
		XmComboBoxCallbackStruct *cbs)
	{
		char *str;
		int item_position;

		XmStringGetLtoR(cbs->item_or_text, "", &str);
		
		printf ("ComboBox SelectionCallback invoked\n");
		printf ("Item is %s\n", str);
		printf ("Position is %d\n", cbs->item_position);

		XtFree(str);
	}

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, combobox;
		XmString items[TOTAL];

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "ComboBox", NULL, 0,
			&argc, argv, NULL, NULL);

		for(i=0; i<TOTAL; i++)
			items[i]=XmStringCreateLocalized(computer[i]);

		//����ComboBox
		n = 0;
		XtSetArg(args[n], XmNcomboBoxType, XmDROP_DOWN_COMBO_BOX);n++;
		//XtSetArg(args[n], XmNcomboBoxType, XmDROP_DOWN_LIST);n++;
		//XtSetArg(args[n], XmNcomboBoxType, XmCOMBO_BOX);	n++;
		XtSetArg(args[n], XmNlistSpacing, 5);			n++;
		XtSetArg(args[n], XmNlistMarginWidth, 2);		n++;
		XtSetArg(args[n], XmNlistMarginHeight, 2);		n++;
		XtSetArg(args[n], XmNitems, items ); 			n++;
		XtSetArg(args[n], XmNitemCount, TOTAL); 		n++;
		XtSetArg(args[n], XmNvisibleItemCount, TOTAL-1 ); 	n++;
		combobox = XmCreateComboBox(toplevel,"combobox",args, n);
		XtManageChild(combobox);

		//���ӻص�����
		XtAddCallback(combobox, XmNselectionCallback, 
			(XtCallbackProc)SelectionCallback, (XtPointer)NULL);

		//����
		XmComboBoxSelectItem(combobox, items[1]);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
