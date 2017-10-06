
	/* File: notebook.c */
	//Runit: XENVIRONMENT=Notebook.ad ./notebook
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/Notebook.h>
	#include <Xm/Label.h>
	#include <Xm/PushB.h>
	#include <Xm/Frame.h>
	#include <Xm/Text.h>

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		char buf[80];
		XtAppContext app;
		Widget toplevel, notebook, page[6], label[6], frame[6], text[6];

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "Notebook", NULL, 0,
			&argc, argv, NULL, NULL);

		//����Notebook
		n = 0;
		XtSetArg(args[n], XmNwidth, 600 ); 			n++;
		XtSetArg(args[n], XmNheight, 400 ); 			n++;
		XtSetArg(args[n], XmNfirstPageNumber, 1); 		n++;
		XtSetArg(args[n], XmNlastPageNumber, 6); 		n++;

		notebook  = XmCreateNotebook(toplevel, "notebook", args, n);
		XtManageChild(notebook);

		//����ҳ��
		for(i=0; i<6; i++){
			n = 0;
			sprintf(buf, "ҳ�� %d", i + 1);
			label[i] = XmCreateLabel(notebook, buf, args, n);
			page[i] = XmCreatePushButton(notebook, buf, args, n);
		}
		XtManageChildren(label, 6);
		XtManageChildren(page, 6);

		for(i=0; i<6; i++){
			XtSetArg(args[n], XmNpageNumber, i + 1); n++;
			text[i] = XmCreateScrolledText(notebook, buf, args, n);
			XtManageChild(text[i]);
		}


		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}

