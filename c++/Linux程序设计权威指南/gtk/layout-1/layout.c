	/* File: layout.c */

	#include <gtk/gtk.h>

	void destroy( GtkWidget *widget, gpointer   data )
	{
		gtk_main_quit();
	}

	int main( int   argc, char *argv[] )
	{
		//GtkWidget �� Widget������
		GtkWidget *window;
		GtkWidget *hbox;
		GtkWidget *label, *entry;
     
		//����Locale
		gtk_set_locale();

		//gtk ��ʼ��
		gtk_init(&argc, &argv);
     
		//�����´���
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
     
		//�� "destroy" �¼����źŴ�������ϵ����
		gtk_signal_connect (GTK_OBJECT (window), "destroy",
			GTK_SIGNAL_FUNC(destroy), NULL);
     
		//���ô��ڵı߽���
		gtk_container_set_border_width (GTK_CONTAINER (window), 10);
     
		//����һ������, ����ˮƽ�ذ������
		hbox = gtk_hbox_new(FALSE, 0);
		//�Ѱ�ť���붥��������
		gtk_container_add (GTK_CONTAINER (window), hbox);
		gtk_widget_show(hbox);

		//����һ�������ı�ǩ, �����뵽hbox��
		label = gtk_label_new("������:");
		gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
		gtk_widget_show(label);
     
		//����һ��������, �����뵽hbox��
		entry = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);
		gtk_widget_show(entry);

		//��ʾ��������
		gtk_widget_show (window);

		//�����¼�ѭ��
		gtk_main ();
     
		return(0);
	}

