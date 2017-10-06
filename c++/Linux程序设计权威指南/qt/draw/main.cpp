

#include "draw.h"
#include <qapplication.h>
#include <qtextcodec.h>

int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	a.setFont(QFont("Times", 16, QFont::Normal));
	a.setDefaultCodec( QTextCodec::codecForName("GBK") );

	//������
	DrawDemo drawdemo;

	//���óߴ�
	drawdemo.resize( 640, 480 );

	//���ô��ڱ���
	drawdemo.setCaption( QObject::tr("��ͼ��ʾ"));

	//����Ϊ������
	a.setMainWidget( &drawdemo );

	//��ʾ
	drawdemo.show();

	//����ѭ��
	return a.exec();
}
