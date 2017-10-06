
	/* File: entry.c */

	#include <stdio.h>
	#include <gtk/gtk.h>

	void enter_callback( GtkWidget *widget, GtkWidget *entry )
	{
		gchar *entry_text;
		entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
		printf("Entry contents: %s\n", entry_text);
	}

	void entry_toggle_editable( GtkWidget *checkbutton, GtkWidget *entry )
	{
		gtk_entry_set_editable(GTK_ENTRY(entry), 
			GTK_TOGGLE_BUTTON(checkbutton)->active);
	}

	void entry_toggle_visibility( GtkWidget *checkbutton, GtkWidget *entry )
	{
		gtk_entry_set_visibility(GTK_ENTRY(entry), 
			GTK_TOGGLE_BUTTON(checkbutton)->active);
	}

	int main( int   argc, char *argv[] )
	{

		GtkWidget *window;
		GtkWidget *vbox, *hbox;
		GtkWidget *entry;
		GtkWidget *button;
		GtkWidget *check;

		gtk_set_locale();
		gtk_init (&argc, &argv);

		//��������
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_widget_set_usize( GTK_WIDGET (window), 200, 100);
		gtk_window_set_title(GTK_WINDOW (window), "GTK Entry");
		gtk_signal_connect(GTK_OBJECT (window), "delete_event",
                   	(GtkSignalFunc) gtk_exit, NULL);

		//��������
		vbox = gtk_vbox_new (FALSE, 0);
		gtk_container_add (GTK_CONTAINER (window), vbox);
		gtk_widget_show (vbox);

		//����������, ������50
		entry = gtk_entry_new_with_max_length (50);
		//�����»س���ʱ, ���� enter_callback
		gtk_signal_connect(GTK_OBJECT(entry), "activate",
                   	GTK_SIGNAL_FUNC(enter_callback),
                   	entry);
		//���������ı�����Ϊ"���"
		gtk_entry_set_text (GTK_ENTRY (entry), "���");
		//���ں���, "��Һ�!"
		gtk_entry_append_text (GTK_ENTRY (entry), ",��Һ�!");
		//ѡ�����������
		gtk_entry_select_region (GTK_ENTRY (entry), 
			0, GTK_ENTRY(entry)->text_length);
		gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
		gtk_widget_show (entry);

		//����������ѡ��ť
		hbox = gtk_hbox_new (FALSE, 0);
		gtk_container_add (GTK_CONTAINER (vbox), hbox);
		gtk_widget_show (hbox);
                                   
		check = gtk_check_button_new_with_label("�ɱ༭");
		gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
		gtk_signal_connect (GTK_OBJECT(check), "toggled",
                         GTK_SIGNAL_FUNC(entry_toggle_editable), entry);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), TRUE);
		gtk_widget_show (check);
     
		check = gtk_check_button_new_with_label("���ݿɼ�");
		gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
		gtk_signal_connect (GTK_OBJECT(check), "toggled",
                         GTK_SIGNAL_FUNC(entry_toggle_visibility), entry);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), TRUE);
		gtk_widget_show (check);
                                    
		button = gtk_button_new_with_label ("�˳�");
		gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
                                GTK_SIGNAL_FUNC(gtk_exit),
                                GTK_OBJECT (window));
		gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);
		GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
		gtk_widget_grab_default (button);
		gtk_widget_show (button);
     
		gtk_widget_show(window);

		gtk_main();
		return(0);
	}
