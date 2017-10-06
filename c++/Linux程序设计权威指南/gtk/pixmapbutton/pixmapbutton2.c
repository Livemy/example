	/* File: pixmapbutton.c */

	#include "info.xpm"
	#include <gtk/gtk.h>

	// ����һ��ˮƽ����, ������һ��ͼ���һ����ǩ
	GtkWidget *xpm_label_box( GtkWidget *parent,
                           gchar     **xpm_data,
                           gchar     *label_text )
	{
		GtkWidget *box;
		GtkWidget *label;
		GtkWidget *pixmapwid;
		GdkPixmap *pixmap;
		GdkBitmap *mask;
		GtkStyle *style;

		//����ˮƽ����
		box = gtk_hbox_new(FALSE, 0);
 		gtk_container_set_border_width(GTK_CONTAINER(box), 2);

		//��ȡ��ť��style, �Ա�ȡ�ñ�����ɫ 
		style = gtk_widget_get_style(parent);

		//���� pixmap
		pixmap = gdk_pixmap_create_from_xpm_d(parent->window, &mask,
			&style->bg[GTK_STATE_NORMAL], xpm_data);
		pixmapwid = gtk_pixmap_new(pixmap, mask);

		//������ǩ
		label = gtk_label_new(label_text);

		//��װpixmap�ͱ�ǩ
		gtk_box_pack_start(GTK_BOX (box), pixmapwid, FALSE, FALSE, 3);
		gtk_box_pack_start(GTK_BOX (box), label, FALSE, FALSE, 3);

		gtk_widget_show(pixmapwid);
		gtk_widget_show(label);

		return(box);
	}

	void callback(GtkWidget *widget, gpointer   data )
	{
		g_print ("Hello again - %s was pressed\n", (char *) data);
	}

	int main( int  argc, char *argv[] )
	{
		GtkWidget *window;
		GtkWidget *button;
		GtkWidget *box;

		//��ʼ��
		gtk_set_locale();
		gtk_init (&argc, &argv);

		//������������
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

		//���ô��ڹ��������ϵı���
		gtk_window_set_title (GTK_WINDOW (window), "ͼ��ť");

		gtk_signal_connect (GTK_OBJECT (window), "destroy",
                         GTK_SIGNAL_FUNC (gtk_exit), NULL);
		gtk_signal_connect (GTK_OBJECT (window), "delete_event",
                         GTK_SIGNAL_FUNC (gtk_exit), NULL);

		gtk_container_set_border_width (GTK_CONTAINER (window), 10);
		gtk_widget_realize(window);

		//����һ���յİ�ť
		button = gtk_button_new ();
		gtk_signal_connect (GTK_OBJECT (button), "clicked",
                         GTK_SIGNAL_FUNC (callback), (gpointer) "GTK ��ť");

		//������ť���
		box = xpm_label_box(window, penguin, "GTK ��ť");

		gtk_widget_show(box);

		gtk_container_add(GTK_CONTAINER(button), box);

		gtk_widget_show(button);

		gtk_container_add(GTK_CONTAINER (window), button);

		gtk_widget_show (window);

		gtk_main ();

		return(0);
	}

