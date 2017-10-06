
	/* File: khtml.cpp */

	#include "khtml.h"
	#include <qvbox.h>
	#include <qlineedit.h>
	#include <kapp.h>
	#include <kmenubar.h>
	#include <ktoolbar.h>
	#include <klocale.h>
	#include <khtml_part.h>
	#include <dcopclient.h>
	#include <kiconloader.h>

	#define TOOLBAR_ID_ADDBOOKMARK 1
	#define TOOLBAR_ID_BACK 2
	#define TOOLBAR_ID_QUIT 3
      
	MainWindow::MainWindow ( char * name ) : KTMainWindow ( name )
	{
		//�˵���
		QPopupMenu * filemenu = new QPopupMenu;
		filemenu->insertItem( i18n( "&Quit" ), kapp, SLOT(quit() ) );
		QString about = i18n("Browser 1.0\n\n"
                      "(C) 2000 Yu Mingjian\n"
                      "yumj@opencjk.org\n");
		QPopupMenu *helpmenu = helpMenu(about);
		KMenuBar * menu = new KMenuBar( this );
		menu->insertItem( i18n( "&File" ), filemenu);
		menu->insertSeparator();
		menu->insertItem(i18n("&Help"), helpmenu);
		setMenu( menu );

		//��ť��
		KToolBar *toolbar=new KToolBar(this);
		toolbar->insertButton(BarIcon("reload"), TOOLBAR_ID_ADDBOOKMARK,
			SIGNAL(clicked(int)),this,SLOT(bookLocation()),TRUE,
			i18n("Add to Bookmarks"));
		toolbar->insertButton(BarIcon("back"), TOOLBAR_ID_BACK,
			SIGNAL(clicked(int)),this,SLOT(gotoPreviousPage()),
			FALSE, i18n("Back to previous page"));
		toolbar->insertButton(BarIcon("exit"), TOOLBAR_ID_QUIT,
			SIGNAL(clicked(int)),kapp,SLOT(quit()),TRUE,
			i18n("Quit the application")); 
		addToolBar(toolbar);

		//��������: vbox ������������HTML�����
		QVBox * vbox = new QVBox ( this );

		//������: URL ��
		location = new QLineEdit ( vbox );
		location->setText( "http://www.opencjk.org/" );

		//�����
		browser=new KHTMLPart( vbox );
		browser->openURL( location->text() );

		//�������ص�
		connect( location , SIGNAL( returnPressed() ),
			this, SLOT( changeLocation() ) );
		//��������ӻص�
		connect( browser->browserExtension(),
			SIGNAL( openURLRequest( const KURL &, const KParts::URLArgs & ) ),
			this, SLOT( openURLRequest(const KURL &, const KParts::URLArgs & ) ) );
		setView( vbox );
	}                                                                               

	void MainWindow::changeLocation()
	{
		browser->openURL( location->text() );
	} 

	void MainWindow::openURLRequest(const KURL &url, const KParts::URLArgs & )
	{
		location->setText(url.url());
		changeLocation();
	} 

	void MainWindow::gotoPreviousPage()
	{
		location->setText( history.pop() );
		if (history.isEmpty()) 
			toolBar()->setItemEnabled( TOOLBAR_ID_BACK, FALSE);
		browser->openURL( location->text() );
	}

	void MainWindow::bookLocation()
	{
		DCOPClient *client=kapp->dcopClient();
		QByteArray params;
		QDataStream stream(params, IO_WriteOnly);
		stream << location->text();
		client->send("", "bookmarkList", "add(QString)", params);
	}
