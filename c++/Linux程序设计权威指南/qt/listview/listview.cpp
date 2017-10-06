#include "listview.h"
#include <qlabel.h>
#include <qtextcodec.h>
#include <qlistview.h>
#include <qlayout.h>

ListDemo::ListDemo( QWidget *parent, const char *name )
    : QWidget( parent, name )
{
	//��������
	QVBoxLayout *vbox = new QVBoxLayout(this);

	//���������б�
	QListView *listview = new QListView(this);
	vbox->addWidget(listview);

	//��������
	listview->addColumn( tr("����") );
	listview->addColumn( tr("��Ŀ����") );
	listview->addColumn( tr("����ֵ") );
	listview->setRootIsDecorated( TRUE );
	listview->setAllColumnsShowFocus(TRUE);

	//������Ŀ
	QListViewItem *application = new QListViewItem( listview, tr("Ӧ�ó���" ));
	QListViewItem *desktop = new QListViewItem( listview, tr("����" ));
	QListViewItem *network = new QListViewItem( listview, tr("����" ));

	QListViewItem* item;
	item = new QListViewItem(application, 
		tr("��¼������"), tr("���"), tr("��׼KDE"));
	item = new QListViewItem(application, 
		tr("�ļ�������"), tr("����"), tr("Times"));
	item = new QListViewItem(application, 
		tr("Web�����"), tr("Proxy"), tr("nothing.com"));

	item = new QListViewItem(desktop, 
		tr("����"), tr("���ڱ���"), tr("��ɫ"));
	item = new QListViewItem(desktop, 
		tr("��ɫ"), tr("������ɫ"), tr("����ɫ"));
	item = new QListViewItem(desktop, 
		tr("����"), tr("��������"), tr("8x16"));
	item = new QListViewItem(desktop, 
		tr("���"), tr("ȱʡ���"), tr("Motif"));


	item = new QListViewItem(network, 
		tr("��ַ"), tr("IP��ַ"), tr("192.168.1.1"));
	item = new QListViewItem(network, 
		tr("�ڵ���"), tr("����"), tr("localhost"));
	

}

