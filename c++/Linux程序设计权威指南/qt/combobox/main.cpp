

#include "combobox.h"
#include <qapplication.h>
#include <qtextcodec.h>

int main( int argc, char **argv )
{
	QApplication a( argc, argv );
	a.setFont(QFont("Times", 16, QFont::Normal));
	a.setDefaultCodec( QTextCodec::codecForName("GBK") );

	//������
	ComboboxDemo comboboxdemo;

	//���óߴ�
	comboboxdemo.resize( 350, 250 );

	//���ô��ڱ���
	comboboxdemo.setCaption( QObject::tr("QComboBox ��ʾ"));

	//����Ϊ������
	a.setMainWidget( &comboboxdemo );

	//��ʾ
	comboboxdemo.show();

	//����ѭ��
	return a.exec();
}
