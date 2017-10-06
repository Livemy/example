#include "button.h"

#include <qlabel.h>
#include <qtextcodec.h>
#include <qpixmap.h>
#include <qmovie.h>
#include <qbuttongroup.h>
#include <qlayout.h>
#include <qradiobutton.h>
#include <qcheckbox.h>
#include <qpushbutton.h>

LabelButton::LabelButton( QWidget *parent, const char *name )
    : QWidget( parent, name)
{
	//�����������
	QVBoxLayout *vbox = new QVBoxLayout( this );
	QHBoxLayout *box1 = new QHBoxLayout( vbox );
	QHBoxLayout *box2 = new QHBoxLayout( vbox );
	QHBoxLayout *box3 = new QHBoxLayout( vbox );


	//������ǩ
	box1->setAlignment( AlignLeft );
	QLabel *label1 = new QLabel(tr("��ǩ�Ͱ�ť��ʾ"), this);
	label1->setFrameStyle( QFrame::Panel | QFrame::Sunken );
	box1->addWidget( label1 );
	QLabel *label2 = new QLabel(this);
	label2->setPixmap(QPixmap("qtlogo.gif"));
	box1->addWidget( label2 );
	QLabel *label3 = new QLabel(this);
	label3->setMovie(QMovie("trolltech.gif"));
	box1->addWidget( label3 );


	//������һ��: ��ѡ��ť��
	QButtonGroup *grp1 = new QButtonGroup(1, QGroupBox::Horizontal, 
		tr("��ѡ��ť��(QCheckBox)"), this );
	box2->addWidget( grp1 );
	grp1->setExclusive( FALSE );
	//�����������������ť
	(void)new QCheckBox( "&Checkbox 1", grp1 );
	QCheckBox *cb12 = new QCheckBox( "C&heckbox 2", grp1 );
	cb12->setPixmap(QPixmap("qtlogo.gif"));
	cb12->setChecked( TRUE );
	QCheckBox *cb13 = new QCheckBox( tr("����״̬�İ�ť(&S)"), grp1 );
	cb13->setTristate( TRUE );
	cb13->setChecked( TRUE );

	//�����ڶ���: ��ѡ��ť��
	QButtonGroup *grp2 = new QButtonGroup( 1, QGroupBox::Horizontal, 
		tr("��ѡ��ť��(QRadioButton)"), this);
	box2->addWidget( grp2 );
	grp2->setExclusive( TRUE );
	//����������ѡ��ť
	QRadioButton *rb11 = new QRadioButton( "&Radiobutton 1", grp2 );
	rb11->setChecked( TRUE );
	(void)new QRadioButton( "R&adiobutton 2", grp2 );
	(void)new QRadioButton( "Ra&diobutton 3", grp2 );


	//����������
	QButtonGroup *grp3 = new QButtonGroup( 1, QGroupBox::Horizontal, 
		tr("��ѡ��ť��, ��ʾ��ť��ֹ״̬"), this );
	box3->addWidget( grp3 );
	grp3->setRadioButtonExclusive( TRUE );
	rb21 = new QRadioButton( "Rad&iobutton 1", grp3 );
	rb22 = new QRadioButton( "Radi&obutton 2", grp3 );
	rb23 = new QRadioButton( "Radio&button 3", grp3 );
	rb23->setChecked( TRUE );

	state = new QCheckBox( tr("���ѡ��ť(&n)"), grp3 );
	state->setChecked( TRUE );
	//���ûص�
	connect( state, SIGNAL( clicked() ), 
		this, SLOT( slotChangeGrp3State() ) );


	//����������: ��ͨ��ť���л���ť
	QGroupBox *grp4 = new QButtonGroup( 1, QGroupBox::Horizontal, 
		tr("��ͨ��ť���л���ť"), this );
	box3->addWidget( grp4 );
	(void)new QPushButton( tr("��ͨ��ť(&P)"), grp4 );
	QPushButton *tb = new QPushButton( tr("�л���ť(&T)"), grp4 );
	tb->setToggleButton( TRUE );
	tb->setOn( TRUE );
}

void LabelButton::slotChangeGrp3State()
{
	rb21->setEnabled( state->isChecked() );
	rb22->setEnabled( state->isChecked() );
	rb23->setEnabled( state->isChecked() );
}
