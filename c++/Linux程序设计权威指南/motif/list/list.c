
	/* File: list.c */
	//runit XENVIRONMENT=List.ad ./list
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/List.h>

	char *months[] = {
		"January(һ��)", "Febrary(����)", "March(����)", "April(����)",
		"May(����)", "June(����)", "July(����)","August(����)", 
		"September(����)", "October(ʮ��)", "November(ʮһ��)", 
		"December(ʮ����)"
	};

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, list;
		XmString str_months[12];

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "List", NULL, 0,
			&argc, argv, NULL, NULL);

		//�����б��ϵĸ����ַ���
		for(i=0; i<12; i++)
			str_months[i] = XmStringCreateSimple(months[i]);

		//�����б�
		n = 0;
		XtSetArg(args[n], XmNitems, str_months); 	n++;
		XtSetArg(args[n], XmNitemCount, 12);	 	n++;
		XtSetArg(args[n], XmNvisibleItemCount, 8); 	n++;
		//XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC);n++;
		//XtSetArg(args[n], XmNlistSizePolicy, XmCONSTANT);n++;
		XtSetArg(args[n], XmNselectionPolicy, XmEXTENDED_SELECT);n++;
		list = XmCreateScrolledList(toplevel, "list", args, n);
		XtManageChild(list);

		for(i=0; i<12; i++)
			XmStringFree(str_months[i]);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
