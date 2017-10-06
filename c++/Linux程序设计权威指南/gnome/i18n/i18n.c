
	/* File: i18n.c */

	#define  ENABLE_NLS

	#include <gnome.h>

	#define PACKAGE "i18ntest"
	#define VERSION "1.0"


	static void about_cb (GtkWidget *widget, gpointer data)
	{
		GtkWidget *about;
		gchar *authors[] = {
			N_("Yu Mingjian"),
			NULL
		}; 
		about = gnome_about_new("Gnome ��̷��", 
			VERSION,
			N_("(C) 2000 the OpenCJK Organization"),
			(const char **)authors,
			N_("Simple demonstration for Gnome programming"),
			NULL);
		gtk_widget_show (about);
	}


	static void item_activated (GtkWidget *widget, gpointer data)
	{
		printf ("%s activated\n", (char *) data);
	}


	static GnomeUIInfo helper_file_menu[] = {
		{ GNOME_APP_UI_ITEM, N_("_New"), N_("Create a new file"), 
			item_activated, "file/new", NULL, 
			GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_NEW, 
			'n', GDK_CONTROL_MASK, NULL },
		{ GNOME_APP_UI_ITEM,N_("_Open..."),N_("Open an existing file"), 
			item_activated, "file/open", NULL,
			GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_OPEN, 
			'o', GDK_CONTROL_MASK, NULL },
		GNOMEUIINFO_SEPARATOR, 
		{ GNOME_APP_UI_ITEM, N_("_Close"),N_("Close the current file"), 
			item_activated, "file/close", NULL,
			GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_CLOSE, 
			0, 0, NULL },
		GNOMEUIINFO_END
	};

	static GnomeUIInfo helper_edit_menu[] = {
		{ GNOME_APP_UI_ITEM, N_("_Undo"),N_("Undo the last operation"), 
			item_activated, "edit/undo", NULL,
			GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_UNDO, 
			'z', GDK_CONTROL_MASK, NULL }, 
		{ GNOME_APP_UI_ITEM, N_("Cu_t"), N_("Cut the selection"), 
			item_activated, "edit/cut", NULL,
			GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_CUT, 
			'x', GDK_CONTROL_MASK, NULL },
		{ GNOME_APP_UI_ITEM, N_("_Copy"), N_("Copy the selection"),
			item_activated, "edit/copy", NULL,
			GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_COPY, 
			'c', GDK_CONTROL_MASK, NULL },
		{ GNOME_APP_UI_ITEM, N_("_Paste"), N_("Paste the contents"), 
			item_activated, "edit/paste", NULL,
			GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_PASTE, 
			'v', GDK_CONTROL_MASK, NULL },
		GNOMEUIINFO_END
	};

	static GnomeUIInfo helper_help_menu[] = {
		{ GNOME_APP_UI_ITEM, N_("_About..."), 
			N_("Displays information about the program"), about_cb, 
			"help/about", NULL,
			GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_MENU_ABOUT, 
			0, 0, NULL },
		GNOMEUIINFO_END
	};



	static GnomeUIInfo helper_main_menu[] = {
		{ GNOME_APP_UI_SUBTREE, N_("_File"), N_("File operations"), 
			helper_file_menu, NULL, NULL,
			GNOME_APP_PIXMAP_NONE, NULL, 0, 0, NULL },
		{ GNOME_APP_UI_SUBTREE, N_("_Edit"), N_("Editing commands"), 
			helper_edit_menu, NULL, NULL,
			GNOME_APP_PIXMAP_NONE, NULL, 0, 0, NULL },
		{ GNOME_APP_UI_SUBTREE, N_("_Help"), N_("Help on the program"), 
			helper_help_menu, NULL, NULL,
			GNOME_APP_PIXMAP_NONE, NULL, 0, 0, NULL },
		GNOMEUIINFO_END
	};




	static GnomeUIInfo helper_toolbar[] = {
		{ GNOME_APP_UI_ITEM, N_("New"), N_("Create a new file"), 
			item_activated, "toolbar/new", NULL,
			GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_PIXMAP_NEW, 
			0, 0, NULL },
		{ GNOME_APP_UI_ITEM, N_("Open"), N_("Open an existing file"), 
			item_activated, "toolbar/open", NULL,
			GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_PIXMAP_OPEN, 
			0, 0, NULL },
		{ GNOME_APP_UI_ITEM, N_("Save"), N_("Save the current file"), 
			item_activated, "toolbar/save", NULL,
			GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_PIXMAP_SAVE, 
			0, 0, NULL },
		{ GNOME_APP_UI_ITEM, N_("Print"), N_("Print the current file"), 
			item_activated, "toolbar/print", NULL,
			GNOME_APP_PIXMAP_STOCK, GNOME_STOCK_PIXMAP_PRINT, 
			0, 0, NULL },
		GNOMEUIINFO_END
	};

	
	void quit_cb (GtkWidget *widget, void *data)
	{
		gtk_main_quit ();
		return;
	}


	int main(int argc, char *argv[])
	{ 
		GtkWidget *app;
		GnomeAppBar *bar;
		GtkWidget *frame;

		//��ʼ��
		//setlocale(LC_ALL, "");
		gnome_init(PACKAGE, "1.0", argc, argv);
		bindtextdomain( PACKAGE, "/usr/share/locale");
		textdomain( PACKAGE );

		//����������
		app = gnome_app_new (PACKAGE, "GNOME Style Programming");
		gtk_signal_connect (GTK_OBJECT (app), "delete_event",
			GTK_SIGNAL_FUNC (quit_cb), NULL);

		//�����˵�
		gnome_app_create_menus (GNOME_APP (app), helper_main_menu);
		//������ť
		gnome_app_create_toolbar (GNOME_APP (app), helper_toolbar);
		//����״̬��
		bar = GNOME_APPBAR(
			gnome_appbar_new(FALSE, TRUE, GNOME_PREFERENCES_USER));
		gnome_app_set_statusbar(GNOME_APP(app), GTK_WIDGET(bar));

		//��״̬������ʾ�˵���ʾ 
		gnome_app_install_appbar_menu_hints(GNOME_APPBAR(bar), 
			helper_main_menu);


		//---- ��Ҫ�������� ---------------------------

		frame = gtk_frame_new (_("Main Work Area"));
		gtk_widget_set_usize(frame, 640, 480);
		gtk_widget_show (frame);


		//-------------------------------

		//�������
		gnome_app_set_contents ( GNOME_APP (app), frame);

		//��ʾ���
		gtk_widget_show (app);

		gtk_main ();
		return 0;
	}
