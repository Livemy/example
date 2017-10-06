#include "listbox.h"
#include <qlabel.h>
#include <qtextcodec.h>
#include <qlistbox.h>
#include <qstatusbar.h>
#include <qlayout.h>

ListDemo::ListDemo( QWidget *parent, const char *name )
    : QWidget( parent, name )
{
	//��������
	QVBoxLayout *vbox = new QVBoxLayout(this);

	//�����б��
	list = new QListBox( this );
	list->setFocusPolicy( QWidget::StrongFocus );
	vbox->addWidget(list);

	//������Ŀ
	list->insertItem(tr("��ʾ��"));
	list->insertItem(tr("����"));
	list->insertItem(tr("���"), 1);
	list->insertItem(QPixmap("qtlogo.gif"));
	for(int i=0; i<5; i++)
		list->insertItem(tr("���ǵ� ") + QString::number(i+4) 
			+ tr(" ��"));
	
	list->setCurrentItem(5);

	//�����źźͲ�۵�����
	sbar = new QStatusBar(this);
	vbox->addWidget(sbar);

	connect(list, SIGNAL(highlighted(int)), 
		this, SLOT(showMessage(int)));

	
}

void ListDemo::showMessage(int idx)
{
	sbar->message(tr("��ѡ���˵�") + QString::number(idx)
		+ tr("��:") + list->currentText());
}

