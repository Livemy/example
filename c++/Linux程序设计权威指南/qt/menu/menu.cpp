

#include "menu.h"
#include "icons.h"
#include <qlabel.h>
#include <qtextcodec.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qstatusbar.h>
#include <qpixmap.h>
#include <qlayout.h>
#include <qapplication.h>
#include <qmessagebox.h>

MenuDemo::MenuDemo( QWidget *parent, const char *name )
    : QWidget( parent, name )
{

	//��������
	QVBoxLayout *vbox = new QVBoxLayout(this);

	QPixmap p1( p1_xpm );
	QPixmap p2( p2_xpm );
	QPixmap p3( p3_xpm );

	//���� print �Ӳ˵�
	QPopupMenu *print = new QPopupMenu( this );
	print->insertTearOffHandle();
	print->insertItem( tr("��ӡ����ӡ��(&P)"), this, SLOT(printer()) );
	print->insertItem( tr("��ӡ���ļ�(&f)"), this, SLOT(file()) );
	print->insertItem( tr("��ӡ�������(&x)"), this, SLOT(fax()) );
	print->insertSeparator();
	print->insertItem( tr("��ӡ������(&S)"), this, SLOT(printerSetup()) );


	//�����ļ��˵�
	QPopupMenu *file = new QPopupMenu( this );
	file->insertItem( p1, tr("��(&O)"), this, SLOT(open()), CTRL+Key_O );
	file->insertItem( p2, tr("�½�(&N)"), this, SLOT(news()), CTRL+Key_N );
	file->insertItem( p3, tr("����(&S)"), this, SLOT(save()), CTRL+Key_S );
	file->insertItem( tr("�ر�(&W)"), this, SLOT(closeDoc()), CTRL+Key_W );
	file->insertSeparator();
	file->insertItem( tr("��ӡ(&P)"), print, CTRL+Key_P );
	file->insertSeparator();
	file->insertItem( tr("�˳�(&x)"),  qApp, SLOT(quit()), CTRL+Key_Q );

	//�����༭�˵�
	QPopupMenu *edit = new QPopupMenu( this );
	int undoID = edit->insertItem( tr("����(&U)"), this, SLOT(undo()) );
	int redoID = edit->insertItem( tr("�ظ�(&R)"), this, SLOT(redo()) );
	edit->setItemEnabled( undoID, FALSE );
	edit->setItemEnabled( redoID, FALSE );

	//���������˵�
	QPopupMenu *help = new QPopupMenu( this );
	help->insertItem( tr("����(&H)..."), this, SLOT(about()), CTRL+Key_H );
	help->insertItem( tr("����&Qt ..."), this, SLOT(aboutQt()) );

	menubar = new QMenuBar( this );
	menubar->insertItem( tr("�ļ�(&F)"), file );
	menubar->insertItem( tr("�༭(&E)"), edit );
	menubar->insertSeparator();
	menubar->insertItem( tr("����(&H)"), help );
	menubar->setSeparator( QMenuBar::InWindowsStyle );
	vbox->addWidget(menubar);

	//stretch the vbox
	vbox->addStretch(0);

	//����״̬��
	QStatusBar *sbar = new QStatusBar(this);
	vbox->addWidget(sbar);
	sbar->message(tr("�˵���ʾ, ����Կ�ݼ�...")); 

	connect( this,  SIGNAL(explain(const QString&)),
		sbar, SLOT(message(const QString&)) );

}

void MenuDemo::printer()
{   
    emit explain( "File/Printer/Print selected" );
}   
    
void MenuDemo::file()
{   
    emit explain( "File/Printer/Print To File selected" );
}

void MenuDemo::fax()
{
    emit explain( "File/Printer/Print To Fax selected" );
}

void MenuDemo::printerSetup()
{
    emit explain( "File/Printer/Printer Setup selected" );
}

void MenuDemo::open()
{
    emit explain( "File/Open selected" );
}


void MenuDemo::news()
{
    emit explain( "File/New selected" );
}

void MenuDemo::save()
{
    emit explain( "File/Save selected" );
}

void MenuDemo::closeDoc()
{
    emit explain( "File/Close selected" );
}


void MenuDemo::undo()
{
    emit explain( "Edit/Undo selected" );
}


void MenuDemo::redo()
{
    emit explain( "Edit/Redo selected" );
}


void MenuDemo::about()
{
    QMessageBox::about( this, "Qt Menu Example",
                        "This example demonstrates simple use of Qt menus.\n"
                        "You can cut and paste lines from it to your own\n"
                        "programs." );
}


void MenuDemo::aboutQt()
{
    QMessageBox::aboutQt( this, "Qt Menu Example" );
}




