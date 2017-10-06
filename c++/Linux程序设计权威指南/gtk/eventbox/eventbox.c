
	/* File: eventbox.c */

	#include <gtk/gtk.h>

	void callback_enter(GtkWidget *w, gpointer data)
	{
		g_print("pointer entered.\n");
	}

	void callback_leave(GtkWidget *w, gpointer data)
	{
		g_print("pointer left.\n");
	}

	int main( int argc, char *argv[] )
	{
		GtkWidget *window;
		GtkWidget *event_box;
		GtkWidget *label;
		GtkTooltips *tips;
     

		//��ʼ��
		gtk_set_locale();
		gtk_init (&argc, &argv);
     
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title (GTK_WINDOW (window), "Event Box");
		gtk_signal_connect (GTK_OBJECT (window), "destroy",
                         GTK_SIGNAL_FUNC (gtk_exit), NULL);
		gtk_container_set_border_width (GTK_CONTAINER (window), 10);
     
		//�����¼�������
		event_box = gtk_event_box_new ();
		gtk_container_add (GTK_CONTAINER(window), event_box);
		gtk_widget_show (event_box);


		//������ǩ
		label = gtk_label_new ("���˱�ǩ�˳�!");
		gtk_container_add (GTK_CONTAINER (event_box), label);
		gtk_widget_show (label);

		//�����¼��и���Ȥ���¼�:�����ͽ����뿪�¼�
		gtk_widget_set_events (event_box, 
			GDK_BUTTON_PRESS_MASK|
			GDK_ENTER_NOTIFY_MASK|
			GDK_LEAVE_NOTIFY_MASK );
		gtk_signal_connect (GTK_OBJECT(event_box), "button_press_event",
                    GTK_SIGNAL_FUNC (gtk_exit), NULL);
		gtk_signal_connect (GTK_OBJECT(event_box), "enter-notify-event",
                    GTK_SIGNAL_FUNC (callback_enter), NULL);
		gtk_signal_connect (GTK_OBJECT(event_box), "leave-notify-event",
                    GTK_SIGNAL_FUNC (callback_leave), NULL);

     
		//�����¼��ж�Ӧ�������״
		gtk_widget_realize (event_box);
		gdk_window_set_cursor (event_box->window, 
			gdk_cursor_new (GDK_HAND1));

		tips = gtk_tooltips_new();
		gtk_tooltips_set_tip(tips, event_box, "����ǩ�����¼���!", NULL);
	
		gtk_widget_show (window);
		gtk_main ();
		return(0);
	}
