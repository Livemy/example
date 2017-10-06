
	/* File: combobox.c */

	#include <stdio.h>
	#include <gtk/gtk.h>
	#include <gtk/gtkcombo.h>

	GtkWidget *status;
	gint context_id;

	void cb_entry(GtkWidget *item, gpointer data)
	{
		char buf[80];
		sprintf(buf, "��ѡ����: %s", 
			gtk_entry_get_text(GTK_ENTRY(data)));
		gtk_statusbar_push( GTK_STATUSBAR(status), context_id, buf);
	}

	int main( int   argc, char *argv[] )
	{
		GtkWidget *window;
		GtkWidget *combo;
		GList *list = NULL;
		GtkWidget *vbox, *hbox;
		GtkWidget *label;

		//��ʼ��
		gtk_set_locale();
		gtk_init (&argc, &argv);

		//����������
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_widget_set_usize (GTK_WIDGET (window), 320, 200);
		gtk_window_set_title (GTK_WINDOW (window), "ComboBox Test");
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
		//�����˵��б�
		list = g_list_append(list, "��ʾ��");
		list = g_list_append(list, "���");
		list = g_list_append(list, "����");
		//ComboBox
		combo = gtk_combo_new();
		//���ò˵�
		gtk_combo_set_popdown_strings(GTK_COMBO(combo), list);
                gtk_signal_connect(GTK_OBJECT(GTK_COMBO(combo)->entry),
                        "changed", GTK_SIGNAL_FUNC(cb_entry), 
			GTK_COMBO(combo)->entry);
		//�ͷ��ڴ�
		g_list_free(list);

		gtk_box_pack_start (GTK_BOX (hbox), combo, FALSE, FALSE, 0);
		gtk_widget_show (combo);

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

