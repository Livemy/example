
	/* File: passwd.c */
	//runit XENVIRONMENT=Passwd.ad ./passwd
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/TextF.h>
	#include <Xm/Label.h>
	#include <Xm/RowColumn.h>

	void checkit(Widget w, XtPointer client_data,
		XmTextVerifyCallbackStruct *cbs)
	{
		static char *passwd;
		char *str;
		int len;

		if(cbs->reason == XmCR_ACTIVATE){
			printf("Your passwd is:%s\n", passwd);
			return;
		}

		//�˸��
		if(cbs->text->ptr == NULL){
			cbs->endPos = strlen(passwd);
			passwd[cbs->startPos] = '\0';
			return;
		} else if(cbs->text->length > 1) { //ճ��
			cbs->doit = False;	//������
			return;
		}

		str = XtMalloc(cbs->endPos + 2);
		if(passwd){
			strcpy(str, passwd);
			XtFree(passwd);
		} else {
			str[0] = '\0';
		}

		passwd = str;
		strncat(passwd, cbs->text->ptr, cbs->text->length);
		passwd[cbs->endPos + cbs->text->length] = '\0';
		for(len = 0; len<cbs->text->length; len++)
			cbs->text->ptr[len] = '*';
	}

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, rowcol, label, textf;
		XmString str_months[12];

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "Passwd", NULL, 0,
			&argc, argv, NULL, NULL);

		//����rowcolumn ����
		n = 0;
		XtSetArg(args[n], XmNpacking, XmPACK_TIGHT);   		n++;
		XtSetArg(args[n], XmNorientation, XmHORIZONTAL);   	n++;
		rowcol = XmCreateRowColumn(toplevel, "rowcol", args, n);
		XtManageChild(rowcol);

		//������ǩ
		label = XmCreateLabel(rowcol, "���������:", NULL, 0);
		XtManageChild(label);

		//����������
		textf = XmCreateTextField(rowcol, "textf", NULL, 0);
		XtManageChild(textf);
		XtAddCallback(textf, XmNmodifyVerifyCallback, 
			(XtCallbackProc)checkit, NULL);
		XtAddCallback(textf, XmNactivateCallback, 
			(XtCallbackProc)checkit, NULL);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
