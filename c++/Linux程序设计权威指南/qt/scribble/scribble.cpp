
#include "scribble.h"
#include <qapplication.h>
#include <qpen.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qwidget.h>

ScribbleDemo::ScribbleDemo()
{
	//����͸��ɫ����
	setBackgroundMode( NoBackground );
}


//�����ָ�밴��ʱ, ��¼���λ��
void ScribbleDemo::mousePressEvent( QMouseEvent* event )
{
	last = event->pos();
	pen = QPen(Qt::red, 3);
}


//�����ָ���ƶ�ʱ, ͬʱ������ͻ������ڻ�ͼ
void ScribbleDemo::mouseMoveEvent( QMouseEvent* event )
{
	//������������, һ�����ڴ���, һ�����ڻ�����
	QPainter windowpainter;
	QPainter bufferpainter;

	//��ʼ
	windowpainter.begin( this );
	bufferpainter.begin( &buffer );

	//���ú�ɫ�ı�, ���Ϊ��������
	windowpainter.setPen( pen );
	bufferpainter.setPen( pen );
	windowpainter.drawLine( last, event->pos() );
	bufferpainter.drawLine( last, event->pos() );

	//����
	windowpainter.end();
	bufferpainter.end();

	//��¼λ��
	last = event->pos();
}

//����Ҫ�ػ�ʱ, �ѻ������ڵ����ݿ�����������
void ScribbleDemo::paintEvent( QPaintEvent* event )
{
	bitBlt( this, 0, 0, &buffer );
}


//�����ڳߴ�ı�ʱ, ʹ�û��������������Ǻʹ��ڳߴ�һ����.
//Ϊ�˲���ʧ��Ϣ, �ѻ�������������, Ȼ��ı仺�����Ĵ�С, 
//�ٰѱ�������ݿ�������������.
void ScribbleDemo::resizeEvent( QResizeEvent* event )
{
	int w = width() > buffer.width() ?  width() : buffer.width();
	int h = height() > buffer.height() ?  height() : buffer.height();

	QPixmap tmp( buffer );
	buffer.resize( w, h );
	buffer.fill( colorGroup().base() );
	bitBlt( &buffer, 0, 0, &tmp, 0, 0, tmp.width(), tmp.height() );
}

