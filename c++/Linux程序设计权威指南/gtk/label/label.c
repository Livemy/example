
	/* File: label.c */

	#include <gtk/gtk.h>

	int main( int   argc, char *argv[] )
	{
		static GtkWidget *window = NULL;
		GtkWidget *vbox;
		GtkWidget *hbox;
		GtkWidget *frame;
		GtkWidget *label;

		//��ʼ��
		gtk_set_locale();
		gtk_init(&argc, &argv);

		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_signal_connect (GTK_OBJECT (window), "destroy",
                       GTK_SIGNAL_FUNC(gtk_main_quit), NULL);
		gtk_window_set_title (GTK_WINDOW (window), "Label");

		//������ֱ���������
		vbox = gtk_vbox_new (FALSE, 5);
		gtk_container_add (GTK_CONTAINER (window), vbox);
		//���������ı߽�ռ�
		gtk_container_set_border_width (GTK_CONTAINER (window), 5);
 
		//����һ�� Frame ����
		frame = gtk_frame_new("������ǩ");
		label = gtk_label_new ("����һ��������ǩ");
		//�������м����ǩ
		gtk_container_add (GTK_CONTAINER (frame), label);
		gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);
   
		//�������б�ǩ
		frame = gtk_frame_new("���б�ǩ");
		label = gtk_label_new("����һ�����б�ǩ.\n�ڶ���\n" \
                          "������");
		gtk_container_add (GTK_CONTAINER (frame), label);
		gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);
   
		//������ǩ
		frame = gtk_frame_new ("������ǩ");
		label = gtk_label_new ("�˱�ǩ��������\n" \
                          "���б�ǩ.\n������");
		gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
		gtk_container_add (GTK_CONTAINER (frame), label);
		gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);
   
		//�Ҷ����ǩ
		frame = gtk_frame_new ("�Ҷ����ǩ");
		label = gtk_label_new ("�˱�ǩ���Ҷ����\n���б�ǩ.\n" \
                          "������");
		gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_RIGHT);
		gtk_container_add (GTK_CONTAINER (frame), label);
		gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

		//�����Զ����б�ǩ
		frame = gtk_frame_new ("�Զ����б�ǩ");
		label = gtk_label_new (
			"This is an example of a line-wrapped label.  It " \
                        "should not be taking up the entire             " /* big space to test spacing */\
                        "width allocated to it, but automatically " \
                        "wraps the words to fit.  " \
                        "The time has come, for all good men, to come to " \
                        "the aid of their party.  " \
                        "The sixth sheik's six sheep's sick.\n" \
                        "     It supports multiple paragraphs correctly, " \
                        "and  correctly   adds "\
                        "many          extra  spaces. ");
		//����Ϊ�Զ�����
		gtk_label_set_line_wrap (GTK_LABEL (label), TRUE);
		gtk_container_add (GTK_CONTAINER (frame), label);
		gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);
   
		//��ʾ���еĴ���
		gtk_widget_show_all (window);

		gtk_main ();
  
		return(0);
	}
