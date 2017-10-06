
#include "theme.h"
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
	ThemeDemo themedemo;

	//���ô��ڱ���
	themedemo.setCaption(QObject::tr("����(Themes)��ʾ"));

	//����Ϊ������
	a.setMainWidget( &themedemo );

	//��ʾ
	themedemo.show();

	//����ѭ��
	return a.exec();
}
