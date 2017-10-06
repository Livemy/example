
	/* File: rowcolumn.c */
	//Runit: XENVIRONMENT=RowColumn.ad ./rowcolumn
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/RowColumn.h>
	#include <Xm/Label.h>
	#include <Xm/TextF.h>

	char *items[] = {
		"����:",
		"�Ա�:",
		"��������:",
		"�绰����:",
		"��ͥסַ:",
		"��������:"
	};

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, rowcolumn, label, textf;

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "RowColumn", NULL, 0,
			&argc, argv, NULL, NULL);

		//����RowColumn���
		n = 0;
		XtSetArg(args[n], XmNnumColumns, 6); 			n++;
		XtSetArg(args[n], XmNpacking, XmPACK_COLUMN);		n++;
		XtSetArg(args[n], XmNorientation, XmHORIZONTAL);	n++;
		XtSetArg(args[n], XmNadjustLast, False);		n++;
		XtSetArg(args[n], XmNisAligned, True);			n++;
		XtSetArg(args[n], XmNentryAlignment, XmALIGNMENT_END);	n++;
		rowcolumn  = XmCreateRowColumn(toplevel, "rowcolumn", args, n);
		XtManageChild(rowcolumn);


		for(i=0; i<XtNumber(items); i++){
			label = XmCreateLabel(rowcolumn, items[i], NULL, 0);
			XtManageChild(label);

			textf = XmCreateTextField(rowcolumn, "textf", NULL, 0);
			XtManageChild(textf);
		}
			
		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}

