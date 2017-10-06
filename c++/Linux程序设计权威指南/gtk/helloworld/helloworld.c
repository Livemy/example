	/* File: helloworld.c */

	#include <gtk/gtk.h>

	/* This is a callback function. The data arguments are ignored
 	* in this example. More on callbacks below. */
	void hello( GtkWidget *widget, gpointer   data )
	{
		g_print ("Hello World\n");
	}

	gint delete_event( GtkWidget *widget,
                    GdkEvent  *event,
                    gpointer   data )
	{
		//��ӡ��Ϣ
		g_print ("delete event occurred\n");

		//�������FALSE, GTK������"destroy"�ź�; �������TRUE,
		//���øô��ڹر�
		return(TRUE);
	}

	void destroy( GtkWidget *widget, gpointer   data )
	{
		gtk_main_quit();
	}

	int main( int   argc, char *argv[] )
	{
		//GtkWidget �� Widget������
		GtkWidget *window;
		GtkWidget *button;
     
		//gtk ��ʼ��
		gtk_init(&argc, &argv);
     
		//�����´���
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
     
		//��ʹ�ô��ڹ������رմ���ʱ, ������ delete_event() ����
		//�����������ݵĲ����� NULL
		gtk_signal_connect (GTK_OBJECT (window), "delete_event",
			GTK_SIGNAL_FUNC (delete_event), NULL);
     
		//�� "destroy" �¼����źŴ�������ϵ����
		gtk_signal_connect (GTK_OBJECT (window), "destroy",
			GTK_SIGNAL_FUNC (destroy), NULL);
     
		//���ô��ڵı߽���
		gtk_container_set_border_width (GTK_CONTAINER (window), 10);
     
		//����һ����ǩ��"Hello World"�İ�ť
		button = gtk_button_new_with_label ("Hello World");
     
		//����ť������ʱ, �����յ�"clicked"�ź�, ������ hello()����
		gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (hello), NULL);

		//����ť������ʱ, ���� gtk_widget_destroy(window)�رմ���.
		//���ｫ���� "destroy" �ź�
		gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (gtk_widget_destroy),
			GTK_OBJECT (window));
     
		//�Ѱ�ť���붥��������
		gtk_container_add (GTK_CONTAINER (window), button);

		//��ʾ��ť
		gtk_widget_show (button);
     
		//��ʾ��������
		gtk_widget_show (window);

		//�����¼�ѭ��
		gtk_main ();
     
		return(0);
	}

