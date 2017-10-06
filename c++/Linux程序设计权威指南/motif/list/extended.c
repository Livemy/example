
	/* File: extended.c */
	//runit XENVIRONMENT=Extended.ad ./extended
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/List.h>
	#include <Xm/PushB.h>
	#include <Xm/Separator.h>
	#include <Xm/RowColumn.h>

	char *months[] = {
		"January(һ��)", "Febrary(����)", "March(����)", "April(����)",
		"May(����)", "June(����)", "July(����)","August(����)", 
		"September(����)", "October(ʮ��)", "November(ʮһ��)", 
		"December(ʮ����)"
	};

	void callback(Widget w, XtPointer client_data,
		XmListCallbackStruct *cbs)
	{
		int i;
		char *string;
		printf("\nreason: %d\n", cbs->reason);
		if(cbs->reason == XmCR_EXTENDED_SELECT){
			printf("items selected:%d\n", cbs->selected_item_count);
			for(i=0; i<cbs->selected_item_count; i++){
				XmStringGetLtoR(cbs->selected_items[i],
					"", &string);
				printf("item %d:%s\n", 
					cbs->selected_item_positions[i],string);
				XtFree(string);
			}
		} else {
			XmStringGetLtoR(cbs->item, "", &string);
			printf("item %d:%s\n", cbs->item_position, string);
			XtFree(string);
		}
	}

	void checkit(Widget w,  Widget list,
		XmAnyCallbackStruct *cbs)
	{
		int i, count;
		XmStringTable selection;
		char *string;

		XtVaGetValues(list,
			XmNselectedItemCount,	&count,
			XmNselectedItems,	&selection,
			NULL);
		printf("\nselection result:\n");
		for(i = 0; i < count; i++){
			XmStringGetLtoR(selection[i], "", &string);
			printf("item %s selected.\n", string);
			XtFree(string);
		}
	}

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, rowcol, list, sep, button;
		XmString str_months[12];

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "Extended", NULL, 0,
			&argc, argv, NULL, NULL);

		//����rowcolumn ����
		n = 0;
		XtSetArg(args[n], XmNpacking, XmPACK_TIGHT);   n++;
		rowcol = XmCreateRowColumn(toplevel, "rowcol", args, n);
		XtManageChild(rowcol);

		//�����б��ϵĸ����ַ���
		for(i=0; i<12; i++)
			str_months[i] = XmStringCreateSimple(months[i]);

		//�����б�
		n = 0;
		XtSetArg(args[n], XmNitems, str_months); 	n++;
		XtSetArg(args[n], XmNitemCount, 12);	 	n++;
		XtSetArg(args[n], XmNvisibleItemCount, 8); 	n++;
		XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC);n++;
		XtSetArg(args[n], XmNlistSizePolicy, XmCONSTANT);n++;
		XtSetArg(args[n], XmNselectionPolicy, XmEXTENDED_SELECT);n++;
		list = XmCreateScrolledList(rowcol, "list", args, n);
		XtManageChild(list);
		//�����ص�
		XtAddCallback(list, XmNextendedSelectionCallback, 
			(XtCallbackProc)callback, NULL);
		XtAddCallback(list, XmNdefaultActionCallback,
			(XtCallbackProc)callback, NULL);


		for(i=0; i<12; i++)
			XmStringFree(str_months[i]);

		//�����ָ���
		sep = XmCreateSeparator(rowcol, "separator", NULL, 0);
		XtManageChild(sep);

		//����һ����ͨ��ť
		button = XmCreatePushButton(rowcol, "��ӡ�б�ѡ��", NULL, 0);
		XtManageChild(button);
		XtAddCallback(button, XmNactivateCallback,
			(XtCallbackProc)checkit, list);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
