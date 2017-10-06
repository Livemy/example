
	/* File: buttons.c */

	#include <stdio.h>
	#include <stdlib.h>
	#include <newt.h>
	#include <string.h>

	int main(int argc, char *argv[]) 
	{
		int i;
		//�������
		newtComponent form;
		newtComponent text, list;
		newtComponent button_ok, button_cancel;
		newtComponent co;
		char *selection;

		char *message =	"��ѡ������Ϊ��õĲ���ϵͳ, "
				"�����ѡ����Windows,  ˵����"
				"�㲻�˽�Linux.";
		char *str_list[7] = {
			"Linux",
			"Windows",
			"Macintosh",
			"Solaris",
			"HP-UX",
			"BeOS",
			"OS/2"
		};


		//��ʼ��
		newtInit();
		newtCls();

		//��������
		newtCenteredWindow(50, 18, "List Sample");

		//-------------------------------------------
		//����Form
		form = newtForm(NULL, NULL, 0);

		text = newtTextboxReflowed(10, 1, message, 30, 5, 5, 0);
		newtFormAddComponent(form, text);

		//�����б�
		list = newtListbox(8, 5, 8, 
	 	   NEWT_FLAG_SCROLL | NEWT_FLAG_RETURNEXIT |NEWT_FLAG_BORDER);
		newtListboxSetWidth(list, 30);
		for(i=0; i<7; i++)
			newtListboxAppendEntry(list, 
                                str_list[i], str_list[i]);
		newtFormAddComponent(form, list);

		//�б�

		button_ok = newtButton(20, 14, "ȷ��");
		newtFormAddComponent(form, button_ok);

		//--------------------------------------------
		//����ѭ��
		newtRunForm(form);
		selection = strdup((char *)newtListboxGetCurrent(list));
		//�ر�Form
		newtFormDestroy(form);
		newtPopWindow();

		newtWinMessage("����ѡ��", "Ok", selection);

		//��ԭ
		newtFinished();

	}
