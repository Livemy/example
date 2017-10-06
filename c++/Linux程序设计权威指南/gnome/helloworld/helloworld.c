
	/* File: helloworld.c */

	//#include <gnome-config.h>
	#include <gnome.h>

	void hello_cb (GtkWidget *widget, void *data)
	{
		g_print ("Hello World\n");
		gtk_main_quit ();
		return;
	}
	void quit_cb (GtkWidget *widget, void *data)
	{
		gtk_main_quit ();
		return;
	}

           
	int main(int argc, char *argv[])
	{ 
		GtkWidget *button;
		GtkWidget *app;

		//��ʼ��
		gnome_init("Helloworld", "1.0", argc, argv);

		//����������
		app = gnome_app_new ("hello", "Hello World Gnomified");
		//gtk_widget_realize (app);
		gtk_signal_connect (GTK_OBJECT (app), "delete_event",
			GTK_SIGNAL_FUNC (quit_cb), NULL);

		//����GTK��ť���
		button = gtk_button_new_with_label ("Hello World!");
		gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (hello_cb), NULL);
		gtk_container_border_width (GTK_CONTAINER (button), 60);

		//�������
		gnome_app_set_contents ( GNOME_APP (app), button);

		//��ʾ���
		gtk_widget_show (button);
		gtk_widget_show (app);

		gtk_main ();
		return 0;
	}
