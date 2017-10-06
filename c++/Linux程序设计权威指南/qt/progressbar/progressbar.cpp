
#include "progressbar.h"

#include <qradiobutton.h>
#include <qpushbutton.h>
#include <qprogressbar.h>
#include <qlayout.h>
#include <qtimer.h>
#include <qtextcodec.h>

ProgressBarDemo::ProgressBarDemo( QWidget *parent, const char *name )
    : QWidget( parent, name )
{

	//��������
	QVBoxLayout *vbox = new QVBoxLayout(this);
	QHBoxLayout *hbox = new QHBoxLayout(vbox); 

	//����������ť
	start = new QPushButton( tr("��ʼ(&S)"), this );
	hbox->addWidget( start );
	reset = new QPushButton( tr("��λ(&R)"), this );
	hbox->addWidget( reset );
    
	vbox->addStretch(0);

	//����������
	progressbar = new QProgressBar( 100, this );
	progressbar->setCenterIndicator(TRUE);
	vbox->addWidget( progressbar );
	connect( start, SIGNAL( clicked() ), this, SLOT( slotStart() ) );
	connect( reset, SIGNAL( clicked() ), this, SLOT( slotReset() ) );

	//������ʱ��
	timer = new QTimer(this);
	connect( timer, SIGNAL( timeout() ), this, SLOT( slotTimeout() ) );
	start->setFixedWidth( 80 );
	reset->setFixedWidth( 80 );

}

void ProgressBarDemo::slotStart()
{
	//������1000����
	progressbar->setTotalSteps( 1000 );

	//���������û�й���
	if ( !timer->isActive() ) {
		timer->start( 1 );	//ÿ1���볬ʱ
		start->setText( tr("��ͣ(&P)") );
	} else {	//����
		timer->stop();
		start->setText( tr("����(&C)") );
	}
}

void ProgressBarDemo::slotReset()
{
	//��λ
	timer->stop();

	start->setText( tr("��ʼ(&S)") );
	start->setEnabled( TRUE );

	progressbar->reset();
}

void ProgressBarDemo::slotTimeout()
{
	int p = progressbar->progress();

	//�����������ͷ
	if ( p == progressbar->totalSteps() )  {
		start->setText( tr("��ʼ(&S)") );
		start->setEnabled( FALSE );
		return;
	}
    
	//����
	progressbar->setProgress( ++p );
}
