
	#include <stdlib.h>
	#include <newt.h>

	int main(int argc, char *argv[]) 
	{
		//�������
		newtComponent form, button;

		//��ʼ��
		newtInit();

		//����Ļ
		newtCls();

		//�ڴ��ڵײ�д������Ϣ
		newtPushHelpLine("Press button to exit...");

		//��������
		newtOpenWindow(10, 5, 40, 6, "Hello World!");

		//-------------------------------------------
		//������ť
		button = newtButton(8, 1, "���, newt����Ա��!");

		//����Form
		form = newtForm(NULL, NULL, 0);

		//�Ѱ�ť����Form
		newtFormAddComponents(form, button, NULL);

		//--------------------------------------------

		//����ѭ��
		newtRunForm(form);

		//�ر�Form
		newtFormDestroy(form);

		//��ԭ
		newtFinished();
	}
