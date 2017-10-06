
	/* File: filesel.c */
	#include <gtk/gtk.h>

	//ѡ�����ļ�, ��ӡ�ļ���
	void file_ok_sel( GtkWidget *w, GtkFileSelection *fs )
	{
		g_print ("%s\n", 
		gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
	}

	void destroy( GtkWidget *widget, gpointer   data )
	{
		gtk_main_quit ();
	}

	int main( int   argc, char *argv[] )
	{
		GtkWidget *filew;
    
		gtk_set_locale();
		gtk_init (&argc, &argv);
    
		//�����ļ�ѡ����
		filew = gtk_file_selection_new ("File selection");
		gtk_signal_connect (GTK_OBJECT (filew), "destroy",
			(GtkSignalFunc) destroy, &filew);
		//���ļ�ѡ�����е�"ȷ��"��ť���ûص�
		gtk_signal_connect (
			GTK_OBJECT(GTK_FILE_SELECTION (filew)->ok_button),
			"clicked", (GtkSignalFunc) file_ok_sel, filew );
    
		//���ļ�ѡ�����е�"ȡ��"��ť���ûص�
		gtk_signal_connect_object (
			GTK_OBJECT (GTK_FILE_SELECTION(filew)->cancel_button),
			"clicked", (GtkSignalFunc) gtk_widget_destroy,
			GTK_OBJECT (filew));
    
		//����ȱʡ���ļ���
		gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew), 
				     "/usr/X11R6/bin/xmag");
		gtk_widget_show(filew);
		gtk_main ();
		return 0;
	}
