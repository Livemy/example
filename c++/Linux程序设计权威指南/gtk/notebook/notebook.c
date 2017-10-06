
	/* File: notebook.c */
	#include <gtk/gtk.h>

	gint delete( GtkWidget *widget, GtkWidget *event, gpointer   data )
	{
		gtk_main_quit();
		return(FALSE);
	}

	int main( int argc, char *argv[] )
	{
		GtkWidget *window;
		GtkWidget *button;
		GtkWidget *table;
		GtkWidget *notebook;
		GtkWidget *frame;
		GtkWidget *label;
		GtkWidget *checkbutton;
		int i;
		static char *notelabel[] = { "��ʾ��", "���", "����"};
    
		//��ʼ��
		gtk_set_locale();
		gtk_init (&argc, &argv);
    
		//����������
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_signal_connect (GTK_OBJECT (window), "delete_event",
			GTK_SIGNAL_FUNC (delete), NULL); 
		gtk_container_set_border_width (GTK_CONTAINER (window), 10);

		//�����ʼǱ�
		notebook = gtk_notebook_new ();
		gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
		//gtk_widget_set_usize(notebook, 640, 480);
		gtk_container_add (GTK_CONTAINER (window), notebook);
		gtk_widget_show(notebook);
    
		//�������ҳ��
		for (i=0; i < 3; i++) {
			char buf[80];
			//����notebookҳ���еĿ������
			sprintf(buf, "��� - %s", notelabel[i]);
			frame = gtk_frame_new(buf);
			gtk_container_set_border_width(GTK_CONTAINER(frame),10);
			gtk_widget_set_usize (frame, 100, 75);
			gtk_widget_show (frame);

			//��������еı�ǩ
			sprintf(buf, "��ǩ - %s", notelabel[i]);
			label = gtk_label_new (buf);
			gtk_container_add (GTK_CONTAINER (frame), label);
			gtk_widget_show (label);
	
			//�����ʼǱ��ı�ǩ
			label = gtk_label_new (notelabel[i]);
			//�����ҳ
			gtk_notebook_append_page (GTK_NOTEBOOK (notebook), 
				frame, label);
		}
      
		gtk_notebook_set_page (GTK_NOTEBOOK(notebook), 2);

		gtk_widget_show(window);
    
		gtk_main ();
    
		return(0);
	}
