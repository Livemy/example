
	/* File: layout.cpp */

	#include <qapplication.h>
	#include <qlabel.h>
	#include <qpushbutton.h>
	#include <qlayout.h>
	#include <qmultilineedit.h>
	#include <qmenubar.h>
	#include <qpopupmenu.h>

	class ExampleWidget : public QWidget
	{
	public:
    		ExampleWidget( QWidget *parent = 0, const char *name = 0 );
    		~ExampleWidget();
	private:
	};

	ExampleWidget::ExampleWidget( QWidget *parent, const char *name )
    		: QWidget( parent, name )
	{
		//��ֱ����
		QBoxLayout *topLayout = new QVBoxLayout( this, 5 );

		//�����˵���
		QMenuBar *menubar = new QMenuBar( this );
		menubar->setSeparator( QMenuBar::InWindowsStyle );
		QPopupMenu* popup;
		popup = new QPopupMenu( this );
		popup->insertItem( "&Quit", qApp, SLOT(quit()) );
		menubar->insertItem( "&File", popup );

		//��Ӳ˵���
		topLayout->setMenuBar( menubar );

		//����ˮƽ������, ����ӵ���ֱ������
		QBoxLayout *buttons = new QHBoxLayout( topLayout);

		int i;
		for ( i = 1; i <= 4; i++ ) {

			//������ť
			QPushButton* but = new QPushButton( this );
			QString s;
			s.sprintf( "Button %d", i );
			but->setText( s );

			//��ˮƽ��������Ӱ�ť
			buttons->addWidget( but, 10 );
		}

		//���������ı���
		QMultiLineEdit *bigWidget = new QMultiLineEdit( this );
		bigWidget->setText( "This widget will get all the remaining space" );
		bigWidget->setFrameStyle( QFrame::Panel | QFrame::Plain );

		//����ı�������ֱ������
		topLayout->addWidget( bigWidget);

		//������ǩ
		QLabel* sb = new QLabel( this );
		sb->setText("Let's pretend this is a status bar");
		sb->setFrameStyle( QFrame::Panel | QFrame::Sunken );
		sb->setFixedHeight( sb->sizeHint().height() );
		sb->setAlignment( AlignVCenter | AlignLeft );

		//��ӱ�ǩ
		topLayout->addWidget( sb );

		//�����
		topLayout->activate();
	}


	ExampleWidget::~ExampleWidget()
	{
	}

	int main( int argc, char **argv )
	{
		QApplication a( argc, argv );

		ExampleWidget f;
		a.setMainWidget(&f);
		f.show();

		return a.exec();
	}
