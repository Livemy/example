

#include "menu.h"
#include <qapplication.h>
#include <qtextcodec.h>
#include <qmenubar.h>
#include <qpopupmenu.h>

int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	a.setFont(QFont("Times", 16, QFont::Normal));
	a.setDefaultCodec( QTextCodec::codecForName("GBK") );

	//������
	MenuDemo menudemo;

	//���óߴ�
	menudemo.resize( 350, 250 );

	//���ô��ڱ���
	menudemo.setCaption( QObject::tr("�˵���ʾ"));

	//����Ϊ������
	a.setMainWidget( &menudemo );

	//��ʾ
	menudemo.show();

	//����ѭ��
	return a.exec();
}
