
#include "scribble.h"
#include <qapplication.h>
#include <qtextcodec.h>

int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	a.setFont(QFont("Times", 16, QFont::Normal));
	a.setDefaultCodec( QTextCodec::codecForName("GBK") );

	//������
	ScribbleDemo scribbledemo;

	//���ô��ڱ���
	scribbledemo.setCaption(QObject::tr("������ͼ��ʾ"));

	//����Ϊ������
	a.setMainWidget( &scribbledemo );

	//��ʾ
	scribbledemo.show();

	//����ѭ��
	return a.exec();
}
