
	/* File: slot.cpp */

	#include <qapplication.h>
	#include <qpushbutton.h>
	#include <qfont.h>


	int main( int argc, char **argv )
	{
		QApplication a( argc, argv );

		//������ť
		QPushButton button( "Quit", 0 );

		//���ð�ť�ߴ�
		button.resize( 75, 30 );

		//���ð�ť����
		button.setFont( QFont( "Times", 18, QFont::Bold ) );

		//�����ص�, �����ť����, ����button()
		QObject::connect( &button, SIGNAL(clicked()), &a, SLOT(quit()) );

		//�Ѱ�ť����Ϊ����������
		a.setMainWidget( &button );

		//��ʾ��ť
		button.show();

		//����ѭ��
		return a.exec();
	}

