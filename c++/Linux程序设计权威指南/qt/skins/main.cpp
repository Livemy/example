

#include "skin.h"
#include <iostream.h>
#include <qwidget.h>
#include <qapplication.h>
#include <qtextcodec.h>

int main( int argc, char **argv )
{
	if(argc < 2){
		cout << "Usage: ./skin gamepad" << endl;
		exit(1);
	}

	QApplication a( argc, argv );
	a.setFont(QFont("Times", 16, QFont::Normal, TRUE));
	a.setDefaultCodec( QTextCodec::codecForName("GBK") );

	//������
	SkinDemo skindemo;

	//����Ϊ������
	a.setMainWidget( &skindemo );

	//��ʾ
	skindemo.show();

	//����ѭ��
	return a.exec();
}
