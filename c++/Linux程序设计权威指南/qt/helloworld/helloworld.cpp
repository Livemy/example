	/* File: helloworld.c */

	#include <qapplication.h>
	#include <qpushbutton.h>

	int main( int argc, char **argv )
	{
		//����Application
		QApplication a( argc, argv ); 

		//������ť
		QPushButton hello( "Hello world!", 0 );

		//���ð�ť�ߴ�
		hello.resize( 100, 30 ); 

		//��Application�м��밴ť
		a.setMainWidget( &hello );

		//��ʾ��ť
		hello.show();

		//����ѭ��
		return a.exec();
	}
