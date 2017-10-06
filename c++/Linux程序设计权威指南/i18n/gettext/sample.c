
	/* file sample.c */
	#include <locale.h>
	#include <libintl.h>

	#define _(String)  gettext(String)
	#define N_(String)  gettext(String)
	#define __(String) (String)

	int main(int argc, char *argv[])
	{

		//�ɻ�����������locale
		setlocale(LC_ALL, "");

		//����message��λ�ú��ļ���
		bindtextdomain("sample", "./locale");
		textdomain("sample");

		printf(_("String to be translated.\n"));
	}


