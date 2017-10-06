	/* File progressbar.c */

	#include <gtk/gtk.h>

	typedef struct _ProgressData {
		GtkWidget *window;
		GtkWidget *pbar;
		int timer;
	} ProgressData;

	//��ʱ����
	gint progress_timeout( gpointer data )
	{
		gfloat new_val;
		GtkAdjustment *adj;

		//ȡ�ý�������ֵ
		new_val = gtk_progress_get_value( GTK_PROGRESS(data) ) + 1;

		//����ﵽ���ֵ, �ٴ�ͷ��ʼ
		adj = GTK_PROGRESS (data)->adjustment;
		if (new_val > adj->upper) new_val = adj->lower;

		//���ý���ֵ
		gtk_progress_set_value (GTK_PROGRESS (data), new_val);

		//����TRUE, ���Լ������øú���
		return(TRUE);
	} 

	//�л��ı���ʾ�ĺ���
	void toggle_show_text( GtkWidget *widget, ProgressData *pdata )
	{
		gtk_progress_set_show_text (GTK_PROGRESS (pdata->pbar),
			GTK_TOGGLE_BUTTON (widget)->active);
	}

	//���ü���ģʽ�ĺ���
	void toggle_activity_mode( GtkWidget *widget, ProgressData *pdata )
	{
		gtk_progress_set_activity_mode (GTK_PROGRESS (pdata->pbar),
			GTK_TOGGLE_BUTTON (widget)->active);
	}

	//��������ģʽ�ĺ���
	void set_continuous_mode( GtkWidget *widget,ProgressData *pdata )
	{
		gtk_progress_bar_set_bar_style (GTK_PROGRESS_BAR (pdata->pbar),
			GTK_PROGRESS_CONTINUOUS);
	}

	//���ò�����ģʽ�ĺ���
	void set_discrete_mode( GtkWidget *widget, ProgressData *pdata )
	{
		gtk_progress_bar_set_bar_style (GTK_PROGRESS_BAR (pdata->pbar),
			GTK_PROGRESS_DISCRETE);
	}
 
	//�˳�ʱ��Ҫ����ڴ�Ͷ�ʱ��
	void destroy_progress( GtkWidget *widget, ProgressData *pdata)
	{
		gtk_timeout_remove (pdata->timer);
		pdata->timer = 0;
		pdata->window = NULL;
		g_free(pdata);
		gtk_main_quit();
	}

	int main(int  argc, char *argv[])
	{
		ProgressData *pdata;
		GtkWidget *align;
		GtkWidget *separator;
		GtkWidget *table;
		GtkAdjustment *adj;
		GtkWidget *button;
		GtkWidget *check;
		GtkWidget *vbox;

		//��ʼ��
		gtk_set_locale();
		gtk_init (&argc, &argv);
		pdata = g_malloc( sizeof(ProgressData) );
  
		//����������
		pdata->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		//���ô�������
		gtk_window_set_policy (GTK_WINDOW (pdata->window), 
			FALSE, FALSE, TRUE);
		gtk_signal_connect (GTK_OBJECT (pdata->window), "destroy",
			GTK_SIGNAL_FUNC (destroy_progress), pdata);
		gtk_window_set_title(GTK_WINDOW(pdata->window),"ProgressBar");
		gtk_container_set_border_width(GTK_CONTAINER(pdata->window),0);

		//��ֱ���������
		vbox = gtk_vbox_new (FALSE, 5);
		gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
		gtk_container_add (GTK_CONTAINER (pdata->window), vbox);
		gtk_widget_show(vbox);
  
		//�м����
		align = gtk_alignment_new (0.5, 0.5, 0, 0);
		gtk_box_pack_start (GTK_BOX (vbox), align, FALSE, FALSE, 5);
		gtk_widget_show(align);

		//����������
		adj = (GtkAdjustment *)gtk_adjustment_new (0, 1, 150, 0, 0, 0);
		//����ʹ�øõ������Ľ�����
		pdata->pbar = gtk_progress_bar_new_with_adjustment (adj);
		//���ý���������ʾ�ı���ʽ
		gtk_progress_set_format_string (GTK_PROGRESS (pdata->pbar),
			"%v from [%l-%u] (=%p%%)");
		gtk_container_add (GTK_CONTAINER (align), pdata->pbar);
		gtk_widget_show(pdata->pbar);

		//������ʱ��, �����½�����
		pdata->timer = gtk_timeout_add (100, 
			progress_timeout, pdata->pbar);


		separator = gtk_hseparator_new ();
		gtk_box_pack_start (GTK_BOX (vbox), separator, FALSE, FALSE, 0);
		gtk_widget_show(separator);

		//�������еı������
		table = gtk_table_new (2, 3, FALSE);
		gtk_box_pack_start (GTK_BOX (vbox), table, FALSE, TRUE, 0);
		gtk_widget_show(table);

		//��ʾ�ı���check button
		check = gtk_check_button_new_with_label ("��ʾ�ı�");
		gtk_table_attach (GTK_TABLE (table), check, 0, 1, 0, 1,
			GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
		gtk_signal_connect (GTK_OBJECT (check), "clicked",
			GTK_SIGNAL_FUNC (toggle_show_text), pdata);
		gtk_widget_show(check);

		//��ʾ����״̬check button
		check = gtk_check_button_new_with_label ("����״̬");
		gtk_table_attach (GTK_TABLE (table), check, 0, 1, 1, 2,
			GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
		gtk_signal_connect (GTK_OBJECT (check), "clicked",
			GTK_SIGNAL_FUNC (toggle_activity_mode), pdata);
		gtk_widget_show(check);

		separator = gtk_vseparator_new ();
		gtk_table_attach (GTK_TABLE (table), separator, 1, 2, 0, 2,
			GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
		gtk_widget_show(separator);

		//��������ģʽ�� radio button
		button = gtk_radio_button_new_with_label (NULL, "����ģʽ");
		gtk_table_attach (GTK_TABLE (table), button, 2, 3, 0, 1,
			GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
		gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (set_continuous_mode), pdata);
		gtk_widget_show (button);

		//���ò�����ģʽ�� radio button
		button = gtk_radio_button_new_with_label(
			gtk_radio_button_group (GTK_RADIO_BUTTON (button)),
			"������ģʽ");
		gtk_table_attach (GTK_TABLE (table), button, 2, 3, 1, 2,
			GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
		gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (set_discrete_mode), pdata);
		gtk_widget_show (button);

		separator = gtk_hseparator_new ();
		gtk_box_pack_start (GTK_BOX (vbox), separator, FALSE, FALSE, 0);
		gtk_widget_show(separator);

		//�˳���ť
		button = gtk_button_new_with_label ("close");
		gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			(GtkSignalFunc) gtk_widget_destroy,
			GTK_OBJECT (pdata->window));
		gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

		//����Ϊ����ȱʡ�۽�
		GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);

		gtk_widget_grab_default (button);
		gtk_widget_show(button);

		gtk_widget_show (pdata->window);

		gtk_main ();
    
		return(0);
	}
