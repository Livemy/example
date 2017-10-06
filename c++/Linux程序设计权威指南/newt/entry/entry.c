
	#include <stdio.h>
	#include <stdlib.h>
	#include <newt.h>
	#include <string.h>

	int main(int argc, char *argv[]) 
	{
		//�������
		newtComponent form, label, entry, button_ok, button_cancel;
		newtComponent co;
		char *entryvalue;

		//��ʼ��
		newtInit();

		//����Ļ
		newtCls();

		//��������
		newtCenteredWindow(50, 10, "Entry Sample");

		//-------------------------------------------
		//������ť
		label  = newtLabel(6, 1, "������סַ:");
		entry  = newtEntry(20, 1, "������", 28,
			NULL, NEWT_FLAG_SCROLL | NEWT_FLAG_RETURNEXIT);

		button_ok = newtButton(8, 6, "ȷ��");
		button_cancel = newtButton(30, 6, "ȡ��");

		//����Form
		form = newtForm(NULL, NULL, 0);

		//�Ѱ�ť����Form
		newtFormAddComponents(form, label, entry, 
			button_ok, button_cancel, NULL);

		//--------------------------------------------

		//����ѭ��
		co = newtRunForm(form);

		//�����������ֵ
		if(co == entry || co == button_ok)
			entryvalue = strdup(newtEntryGetValue(entry));
		else
			entryvalue = strdup("Input cancelled.");
 
		//�ر�Form
		newtFormDestroy(form);

		//��ԭ
		newtFinished();

		//��ӡ���
		printf("%s\n", entryvalue);
		free(entryvalue);
	}
