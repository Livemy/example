

	/* File: toolbar.c */
	#include <gtk/gtk.h>
	#include "gtk.xpm"

	gint delete_event (GtkWidget *widget, GdkEvent *event, gpointer data)
	{
		gtk_main_quit ();
		return(FALSE);
	}

	void cb_button (GtkWidget *widget, gpointer data)
	{
		g_print("button pressed.\n");
	}

	int main (int argc, char *argv[])
	{
		GtkWidget* dialog;
		GtkWidget* handlebox;
		GtkWidget* close_button, *backward_button, 
			   *forward_button, *refresh_button;
		GtkWidget* tooltips_button;
		GtkWidget* entry;

		GtkWidget * toolbar;
		GdkPixmap * icon;
		GdkBitmap * mask;
		GtkWidget * iconw;

		//��ʼ��
		gtk_set_locale();
		gtk_init (&argc, &argv);
   
		//�����Ի���
		dialog = gtk_dialog_new ();
		gtk_window_set_title (GTK_WINDOW(dialog) , "GTKToolbar");
		gtk_widget_set_usize(GTK_WIDGET ( dialog ) , 600 , 300 );
		GTK_WINDOW ( dialog ) ->allow_shrink = TRUE;

		//�رմ�����Ϊ
		gtk_signal_connect ( GTK_OBJECT ( dialog ), "delete_event",
			GTK_SIGNAL_FUNC(delete_event), NULL);

		//ʵ�ֶԻ���, �Ա�����ͼ��
		gtk_widget_realize ( dialog );

		//handle box �Ǹ��߼�������, ������ʹ��ť�ʹ��ڷ���
		handlebox = gtk_handle_box_new ();
		gtk_box_pack_start ( GTK_BOX ( GTK_DIALOG(dialog)->vbox ),
			handlebox, FALSE, FALSE, 5 );

		//���������, �����ı���ͼ��ť�İ�ť��
		toolbar = gtk_toolbar_new ( GTK_ORIENTATION_HORIZONTAL,
			GTK_TOOLBAR_BOTH );
		gtk_container_set_border_width(GTK_CONTAINER ( toolbar ) , 5 );
		gtk_toolbar_set_space_size ( GTK_TOOLBAR ( toolbar ), 5);
		gtk_toolbar_set_button_relief( GTK_TOOLBAR ( toolbar ),
			GTK_RELIEF_NONE);
		gtk_container_add ( GTK_CONTAINER ( handlebox ) , toolbar );

		//����ͼ��
		icon = gdk_pixmap_create_from_xpm_d(dialog->window, &mask,
			&dialog->style->white, gtk_xpm);
		iconw = gtk_pixmap_new (icon, mask);
		//������ť
		close_button = gtk_toolbar_append_item(GTK_TOOLBAR (toolbar),
			"�ر�", "�رճ���", "Private", iconw,
			GTK_SIGNAL_FUNC (delete_event), NULL );
		gtk_toolbar_append_space(GTK_TOOLBAR ( toolbar ) );
		gtk_widget_set_usize(GTK_WIDGET(close_button) , 60 , 60 );

		//������ť
		iconw = gtk_pixmap_new ( icon, mask );
		backward_button=gtk_toolbar_append_item(GTK_TOOLBAR(toolbar),
			"ǰ��", "��ǰ��ҳ", "Private", iconw,
			GTK_SIGNAL_FUNC (cb_button), backward_button);
		gtk_toolbar_append_space ( GTK_TOOLBAR ( toolbar ) );

		//������ť
		iconw = gtk_pixmap_new ( icon, mask );
		forward_button=gtk_toolbar_append_item(GTK_TOOLBAR(toolbar),
			"ˢ��", "ˢ�µ�ǰҳ", "Private", iconw,
			GTK_SIGNAL_FUNC (cb_button), forward_button);
		gtk_toolbar_append_space ( GTK_TOOLBAR ( toolbar ) );

		//����������
		entry = gtk_entry_new ();
		gtk_toolbar_append_widget(GTK_TOOLBAR (toolbar), entry, 
			"������ for fun", "Private" );
		gtk_widget_show ( entry );


		gtk_widget_show ( toolbar );
		gtk_widget_show (handlebox);
		gtk_widget_show ( dialog );

		gtk_main ();
		return 0;
	}


