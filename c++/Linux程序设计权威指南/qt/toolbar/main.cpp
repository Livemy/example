
#include "toolbar.h"
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
	ToolbarDemo toolbardemo;

	//���ô��ڱ���
	toolbardemo.setCaption(QObject::tr("��ť����ʾ"));

	//����Ϊ������
	a.setMainWidget( &toolbardemo );

	//��ʾ
	toolbardemo.show();

	//����ѭ��
	return a.exec();
}
