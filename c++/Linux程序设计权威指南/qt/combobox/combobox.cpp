#include "combobox.h"
#include <qtextcodec.h>
#include <qcombobox.h>
#include <qstatusbar.h>
#include <qpixmap.h>
#include <qlayout.h>

ComboboxDemo::ComboboxDemo( QWidget *parent, const char *name )
    : QWidget( parent, name )
{
	//��������
	QVBoxLayout *vbox = new QVBoxLayout(this);

	//����ComboBox
	combo = new QComboBox(TRUE, this);
	combo->setInsertionPolicy(QComboBox::AtTop);
	vbox->addWidget(combo);

	//������Ŀ
	int i;
	for ( i = 0; i < 5; i++ ) {
		combo->insertItem(QString( tr("Combobox ��Ŀ %1") ).arg( i ));
	}
	combo->insertItem( QPixmap( "fileopen.xpm" ), tr("QT ��Ʒ") );

	//
	vbox->addStretch(0);

	//�����źźͲ�۵�����
	sbar = new QStatusBar(this);
	sbar->message(tr("�������������������..."));
	vbox->addWidget(sbar);

	// ��������
	connect( combo, SIGNAL( activated( const QString & ) ), 
		sbar, SLOT( message( const QString & ) ) );
	connect( combo, SIGNAL( highlighted( const QString & ) ), 
		sbar, SLOT( message( const QString & ) ) );

}

