	/* File: ctree.c */

	#include <gtk/gtk.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include "xpm.h"

	gboolean drag_compare (GtkCTree     *ctree,
		GtkCTreeNode *src_node,
		GtkCTreeNode *dest_parent,
		GtkCTreeNode *dest_node)
	{
		GtkCTreeNode *user_box_parent;

		//ֻ��������к����Ŀ�Ϸ�
		user_box_parent = gtk_ctree_node_nth (ctree, 4);
		if (user_box_parent != GTK_CTREE_ROW (src_node)->parent)
			return FALSE;
		if (user_box_parent != dest_parent)return FALSE;
		return TRUE;
	}



	void cb_selected (GtkCTree       *ctree,
			 gint            row,
			 gint            column,
			 GdkEventButton *event,
			 gpointer        data)
	{
		g_print ("signal: %s\n", (gchar *)data);
		if (column > 0){
			gchar *text;
			if (gtk_clist_get_text (GTK_CLIST (ctree), 
				row, column, &text))
				g_print ("(%d, %d): %s\n", row, column, text);
			else
				g_print ("(%d, %d) : Sorry!\n", row, column);
		} else {
			gchar     *text;
			guint8     spacing;
			GdkPixmap *pixmap;
			GdkBitmap *mask;

			if (gtk_clist_get_pixtext (GTK_CLIST (ctree), 
				row, column, &text, &spacing, &pixmap, &mask))
				g_print ("(%d, %d): %s\n", row, column, text);
			else
				g_print ("(%d, %d) : Sorry!\n", row, column);
		}
		g_print ("data: (%s)\n", (gchar *)gtk_ctree_node_get_row_data
			(ctree, gtk_ctree_node_nth (ctree, row)));

	}

	void rebuild_tree (GtkWidget *window, GtkCTree  *ctree)
	{
		gchar *text[3];
		GtkCTreeNode *parent;
		GtkCTreeNode *sibling;
		GdkPixmap *pixmap1;
		GdkPixmap *pixmap2;
		GdkPixmap *pixmap3;
		GdkBitmap *mask1;
		GdkBitmap *mask2;
		GdkBitmap *mask3;

		GdkColor transparent;
		gchar buf1[60];
		gchar buf2[60];
		GtkCTreeNode *p;

		//����ͼ��
		if (!GTK_WIDGET_REALIZED (window))
			gtk_widget_realize (window);
		pixmap1 = gdk_pixmap_create_from_xpm_d (window->window, 
			&mask1, &transparent, book_closed_xpm);
		pixmap2 = gdk_pixmap_create_from_xpm_d (window->window, 
			&mask2, &transparent, book_open_xpm);
		pixmap3 = gdk_pixmap_create_from_xpm_d (window->window, 
			&mask3, &transparent, mini_page_xpm);

		//�����б�
		gtk_clist_freeze (GTK_CLIST (ctree));
		gtk_clist_clear (GTK_CLIST (ctree));

		//��������Ŀ
		text[0] = "����";
		text[1] = "";
		parent = gtk_ctree_insert_node (ctree, NULL, NULL, text, 5,
			pixmap1, mask1, pixmap2, mask2, FALSE, TRUE);

		text[0] = buf1;
		text[1] = buf2;

		sibling = NULL;
		sprintf (buf1, "���");
		sprintf (buf2, "");
		sibling = gtk_ctree_insert_node (ctree, parent, sibling, 
			text, 5, pixmap1, mask1, pixmap2, mask2, FALSE, FALSE);
		gtk_ctree_node_set_row_data (ctree, sibling, "Software");
		sprintf (buf1, "VCD������");
		sprintf (buf2, "MTV");
		p = gtk_ctree_insert_node (ctree, sibling, NULL, text, 5,
			pixmap3, mask3, NULL, NULL, TRUE, FALSE);
		gtk_ctree_node_set_row_data (ctree, p, "mtv player");

		sprintf (buf1, "CD������");
		sprintf (buf2, "xmms");
		p = gtk_ctree_insert_node (ctree, sibling, NULL, text, 5,
			pixmap3, mask3, NULL, NULL, TRUE, FALSE);
		gtk_ctree_node_set_row_data (ctree, p, "XMMS freeware");
	
		sprintf (buf1, "MIDI������");
		sprintf (buf2, "kmidi");
		p = gtk_ctree_insert_node (ctree, sibling, NULL, text, 5,
			pixmap3, mask3, NULL, NULL, TRUE, FALSE);
		gtk_ctree_node_set_row_data (ctree, p, "Kde �µĲ�����");

		sprintf (buf1, "���");
		sprintf (buf2, "PS/2");
		sibling = gtk_ctree_insert_node (ctree, parent, sibling, 
			text, 5, pixmap3, mask3, NULL, NULL, TRUE, FALSE);
		gtk_ctree_node_set_row_data (ctree, sibling, "mouse");

		sprintf (buf1, "��Ƶ");
		sprintf (buf2, "650");
		sibling = gtk_ctree_insert_node (ctree, parent, sibling, 
			text, 5, pixmap3, mask3, NULL, NULL, TRUE, FALSE);
		gtk_ctree_node_set_row_data (ctree, sibling,  "CPU Info");

		sprintf (buf1, "Ӳ��");
		sprintf (buf2, "18G");
		sibling = gtk_ctree_insert_node (ctree, parent, sibling, 
			text, 5, pixmap3, mask3, NULL, NULL, TRUE, FALSE);
		gtk_ctree_node_set_row_data (ctree, sibling, "disk");
		gtk_ctree_set_drag_compare_func (ctree, 
			(GtkCTreeCompareDragFunc) drag_compare);
		gtk_clist_thaw (GTK_CLIST (ctree));
	}

	gint main (gint   argc, gchar *argv[])
	{
		GtkWidget *window;
		GtkWidget *scrolled_win;
		GtkWidget *vbox;
		char *title[] =  {"��Ŀ", "��Ϣ"};
		GtkCTree *ctree;
		GtkWidget *button;
  
		//��ʼ��
		gtk_set_locale();
		gtk_init(&argc, &argv);

		//����������
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_signal_connect (GTK_OBJECT (window), "destroy",
			GTK_SIGNAL_FUNC (gtk_main_quit), NULL);
		gtk_window_set_title (GTK_WINDOW (window), "CTree");
		gtk_container_set_border_width (GTK_CONTAINER (window), 0);

		//��ֱ�������������������ںͰ�ť
		vbox = gtk_vbox_new (FALSE, 0);
		gtk_container_add (GTK_CONTAINER (window), vbox);
		scrolled_win = gtk_scrolled_window_new (NULL, NULL);
		gtk_container_set_border_width (GTK_CONTAINER(scrolled_win), 5);
		gtk_scrolled_window_set_policy (
			GTK_SCROLLED_WINDOW (scrolled_win),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS); 
		gtk_box_pack_start (GTK_BOX (vbox),scrolled_win, TRUE, TRUE, 0);

		//����������
		ctree = GTK_CTREE (gtk_ctree_new_with_titles (2, 0, title));
		//�������ĳߴ�
		gtk_widget_set_usize (GTK_WIDGET (ctree), 300, 300);
		gtk_container_add (GTK_CONTAINER (scrolled_win), 
			GTK_WIDGET (ctree));
 
		//������������
		gtk_clist_set_column_auto_resize (GTK_CLIST (ctree), 0, TRUE);
		gtk_clist_set_column_width (GTK_CLIST (ctree), 1, 100);
		gtk_clist_set_column_width (GTK_CLIST (ctree), 2, 100);
		gtk_clist_set_selection_mode (GTK_CLIST (ctree),
			GTK_SELECTION_EXTENDED);

		//�����ߵ���״
		gtk_ctree_set_line_style (ctree, GTK_CTREE_LINES_DOTTED);
		gtk_clist_set_reorderable (GTK_CLIST(ctree), TRUE);
		//ѡ��������Ļص�, ˫������
		gtk_signal_connect (GTK_OBJECT(ctree), "select_row",
			GTK_SIGNAL_FUNC(cb_selected), "tree-select-row");
		//������
		rebuild_tree (window, ctree);
    
		//�˳���ť
		button = gtk_button_new_with_label ("�˳�");
		gtk_box_pack_end (GTK_BOX (vbox), button, TRUE, TRUE, 0);
		gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (gtk_main_quit), NULL);

		gtk_widget_show_all (window);
		gtk_main ();
  
		return 0;
	}

