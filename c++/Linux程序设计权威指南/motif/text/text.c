
	/* File: text.c */
	//runit XENVIRONMENT=Text.ad ./text
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/TextF.h>
	#include <Xm/Text.h>
	#include <Xm/PushB.h>
	#include <Xm/Separator.h>
	#include <Xm/RowColumn.h>

	Widget textf, text;

	void checkit(Widget w,  XtPointer client_data ,
		XmAnyCallbackStruct *cbs)
	{
		char *string;
		string = XmTextFieldGetString(textf);
		printf("TextField:%s\n", string);
		XtFree(string);
		
		string = XmTextGetString(text);
		printf("Text:%s\n", string);
		XtFree(string);
		
	}

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, rowcol, sep, button;
		XmString str_months[12];

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "Text", NULL, 0,
			&argc, argv, NULL, NULL);

		//����rowcolumn ����
		n = 0;
		XtSetArg(args[n], XmNpacking, XmPACK_TIGHT);   n++;
		rowcol = XmCreateRowColumn(toplevel, "rowcol", args, n);
		XtManageChild(rowcol);

		//����������
		n = 0;
		XtSetArg(args[n], XmNvalue, "������");	n++;
		textf = XmCreateTextField(rowcol, "textf", args, n);
		XtManageChild(textf);
		//�����ص�
		XtAddCallback(textf, XmNactivateCallback, 
			(XtCallbackProc)checkit, NULL);

		//����������
		n = 0;
		XtSetArg(args[n], XmNrows, 10);				n++;
		XtSetArg(args[n], XmNcolumns, 40);			n++;
		XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);	n++;
		XtSetArg(args[n], XmNvalue, "��������\n�����");	n++;
		text = XmCreateScrolledText(rowcol, "text", args, n);
		//text = XmCreateText(rowcol, "text", args, n);
		XtManageChild(text);
		
		//�����ָ���
		sep = XmCreateSeparator(rowcol, "separator", NULL, 0);
		XtManageChild(sep);

		//����һ����ͨ��ť
		button = XmCreatePushButton(rowcol, 
			"��ӡ���������ı�������", NULL, 0);
		XtManageChild(button);
		XtAddCallback(button, XmNactivateCallback,
			(XtCallbackProc)checkit, NULL);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
