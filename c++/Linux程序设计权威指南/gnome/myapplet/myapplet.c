
	/* File: applet.c */

	#include <applet-widget.h>

	#define PACKAGE "myapplet"
	#define VERSION "1.0"

        static void cb_about (GtkWidget *widget, gpointer data)
        {
                GtkWidget *about;
                gchar *authors[] = {
                        "������",
                        NULL
                }; 
                about = gnome_about_new("Applet ��ʾ", 
                        VERSION,
                        "(C) 2000 the OpenCJK Organization",
                        (const char **)authors,
                        "Applet �����ʾ",
                        NULL);
                gtk_widget_show (about);
        }


	void cb_entry(GtkWidget *w, gpointer data)
	{
		char *str;
		str = gtk_entry_get_text(GTK_ENTRY(w));
		printf("Lookup %s\n", str);
	}

	int main(int argc, char **argv)
	{
		GtkWidget *applet;
		GtkWidget *entry;

		//��ʼ��
		applet_widget_init(PACKAGE, VERSION, argc, argv,
			NULL, 0, NULL);

		//����Applet
		applet = applet_widget_new(PACKAGE);

		//-------------��Ҫ������----------------------
		entry = gtk_entry_new();
		gtk_widget_set_usize(entry, 40, 20);
		gtk_signal_connect (GTK_OBJECT (entry), "activate",
			GTK_SIGNAL_FUNC(cb_entry), NULL);
		gtk_widget_show(entry);
		//---------------------------------------------

		//ע��˵���
		applet_widget_register_stock_callback (APPLET_WIDGET(applet),
			"about", GNOME_STOCK_MENU_ABOUT, "����...",
			cb_about, NULL);

		//��ӹ�������Applet
		applet_widget_add(APPLET_WIDGET(applet), entry);

		//��ʾApplet
		gtk_widget_show(applet);

		//Applet ѭ��
		applet_widget_gtk_main();
		return 0;
	}

