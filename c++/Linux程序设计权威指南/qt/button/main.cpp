

#include "button.h"
#include <qapplication.h>
#include <qtextcodec.h>

int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	a.setFont(QFont("Times", 14, QFont::Normal));
	a.setDefaultCodec( QTextCodec::codecForName("GBK") );

	//������
	LabelButton labelbutton;

	//���óߴ�
	labelbutton.resize( 500, 250 );

	//���ô��ڱ���
	labelbutton.setCaption( QObject::tr("��ǩ�Ͱ�ť����ʾ����"));

	//����Ϊ������
	a.setMainWidget( &labelbutton );

	//��ʾ
	labelbutton.show();

	//����ѭ��
	return a.exec();
}
