

#include "edit.h"
#include <qapplication.h>
#include <qtextcodec.h>

int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	a.setFont(QFont("Times", 16, QFont::Normal));
	a.setDefaultCodec( QTextCodec::codecForName("GBK") );

	//������
	EditDemo editdemo;

	//���óߴ�
	editdemo.resize( 350, 250 );

	//���ô��ڱ���
	editdemo.setCaption( QObject::tr("�������ͱ༭����ʾ"));

	//����Ϊ������
	a.setMainWidget( &editdemo );

	//��ʾ
	editdemo.show();

	//����ѭ��
	return a.exec();
}
