	/* File: helloworld.c */

	#include <qapplication.h>
	#include <qtextview.h>
	#include <qtextstream.h>
	#include <qfile.h>
	#include <qtextcodec.h>

	int main( int argc, char **argv )
	{
		//����Application
		QApplication a( argc, argv ); 
		a.setFont(QFont("Times", 16, QFont::Normal));
		a.setDefaultCodec( QTextCodec::codecForName("GBK") );

		//������ť
		QTextView tview;

		//���ð�ť�ߴ�
		tview.resize( 640, 480 ); 


		//���ļ�
		QFile f("index.html");
		QString s;
		if ( f.open(IO_ReadOnly) ) {
			QTextStream t( &f );
			while ( !t.eof() ) {
				s += t.readLine();
			}
			f.close();
		}

		tview.setText(s);

		//��Application�м��밴ť
		a.setMainWidget( &tview );

		//��ʾ��ť
		tview.show();

		//����ѭ��
		return a.exec();
	}
