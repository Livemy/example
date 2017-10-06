	/* File: thread.c */

	#include <pthread.h>
	#include <gtk/gtk.h>

	GtkWidget *clist;
	//�����������е��б�
	gchar *card[4][3] = { 
		{ "�Կ�",    "68001234",	"" },
		{ "��С��",  "022-6234567",	"" },
		{ "������",  "13601111111",	"" },
		{ "����",    "66054321",	"" } };
	
	pthread_t thread1, thread2;
	pthread_mutex_t mutex;

	void thread_add_item(void *ptr)
	{
		int idx;
		while(1){
			idx = (int)random()%4;
			sleep((int)random()%2 + 2);
			pthread_mutex_lock(&mutex);
			card[idx][2] = (char *)ptr;
			gtk_clist_append(GTK_CLIST(clist), card[idx]); 
			pthread_mutex_unlock(&mutex);
		}
	}


	int main( int argc, gchar *argv[] )
	{
		int i, row;
		GtkWidget *window;
		GtkWidget *vbox;
		GtkWidget *scrolled_window;	//clist�Ĺ�������
		//����
		gchar *titles[3] = { "����", "�绰����", "סַ" };

		//��ʼ��
		gtk_set_locale();
		g_thread_init(NULL);
		gtk_init(&argc, &argv);
     
		//��������
		window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
		//���ô��ڵĳߴ�
		gtk_widget_set_usize(GTK_WIDGET(window), 400, 250);
		//���ڱ���
		gtk_window_set_title(GTK_WINDOW(window), "GtkCList��ʾ");
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
		//������Ӱ����
		gtk_clist_set_shadow_type (GTK_CLIST(clist), GTK_SHADOW_OUT);
		//�����еĿ��(�����Ǵ�0��ʼ��)
		gtk_clist_set_column_width (GTK_CLIST(clist), 0, 60);
		gtk_clist_set_column_width (GTK_CLIST(clist), 1, 100);

		//�����
		for (i=0 ; i < 4 ; i++ ){
			row = gtk_clist_append(GTK_CLIST(clist), card[i]); 
		}

		//��CList�ӵ�����������
		gtk_container_add(GTK_CONTAINER(scrolled_window), clist);
		gtk_widget_show(clist);
		gtk_widget_show(window);



		//�����߳�
		pthread_mutex_init(&mutex, NULL);
		pthread_create(&thread1, NULL, 
			(void *)thread_add_item, (void *)"�߳�1");
		pthread_create(&thread2, NULL, 
			(void *)thread_add_item, (void *)"�߳�2");

		gdk_threads_enter();
		gtk_main(); 
		gdk_threads_leave();

		pthread_mutex_destroy(&mutex);
		return(0);
	}
