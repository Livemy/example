

#include "progressbar.h"
#include <qapplication.h>
#include <qtextcodec.h>

int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	a.setFont(QFont("Times", 16, QFont::Normal));
	a.setDefaultCodec( QTextCodec::codecForName("GBK") );

	//������
	ProgressBarDemo progressbardemo;

	//���óߴ�
	progressbardemo.resize( 350, 250 );

	//���ô��ڱ���
	progressbardemo.setCaption( QObject::tr("��������ʾ") );

	//����Ϊ������
	a.setMainWidget( &progressbardemo );

	//��ʾ
	progressbardemo.show();

	//����ѭ��
	return a.exec();
}
