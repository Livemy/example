

#include "listbox.h"
#include <qapplication.h>
#include <qtextcodec.h>

int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	a.setFont(QFont("Times", 16, QFont::Normal));
	a.setDefaultCodec( QTextCodec::codecForName("GBK") );

	//������
	ListDemo listdemo;

	//���óߴ�
	listdemo.resize( 350, 250 );

	//���ô��ڱ���
	listdemo.setCaption( QObject::tr("�б���ʾ"));

	//����Ϊ������
	a.setMainWidget( &listdemo );

	//��ʾ
	listdemo.show();

	//����ѭ��
	return a.exec();
}
