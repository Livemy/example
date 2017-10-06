	/* File: tab.cpp */

	#include <qapplication.h>
	#include <qlabel.h>
	#include <qtabwidget.h>
	#include <qlineedit.h>
	#include <qmultilineedit.h>
	#include <qtextcodec.h>
	#include <qvbox.h>

	int main( int argc, char **argv )
	{
		//����Application
		QApplication a( argc, argv ); 
		a.setFont(QFont("Times", 16));
		a.setDefaultCodec( QTextCodec::codecForName("GBK") );

		//����QTabWidget
		QTabWidget *tab = new QTabWidget;
		tab->resize(320, 200);

		//-------------------------------------
		QWidget *tab1 = new QWidget(tab);
		QLineEdit *le = new QLineEdit(tab1);
		le->resize(300, 30);
		tab->addTab( tab1, QObject::tr("������(&E)") );
		
		//-------------------------------------
		QWidget *tab2 = new QWidget(tab);
		QMultiLineEdit *me = new QMultiLineEdit(tab2);
		me->resize(300, 150);
		tab->addTab( tab2, QObject::tr("������(&M)") );

		//��Application�м��밴ť
		a.setMainWidget( tab );

		//��ʾ��ť
		tab->show();

		//����ѭ��
		return a.exec();
	}
