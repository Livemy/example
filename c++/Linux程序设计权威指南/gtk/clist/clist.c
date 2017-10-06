	/* File: clist.c */

	#include <gtk/gtk.h>
	#include "gtk.xpm"

	int selected_row = 0;

	//�����б�
	void button_add_clicked( gpointer data )
	{
		int indx;
		int row;
		GtkCList *clist = GTK_CLIST (data);

		//ͼ��
		GdkBitmap *mask;
		GdkPixmap *pixmap;

		//�����������е��б�
		gchar *card[4][3] = { 
			{ "�Կ�",    "68001234",	"����" },
			{ "��С��",  "022-6234567",	"ɽ��" },
			{ "������",  "13601111111",	"����" },
			{ "����",    "66054321",	"���" } };

		//����ͼ��
		pixmap = gdk_pixmap_create_from_xpm_d(clist->clist_window,
				&mask, &GTK_WIDGET (data)->style->white,
				gtk_mini_xpm);


		//�����б�
		gtk_clist_freeze(clist);

		//������
		for ( indx=0 ; indx < 4 ; indx++ ){
			row = gtk_clist_append(clist, card[indx]); 
			gtk_clist_set_pixtext (clist, row, 2, 
				card[indx][2], 5, pixmap, mask);
		}

		//ѡ��(0,0)��Ԫ
		gtk_clist_select_row(clist, 0, 0);
		selected_row = 0;

		//�ⶳ
		gtk_clist_thaw(clist);
		return;
	}

	//����б�
	void button_clear_clicked( gpointer data )
	{
		gtk_clist_clear( (GtkCList *) data);
		return;
	}

	//ɾ����
	void button_del_clicked( gpointer data )
	{
		gtk_clist_remove((GtkCList *) data, selected_row);
		if(selected_row > 0) selected_row --;
		gtk_clist_select_row((GtkCList *)data, selected_row, 0);
	}

	//��ʾ/���ر���
	void button_hide_show_clicked( gpointer data )
	{
		static short int flag = 0;
		if (flag == 0){
			gtk_clist_column_titles_hide((GtkCList *) data);
         		flag++;
		} else {
			gtk_clist_column_titles_show((GtkCList *) data);
			flag--;
		} 
		return;
	}

	//ѡ��ĳ��
	void selection_made( GtkWidget      *clist,
                      gint            row,
                      gint            column,
                      GdkEventButton *event,
                      gpointer        data )
	{
		gchar *text;
		guint8 spacing;
                GdkBitmap *mask;
                GdkPixmap *pixmap;

		//ȡ���ַ���
		if(column == 2){
			//�ڶ��к���ͼ����ַ�
			gtk_clist_get_pixtext(GTK_CLIST(clist), row, column,
				&text, &spacing, &pixmap, &mask);
		} else {	
			gtk_clist_get_text(GTK_CLIST(clist), row, column,&text);
		}
		selected_row = row;

		g_print("(%d,%d):%s\n", row, column, text);
		return;
	}

	int main( int argc, gchar *argv[] )
	{
		GtkWidget *window;
		GtkWidget *vbox, *hbox;
		GtkWidget *clist;
		GtkWidget *scrolled_window;	//clist�Ĺ�������
		GtkWidget *button_add, *button_clear,
			  *button_del, *button_hide_show;    
		//����
		gchar *titles[3] = { "����", "�绰����", "סַ" };

		//��ʼ��
		gtk_set_locale();
		gtk_init(&argc, &argv);
     
		//��������
		window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
		//���ô��ڵĳߴ�
		gtk_widget_set_usize(GTK_WIDGET(window), 400, 250);
		//���ڱ���
		gtk_window_set_title(GTK_WINDOW(window), "CList��ʾ");
		gtk_signal_connect(GTK_OBJECT(window), "destroy",
                        GTK_SIGNAL_FUNC(gtk_main_quit), NULL);

		//�������ɹ������ںͰ�ť
		vbox=gtk_vbox_new(FALSE, 5);
		gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
		gtk_container_add(GTK_CONTAINER(window), vbox);
		gtk_widget_show(vbox); 

		//��������
		scrolled_window = gtk_scrolled_window_new (NULL, NULL);
		//�������ڵĹ�������, ������ˮƽ������Զ��������,
		//��ֱ������Զ������Զ���
		gtk_scrolled_window_set_policy(
			GTK_SCROLLED_WINDOW (scrolled_window),
			GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
		//�ѹ������ڷŵ�������
		gtk_box_pack_start(GTK_BOX(vbox), scrolled_window,TRUE,TRUE,0);
		gtk_widget_show (scrolled_window);

		//�������еĴ������CList
		clist = gtk_clist_new_with_titles( 3, titles);
		//ѡ��ĳ��ʱ�Ļص�����
		gtk_signal_connect(GTK_OBJECT(clist), "select_row",
                        GTK_SIGNAL_FUNC(selection_made),
                        NULL);
		//������Ӱ����
		gtk_clist_set_shadow_type (GTK_CLIST(clist), GTK_SHADOW_OUT);
		//�����еĿ��(�����Ǵ�0��ʼ��)
		gtk_clist_set_column_width (GTK_CLIST(clist), 0, 150);
		gtk_clist_set_column_width (GTK_CLIST(clist), 1, 100);

		//���õ�һ�е���С�������
		gtk_clist_set_column_max_width (GTK_CLIST (clist), 0, 200);
		gtk_clist_set_column_min_width (GTK_CLIST (clist), 0, 50);

		//����ѡ���ģʽ
		//gtk_clist_set_selection_mode (GTK_CLIST (clist), GTK_SELECTION_EXTENDED);
		//���õ�0�ж��뷽ʽ
		gtk_clist_set_column_justification (GTK_CLIST (clist), 0,
			GTK_JUSTIFY_CENTER);

		//�����еĸ߶�
		gtk_clist_set_row_height (GTK_CLIST (clist), 24);

		//��CList�ӵ�����������
		gtk_container_add(GTK_CONTAINER(scrolled_window), clist);
		gtk_widget_show(clist);

		//ˮƽ�������ɰ�ť
		hbox = gtk_hbox_new(FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 0);
		gtk_widget_show(hbox);

		//������ť
		button_add = gtk_button_new_with_label("�����б�");
		button_clear = gtk_button_new_with_label("����б�");
		button_del = gtk_button_new_with_label("ɾ��ѡ����");
		button_hide_show = gtk_button_new_with_label("��ʾ/���ر���");
		gtk_box_pack_start(GTK_BOX(hbox), button_add, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(hbox), button_clear, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(hbox), button_del, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(hbox), button_hide_show,TRUE,TRUE,0);

		//���ûص�����
		gtk_signal_connect_object(GTK_OBJECT(button_add), "clicked",
			GTK_SIGNAL_FUNC(button_add_clicked), (gpointer) clist);
		gtk_signal_connect_object(GTK_OBJECT(button_clear), "clicked",
			GTK_SIGNAL_FUNC(button_clear_clicked), (gpointer)clist);
		gtk_signal_connect_object(GTK_OBJECT(button_del), "clicked",
			GTK_SIGNAL_FUNC(button_del_clicked), (gpointer)clist);
		gtk_signal_connect_object(GTK_OBJECT(button_hide_show),"clicked",
			GTK_SIGNAL_FUNC(button_hide_show_clicked), 
			(gpointer) clist);
		gtk_widget_show(button_add);
		gtk_widget_show(button_clear);
		gtk_widget_show(button_del);
		gtk_widget_show(button_hide_show);

		gtk_widget_show(window);
		gtk_main(); 
		return(0);
	}
