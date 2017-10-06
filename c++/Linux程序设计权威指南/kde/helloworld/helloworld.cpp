
	/* File: helloworld.cpp */
	#include <kapp.h>
	#include <klocale.h>
	#include <qpushbutton.h>

	int main( int argc, char **argv )
	{
		KApplication app(argc, argv , "HelloWorld"); 

		//������ť
		QPushButton *button = new QPushButton(i18n("Hello World!"), 0);
		button->setAutoResize( TRUE ); 

		//������ť�ص�
		QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));

		//�Ѱ�ť�������Ϊ������
		app.setMainWidget(button);
		button->show(); 

		//����ѭ��
		return app.exec();
	}
