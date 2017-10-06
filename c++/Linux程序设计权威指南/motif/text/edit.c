
	/* File: edit.c */
	//runit XENVIRONMENT=Edit.ad ./edit
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/TextF.h>
	#include <Xm/Text.h>
	#include <Xm/PushB.h>
	#include <Xm/Separator.h>
	#include <Xm/RowColumn.h>

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, rowcol, textf, text;
		XmString str_months[12];

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "Edit", NULL, 0,
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

		//�����ı���
		n = 0;
		XtSetArg(args[n], XmNrows, 10);				n++;
		XtSetArg(args[n], XmNcolumns, 40);			n++;
		XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);	n++;
		XtSetArg(args[n], XmNwordWrap, True);			n++;
		XtSetArg(args[n], XmNvalue, "��������\n�����");	n++;
		text = XmCreateScrolledText(rowcol, "text", args, n);
		XtManageChild(text);
		
		//��ʾ����
		XtRealizeWidget(toplevel);

		//edit
		XmTextSetInsertionPosition(text, 3);
		XmTextInsert(text, 5, "���Բ���");
		XmTextSetSelection(text, 5, 8, CurrentTime);
		XmTextCopy(text, CurrentTime);
		XmTextSetInsertionPosition(text, 1);
		XmTextPaste(text);
		

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
