
	/* File: form.c */
	//Runit: XENVIRONMENT=Form.ad ./form
	#include <locale.h>
	#include <Xm/Xm.h>
	#include <Xm/Form.h>
	#include <Xm/Label.h>
	#include <Xm/ComboBox.h>
	#include <Xm/Text.h>
	#include <Xm/RowColumn.h>
	#include <Xm/DrawnB.h>
	#include <X11/xpm.h>
	#include "smile.xpm"

	void create_menu(Widget w);

	int main(int argc, char *argv[])
	{
		int i, n;
		Arg args[10];
		XtAppContext app;
		Widget toplevel, form, menubar, form2, text;
		Widget label, combobox, button;
		Pixmap pixmap;

		setlocale(LC_ALL, "");

		//������������
		toplevel = XtVaAppInitialize(&app, "Form", NULL, 0,
			&argc, argv, NULL, NULL);
		n = 0;
		XtSetArg(args[n], XmNwidth, 500);	n++;
		XtSetArg(args[n], XmNheight, 500);	n++;
		XtSetValues(toplevel, args, n);

		//����������
		form = XmCreateForm(toplevel, "form", NULL, 0);
		XtManageChild(form);
		
		//�����˵���
		n = 0;
		XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);	n++;
		XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
		XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
		menubar = XmCreateMenuBar(form, "menubar", args, n);
		XtManageChild(menubar);

		create_menu(menubar);

		//������ Form
		n = 0;
		XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET);	n++;
		XtSetArg(args[n], XmNtopWidget, menubar);		n++;
		XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
		XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
		form2 = XmCreateForm(form, "form2", args, n);
		XtManageChild(form2);
		//������ǩ��������
		n = 0;
		XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);	n++;
		XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
		XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
		label = XmCreateLabel(form2, "�����ַ���:", args, n);
		XtManageChild(label);
		//����ͼ��
		XpmCreatePixmapFromData(XtDisplay(toplevel),
			XRootWindowOfScreen(XtScreen(toplevel)), 
			xpm_smile, &pixmap, NULL, NULL);
		//������ť
		n = 0;
		XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);	n++;
		XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
		//XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);	n++;
		//XtSetArg(args[n], XmNleftWidget, combobox);		n++;
		XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
		XtSetArg(args[n], XmNlabelType, XmPIXMAP);		n++;
		XtSetArg(args[n], XmNlabelPixmap, pixmap);		n++;
		button = XmCreateDrawnButton(form2, "button", args, n);
		XtManageChild(button);
		//����ComboBox
		n = 0;
		XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);	n++;
		XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
		XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET);	n++;
		XtSetArg(args[n], XmNleftWidget, label);		n++;
		XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET);	n++;
		XtSetArg(args[n], XmNrightWidget, button);		n++;
		XtSetArg(args[n], XmNcomboBoxType, XmDROP_DOWN_COMBO_BOX);n++;
		XtSetArg(args[n], XmNshadowThickness, 1);		n++;
		combobox = XmCreateComboBox(form2, "combobox", args, n);
		XtManageChild(combobox);
		//�����ı���
		n = 0;
		XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET);	n++;
		XtSetArg(args[n], XmNtopWidget, form2);			n++;
		XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);	n++;
		XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);	n++;
		XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);	n++;
		XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);	n++;
		text = XmCreateText(form, "text", args, n);
		XtManageChild(text);

		//��ʾ����
		XtRealizeWidget(toplevel);

		//�����¼�ѭ��
		XtAppMainLoop(app);

	}
