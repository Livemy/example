
#include "rangecontrol.h"
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
	RangeControlDemo rangecontroldemo;

	//���ô��ڱ���
	rangecontroldemo.setCaption(QObject::tr("��Χ������ʾ"));

	//����Ϊ������
	a.setMainWidget( &rangecontroldemo );

	//��ʾ
	rangecontroldemo.show();

	//����ѭ��
	return a.exec();
}
