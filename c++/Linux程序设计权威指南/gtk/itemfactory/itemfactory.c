
	/* File: itemfactory.c */

	#include <gtk/gtk.h>
	#include <strings.h>

	static void print_hello( GtkWidget *w, gpointer   data )
	{
		g_message ("Hello, World!\n");
	}

	static GtkItemFactoryEntry menu_items[] = {
		{ "/�ļ�(_F)",         NULL,         NULL, 0, "<Branch>" },
		{ "/�ļ�(_F)/�µ�(_N)","<control>N", print_hello, 0, NULL },
		{ "/�ļ�(_F)/��(_O)","<control>O", print_hello, 0, NULL },
		{ "/�ļ�(_F)/����(_S)","<control>S", print_hello, 0, NULL },
		{ "/�ļ�(_F)/����Ϊ(_A)", NULL,      NULL, 0, NULL },
		{ "/�ļ�(_F)/sep1",    NULL,         NULL, 0, "<Separator>" },
		{ "/�ļ�(_F)/�˳�",    "<control>Q", gtk_main_quit, 0, NULL },
		{ "/ѡ��(_O)",         NULL,         NULL, 0, "<Branch>" },
		{ "/ѡ��(_O)/����1",    NULL,        NULL, 0, "<Branch>" },
		{ "/ѡ��(_O)/����1/Item 1-1",        NULL, NULL, 0, NULL },
		{ "/ѡ��(_O)/����1/Item 1-2",        NULL, NULL, 0, NULL },
		{ "/ѡ��(_O)/����2",    NULL,        NULL, 0, "<Branch>" },
		{ "/ѡ��(_O)/����2/Item 2-1",        NULL, NULL, 0, NULL },
		{ "/ѡ��(_O)/����2/Item 2-2",        NULL, NULL, 0, NULL },
		{ "/ѡ��(_O)/����2/Item 2-3",        NULL, NULL, 0, NULL },
		{ "/����(_H)",         NULL,         NULL, 0, "<LastBranch>" },
		{ "/����(_H)/����...", NULL,         NULL, 0, NULL },
	};

	GtkWidget *get_main_menu( GtkWidget  *window)
	{
		GtkItemFactory *item_factory;
		GtkAccelGroup *accel_group;
		gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);

		//������
		accel_group = gtk_accel_group_new ();

		//��ʼ�� item_factory
		item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, 
			"<main>", accel_group);

		//�����˵�
		gtk_item_factory_create_items (item_factory, 
			nmenu_items, menu_items, NULL);

		//�Ѽ�����ŵ�������
		gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);

		//���ز˵���
		return gtk_item_factory_get_widget (item_factory, "<main>");
	}

	int main( int argc, char *argv[] )
	{
		GtkWidget *window;
		GtkWidget *main_vbox;
		GtkWidget *menubar;
   
		//��ʼ��
		gtk_set_locale();
		gtk_init (&argc, &argv);
   
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_signal_connect (GTK_OBJECT (window), "destroy", 
			GTK_SIGNAL_FUNC (gtk_main_quit), "WM destroy");
		gtk_window_set_title (GTK_WINDOW(window), "Item Factory");
		gtk_widget_set_usize (GTK_WIDGET(window), 300, 200);
   
		//��ֱ����
		main_vbox = gtk_vbox_new (FALSE, 1);
		gtk_container_border_width (GTK_CONTAINER (main_vbox), 1);
		gtk_container_add (GTK_CONTAINER (window), main_vbox);
		gtk_widget_show (main_vbox);

		//�����˵�
		menubar = get_main_menu (window);
		gtk_box_pack_start(GTK_BOX(main_vbox), menubar, FALSE, TRUE, 0);
		gtk_widget_show(menubar);
   
		gtk_widget_show (window);
		gtk_main ();
   
		return(0);
	}
