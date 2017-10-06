
	/* File: optmenu.c */

	#include <stdio.h>
	#include <gtk/gtk.h>

	GtkWidget *status;
	gint context_id;

	void cb_menu_select(GtkWidget *item, gpointer data)
	{
		char buf[80];
		sprintf(buf, "��ѡ����: %d", (gint) data);
		gtk_statusbar_push( GTK_STATUSBAR(status), context_id, buf);
	}

	int main( int   argc, char *argv[] )
	{
		GtkWidget *window;
		GtkWidget *optmenu, *menu, *item;
		GtkWidget *vbox, *hbox;
		GtkWidget *label;

		//��ʼ��
		gtk_set_locale();
		gtk_init (&argc, &argv);

		//����������
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_widget_set_usize (GTK_WIDGET (window), 320, 200);
		gtk_window_set_title (GTK_WINDOW (window), "GTK Menu Test");
		gtk_signal_connect (GTK_OBJECT (window), "delete_event",
			(GtkSignalFunc) gtk_main_quit, NULL);

		//������ֱ����
		vbox = gtk_vbox_new (FALSE, 0);
		gtk_container_add (GTK_CONTAINER (window), vbox);
		gtk_widget_show (vbox);

		hbox = gtk_hbox_new(FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);
		gtk_widget_show(hbox);
		//��ǩ
		label = gtk_label_new("��ѡ����Ŀ:");
		gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 5);
		gtk_widget_show(label);
		//ѡ��˵�
		optmenu = gtk_option_menu_new();
		menu = gtk_menu_new();
		item = gtk_menu_item_new_with_label("��ʾ��");
		gtk_signal_connect (GTK_OBJECT(item), "activate",
			GTK_SIGNAL_FUNC(cb_menu_select), GINT_TO_POINTER(0));
		gtk_widget_show (item);
		gtk_menu_append (GTK_MENU (menu), item);
		item = gtk_menu_item_new_with_label("���");
		gtk_signal_connect (GTK_OBJECT(item), "activate",
			GTK_SIGNAL_FUNC(cb_menu_select), GINT_TO_POINTER(1));
		gtk_widget_show (item);
		gtk_menu_append (GTK_MENU (menu), item);
		item = gtk_menu_item_new_with_label("����");
		gtk_signal_connect (GTK_OBJECT(item), "activate",
			GTK_SIGNAL_FUNC(cb_menu_select), GINT_TO_POINTER(2));
		gtk_widget_show (item);
		gtk_menu_append (GTK_MENU (menu), item);

		//����˵�
		gtk_option_menu_set_menu (GTK_OPTION_MENU(optmenu), menu);
		//���õ�2��Ϊȱʡ��
		gtk_option_menu_set_history (GTK_OPTION_MENU(optmenu), 2);
		gtk_box_pack_start (GTK_BOX (hbox), optmenu, FALSE, FALSE, 0);
		gtk_widget_show (optmenu);

		//����״̬��
		status = gtk_statusbar_new();
		//���뵽���·�
		gtk_box_pack_end(GTK_BOX (vbox), status, FALSE, FALSE, 0);
		gtk_widget_show (status);

		//����״̬���� ID
		context_id = gtk_statusbar_get_context_id(
			GTK_STATUSBAR(status), "Statusbar example");

		gtk_widget_show (window);

		gtk_main ();
		return(0);
	}

