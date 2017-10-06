#include "edit.h"
#include <stdio.h>
#include <qlabel.h>
#include <qtextcodec.h>
#include <qlineedit.h>
#include <qmultilineedit.h>
#include <qvalidator.h>
#include <qlayout.h>


EditDemo::EditDemo( QWidget *parent, const char *name )
    : QWidget( parent, name )
{
	//�����������
	QGridLayout *grid = new QGridLayout(this, 5, 2, 2, 2);

	//��ͨ������
	QLabel *label1 = new QLabel(tr("��ͨ������:"), this);
	grid->addWidget( label1 , 0, 0);
	QLineEdit *edit1 = new QLineEdit(tr("LineEdit����"), this);
	edit1->setFocus();
	edit1->setCursorPosition(4);
	grid->addWidget( edit1, 0, 1);

	//ֻ��������
	QLabel *label2 = new QLabel(tr("<u><font color=#ff0000>ֻ��������:</font></u>"), this);
	grid->addWidget( label2 , 1, 0);
	QLineEdit *edit2 = new QLineEdit(tr("ֻ��:)"), this);
	edit2->setReadOnly(TRUE);
	grid->addWidget( edit2, 1, 1);

	//����ʾ������
	QLabel *label3 = new QLabel(tr("��������ģʽ:"), this);
	grid->addWidget( label3 , 2, 0);
	QLineEdit *edit3 = new QLineEdit(this);
	edit3->setEchoMode(QLineEdit::Password);
	grid->addWidget( edit3, 2, 1);

	//��������У��
	QLabel *label4 = new QLabel(tr("��������У��:"), this);
	grid->addWidget( label4 , 3, 0);
	QLineEdit *edit4 = new QLineEdit(this);
	edit4->setValidator( new QIntValidator( edit4 ) );
	grid->addWidget( edit4, 3, 1);
	
	//���б༭��
	QMultiLineEdit *multiedit = new QMultiLineEdit(this);
	grid->addMultiCellWidget(multiedit, 4, 4, 0, 1);

}
