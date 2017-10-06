

#include "toolbar.h"
#include "icons.h"
#include <qtextcodec.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qstatusbar.h>
#include <qpixmap.h>
#include <qapplication.h>
#include <qmultilineedit.h>
#include <qmessagebox.h>
#include <qmainwindow.h>
#include <qtoolbar.h>
#include <qaction.h>
#include <qwhatsthis.h>
#include <qfiledialog.h>

const char * fileOpenText = "<img source=\"fileopen\"> "
"���˰�ť��һ��<em>���ļ�</em>. <br><br>"
"��Ҳ����ʹ���ļ��˵��е�<b>������</b>";
const char * fileSaveText = "���˰�ť���汻�༭������"
"�㽫����ʾѡ��һ���ļ���\n\n"
"��Ҳ���ԴӲ˵���ѡ�񱣴���߱���Ϊ����";
const char * filePrintText = "���˰�ť��ӡ���ڱ༭���ļ�\n\n"
"��Ϳ��ԴӲ˵���ѡ���ӡ����";



ToolbarDemo::ToolbarDemo()
    : QMainWindow(0, "Toolbar Demo")
{

	//�����ڱ�����һ���߼�����

	//��������
	QAction *fileNewAction, *fileOpenAction, *fileSaveAction,
		*fileSaveAsAction, *filePrintAction, *fileCloseAction,
		*fileQuitAction;
	fileNewAction = new QAction( "New", tr("�½�(&N)"), 
		CTRL+Key_N, this, "new" );
	connect( fileNewAction, SIGNAL( activated() ) ,this, SLOT( newDoc()));
	fileOpenAction = new QAction( "Open File", QPixmap( fileopen ), 
		tr("��(&O)"), CTRL+Key_O, this, "open" );
	connect( fileOpenAction, SIGNAL( activated() ) , this, SLOT( load() ) );
	QMimeSourceFactory::defaultFactory()->setPixmap( "fileopen",
		QPixmap( fileopen ) );
	fileOpenAction->setWhatsThis( tr(fileOpenText) );

	fileSaveAction = new QAction( "Save File", QPixmap( filesave ), 
		tr("����(&S)"), CTRL+Key_S, this, "save" );
	connect( fileSaveAction, SIGNAL( activated() ) , this, SLOT( save() ) );
	fileSaveAction->setWhatsThis( tr(fileSaveText) );

	fileSaveAsAction = new QAction( "Save File As", tr("����Ϊ(&s)..."), 
		0,  this, "save as" );
	connect( fileSaveAsAction, SIGNAL(activated()),this,SLOT( saveAs() ));
	fileSaveAsAction->setWhatsThis( tr(fileSaveText) );
	filePrintAction = new QAction( "Print File", QPixmap( fileprint ), 
		tr("��ӡ(&P)"), CTRL+Key_P, this, "print" );
	connect( filePrintAction, SIGNAL(activated()) , this, SLOT(print()));
	filePrintAction->setWhatsThis( tr(filePrintText) );

	fileCloseAction = new QAction( "Close", tr("�ر�(&C)"), CTRL+Key_W, 
		this, "close" );
	connect( fileCloseAction, SIGNAL(activated()) , this, SLOT(close()) );

	fileQuitAction = new QAction( "Quit", tr("�˳�(&Q)"), CTRL+Key_Q, 
		this, "quit" );
	connect(fileQuitAction,SIGNAL(activated()),qApp,SLOT(closeAllWindows()));


	//������ť��
	QToolBar* fileTools = new QToolBar( this, "file operations" );
	fileTools->setLabel( "File Operations" );
	fileOpenAction->addTo( fileTools );
	fileSaveAction->addTo( fileTools );
	filePrintAction->addTo( fileTools );
	(void)QWhatsThis::whatsThisButton( fileTools );


	//�����ļ��˵�
	QPopupMenu * file = new QPopupMenu( this );
	menuBar()->insertItem( tr("�ļ�(&F)"), file );
	fileNewAction->addTo( file );
	fileOpenAction->addTo( file );
	fileSaveAction->addTo( file );
	fileSaveAsAction->addTo( file );
	file->insertSeparator();
	filePrintAction->addTo( file );
	file->insertSeparator();
	fileCloseAction->addTo( file );
	fileQuitAction->addTo( file );

	//���������˵�
	QPopupMenu * help = new QPopupMenu( this );
	menuBar()->insertSeparator();
	menuBar()->insertItem( tr("����(&H)"), help );
	help->insertItem( tr("����(&A)"), this, SLOT(about()), Key_F1 );
	help->insertItem( tr("���� &Qt"), this, SLOT(aboutQt()) );
	help->insertSeparator();
	help->insertItem(tr("����ʲô?"),this,SLOT(whatsThis()),SHIFT+Key_F1);


	QMultiLineEdit *e = new QMultiLineEdit( this, "editor" );
	e->setFocus();
	setCentralWidget( e );
	statusBar()->message( tr("׼������"), 2000 );
	resize( 400, 400 );

}


void ToolbarDemo::newDoc()
{
    ToolbarDemo *ed = new ToolbarDemo;
    ed->show();
}

void ToolbarDemo::load()
{
    QString fn = QFileDialog::getOpenFileName( QString::null, QString::null,
                                               this);
    statusBar()->message( "Loading " + fn );
}


void ToolbarDemo::save()
{
    statusBar()->message( "Saved" );
}


void ToolbarDemo::saveAs()
{
    statusBar()->message( "Save as..." );
}


void ToolbarDemo::closeEvent( QCloseEvent* ce )
{
	ce->accept();
}


void ToolbarDemo::print()
{
    statusBar()->message( "Send to printer..." );
}

void ToolbarDemo::about()
{
    QMessageBox::about( this, "Qt Toolbar Example",
                        "This example demonstrates simple use of "
                        "QMainWindow,\nQMenuBar and QToolBar.");
}


void ToolbarDemo::aboutQt()
{
    QMessageBox::aboutQt( this, "Qt Toolbar Example" );
}



