
	/* File: skins.c */

	/* ����ʹ���� SecurityFocus.com �� Pager ��ĳЩ����.
	*/

	#include <stdio.h>
	#include <string.h>
	#include <gtk/gtk.h>
	#include <gdk_imlib.h>
	#include <gdk/gdkx.h>

	//��Ƥ
	typedef struct _Skin {
		int x, y, w, h;
		char file[80];
		GdkImlibImage *im1, *im2;
	} Skin;

	typedef struct _Skinimage {
		Skin win;
		Skin main;
		Skin images[7];
	} Skinimage;

	char *sample_skins[] = {"focus", "future", "gamepad", "large", "max"};

	Skinimage skinimage;
	GtkWidget *pixmap;
	GdkPixmap *gdk_pixmap, *gdk_mask;
	//�����ƶ����ڵ�ȫ�ֱ���
	static GdkWindow *root_win = NULL;
	static GtkWidget *window, *fixed, *scrolled_window;
	typedef struct _position {gint x,y;} Position;
	Position root_pos, win_pos;


	int mystrncmp(char *s1, char *s2)
	{
		return strncmp(s1, s2, strlen(s2));
	}

	static void get_pair(Skinimage *skin, int idx, char *name, char *line)
	{
		char *p1, *p2;
		char fname[80];

		p1 = strchr(line, '=');
		bzero(skin->images[idx].file, 80); 
		strncpy(skin->images[idx].file, line, p1-line);
		p2 = strchr(p1, ',');
		skin->images[idx].y = atoi(p2+1);
		*p2 = 0;
		skin->images[idx].x = atoi(p1+1);


		sprintf(fname, "./%s/%s.jpg", name, skin->images[idx].file);
		skin->images[idx].im1 = gdk_imlib_load_image(fname);

		sprintf(fname,"./%s/%sclick.jpg", name, skin->images[idx].file);
		skin->images[idx].im2 = gdk_imlib_load_image(fname);

		if(skin->images[idx].im1){
			skin->images[idx].w = skin->images[idx].im1->rgb_width;
			skin->images[idx].h = skin->images[idx].im1->rgb_height;
			gdk_imlib_render(skin->images[idx].im1, 
				skin->images[idx].w, skin->images[idx].h);
			gdk_imlib_render(skin->images[idx].im2, 
				skin->images[idx].w, skin->images[idx].h);
		}

	}

	/* file skin.ini 
	[skin]
	name=gamepad
	main=113,26
	mainwidth=357
	mainheight=206
	banner=185,265
	help=34,73
	min=479,73
	exit=532,125
	search=0,107
	update=74,107
	config=34,145
	*/
	static void load_skin(Skinimage *skin, char *name)
	{
		FILE *fp;
		char fname[128];
		char line[2560];
		char *p1, *p2;
		int idx = 0;

		sprintf(fname, "./%s/skin.ini", name);
		fp = fopen(fname, "r");
		if(!fp) {
			printf("Skin %s not found!\n", name);
			exit(1);
		}

		while(fgets(line, 256, fp)){
			//trim
			line[strlen(line)-1] = 0;
			if(!mystrncmp(line, "[skin]")) continue;
			else if(!mystrncmp(line, "name=")) continue;
			else if(!mystrncmp(line, "main=")){
				//get (x, y)
				p1 = line + 5;
				p2 = strchr(p1, ',');
				skin->main.y = atoi(p2+1);
				*p2 = 0;
				skin->main.x = atoi(p1);
			} else if(!mystrncmp(line, "mainwidth=")){
				p1 = line + 10;
				skin->main.w = atoi(p1);
			} else if(!mystrncmp(line, "mainheight=")){
				p1 = line + 11;
				skin->main.h = atoi(p1);
			} else {
			//other images
				get_pair(skin, idx, name, line);
				idx ++;
			}
		}
		//������ͼ��
		sprintf(fname, "./%s/skin.xpm", name);
		skin->win.im1 = gdk_imlib_load_image(fname);

		sprintf(fname,"./%s/skin-mask.xpm", name);
		skin->win.im2 = gdk_imlib_load_image(fname);

		skin->win.w = skin->win.im1->rgb_width;
		skin->win.h = skin->win.im1->rgb_height;
		gdk_imlib_render(skin->win.im1, skin->win.w, skin->win.h);
		gdk_imlib_render(skin->win.im2, skin->win.w, skin->win.h);
	}

	void reload_skin(Skinimage *skin)
	{
		int i;

		//ȡ������ı�Ƥ
		int idx = (int)random() % 5;

		//�ͷ��ڴ�
		gdk_imlib_destroy_image(skin->win.im1);
		gdk_imlib_destroy_image(skin->win.im2);
		for(i=0; i<7; i++){
			if(skin->images[i].im1){
				gdk_imlib_destroy_image(skin->images[i].im1);
				gdk_imlib_destroy_image(skin->images[i].im2);
			}
		}

		//�����Ƥ
		load_skin(skin, sample_skins[idx]);

		//�ı������λ�úʹ�С
		gtk_widget_set_usize(window, skin->win.w, skin->win.h);
		gtk_widget_set_usize(fixed,  skin->win.w, skin->win.h);
		gtk_widget_set_usize(scrolled_window,  
			skin->main.w, skin->main.h);
		gtk_fixed_move(GTK_FIXED(fixed), scrolled_window,
			skin->main.x, skin->main.y);

		//��������ͼ��
                gdk_pixmap = gdk_imlib_move_image(skin->win.im1);
                gdk_mask = gdk_imlib_move_mask(skin->win.im2);
		gdk_imlib_paste_image(skin->win.im1, fixed->window, 0, 0,
			skin->win.w, skin->win.h);
		gtk_pixmap_set(GTK_PIXMAP(pixmap), gdk_pixmap, gdk_mask);

		//����������״
		gdk_window_shape_combine_mask(window->window, gdk_mask,0,0);

		gdk_flush();

	}


	GtkWidget *create_tree(GtkWidget *parent)
	{
		int i;
		GtkWidget *root_tree, *tree;
		GtkWidget *root_item;
		GtkWidget *subtree, *item, *subitem;

		static char *hardware[3] = {
			"����",
			"���",
			"Ӳ��"};

		static char *software[2] = {
			"GIMP",
			"MTV"};

		//��������
		root_tree = gtk_tree_new();
		//��Tree�ӵ�����������
		gtk_scrolled_window_add_with_viewport(
			GTK_SCROLLED_WINDOW(parent), root_tree);
		gtk_widget_show(root_tree);
		//����label
		root_item = gtk_tree_item_new_with_label("�����");
		gtk_tree_append(GTK_TREE(root_tree), root_item);
		gtk_widget_show(root_item);

		//����
		tree = gtk_tree_new();
		gtk_widget_show (tree);
		gtk_tree_item_set_subtree(GTK_TREE_ITEM(root_item), tree);

		//����������֦
		item = gtk_tree_item_new_with_label("Ӳ��");
		//���뵽parent��
		gtk_tree_append(GTK_TREE(tree), item);
		gtk_widget_show (item);
		//��֦
		subtree = gtk_tree_new();
		gtk_tree_set_view_mode (GTK_TREE(subtree), GTK_TREE_VIEW_ITEM);
		gtk_tree_item_set_subtree (GTK_TREE_ITEM(item), subtree);
		//��Ҷ
		for(i = 0; i < 3; i++){
			subitem = gtk_tree_item_new_with_label(hardware[i]);
			gtk_tree_append (GTK_TREE(subtree), subitem);
			gtk_widget_show (subitem);
		}

		//����һ����֦
		item = gtk_tree_item_new_with_label("���");
		gtk_tree_append(GTK_TREE(tree), item);
		gtk_widget_show (item);
		subtree = gtk_tree_new();
		gtk_tree_set_view_mode (GTK_TREE(subtree), GTK_TREE_VIEW_ITEM);
		gtk_tree_item_set_subtree (GTK_TREE_ITEM(item), subtree);
		//��Ҷ
		for(i = 0; i < 2; i++){
			subitem = gtk_tree_item_new_with_label(software[i]);
			gtk_tree_append (GTK_TREE(subtree), subitem);
			gtk_widget_show (subitem);
		}

		return root_tree;
	}


	//�˳�
	gint close_application( GtkWidget *widget, 
		GdkEvent  *event, gpointer   data )
	{
		gtk_main_quit();
		return(FALSE);
	}


	static int flag_pressed = 0;

	static int in_box(int x0, int y0, int x, int y, int w, int h)
	{
		if( (x0 > x && x0 < x + w) && (y0 > y && y0 < y + h)) 
			return 1;
		return 0;
	}
	static void shape_pressed (GtkWidget *widget, GdkEventButton *event)
	{
		int i;
		int px, py, prootx, prooty;
		GdkModifierType mask;


		flag_pressed = 1;
		//�ڹ���������
		if(event->window != fixed->window) {
			flag_pressed = 0;
			return;
		}

		//�ڹ���������
		if(in_box((int)event->x, (int)event->y,  
			skinimage.main.x, skinimage.main.y,
			skinimage.main.y, skinimage.main.h)){
			flag_pressed = 0;
			return;
		}

		//�Ƿ����˰�ť
		for(i=0; i<7; i++) {
			//silly method
			if(!skinimage.images[i].im1) continue;
			if(in_box((int)event->x, (int)event->y,
				skinimage.images[i].x, skinimage.images[i].y,
				skinimage.images[i].w, skinimage.images[i].h)){
					gdk_imlib_paste_image(
					skinimage.images[i].im2, fixed->window, 
					skinimage.images[i].x,
					skinimage.images[i].y,
					skinimage.images[i].w,
					skinimage.images[i].h);
				} else {
					gdk_imlib_paste_image(
					skinimage.images[i].im1, fixed->window, 
					skinimage.images[i].x,
					skinimage.images[i].y,
					skinimage.images[i].w,
					skinimage.images[i].h);
				}
		}

		//�������
		gdk_window_get_pointer(root_win, &prootx, &prooty, &mask);
		root_pos.x = prootx;
		root_pos.y = prooty;
		gdk_window_get_pointer(fixed->window, &px, &py, &mask);
		win_pos.x = prootx - px;
		win_pos.y = prooty - py;

		//�������
		gtk_grab_add (widget);
		gdk_pointer_grab (widget->window, TRUE,
			GDK_BUTTON_RELEASE_MASK |
			GDK_BUTTON_MOTION_MASK  | 
			GDK_POINTER_MOTION_MASK,
			//GDK_POINTER_MOTION_HINT_MASK,
			NULL, NULL, 0);
	}

	static void shape_released (GtkWidget *widget, GdkEventButton *event)
	{
		int i;

		flag_pressed = 0;

		//������һ����ť��������
		for(i=0; i<7; i++) {
			//silly method
			if(!skinimage.images[i].im1) continue;
			gdk_imlib_paste_image(
				skinimage.images[i].im1, fixed->window, 
				skinimage.images[i].x, skinimage.images[i].y,
				skinimage.images[i].w, skinimage.images[i].h);
			if(in_box((int)event->x, (int)event->y,
				skinimage.images[i].x, skinimage.images[i].y,
				skinimage.images[i].w, skinimage.images[i].h)){
				printf("Button %s called.\n", 
					skinimage.images[i].file);
				reload_skin(&skinimage);
				if(!mystrncmp(skinimage.images[i].file, "exit"))
					exit(1);
			}

		}

		//�ͷ����
		gtk_grab_remove (widget);
		gdk_pointer_ungrab (0);
	}

	static void shape_motion (GtkWidget *widget, GdkEventMotion *event)
	{
		int i;
		gint px, py, prootx, prooty;
		GdkModifierType mask;


		if(!flag_pressed ) return;
		if(!(event->state & GDK_BUTTON1_MASK)) return;

		//�ƶ�����
		gdk_window_get_pointer(root_win, &prootx, &prooty, &mask);
		gtk_widget_set_uposition(window, 
			win_pos.x + prootx - root_pos.x, 
			win_pos.y + prooty - root_pos.y);
	}



	int main (int argc, char *argv[] )
	{
		GdkBitmap *mask;
		GtkStyle *style;
		GdkGC *gc;
		GtkWidget *tree;

		int idx;

		srand(time(NULL));
		idx = (int) random() % 5;

		//��ʼ��
		gtk_set_locale();
		gtk_init (&argc, &argv);

		//imlib ��ʼ��
		gdk_imlib_init();
		gtk_widget_push_visual(gdk_imlib_get_visual());
		gtk_widget_push_colormap(gdk_imlib_get_colormap());

		//������
		root_win = gdk_window_foreign_new (GDK_ROOT_WINDOW ());
		//�����ޱ߽細��
		window = gtk_window_new( GTK_WINDOW_POPUP );
		gtk_widget_set_events(window,
			gtk_widget_get_events (window) |
			GDK_BUTTON_MOTION_MASK |
			GDK_POINTER_MOTION_MASK |
			//GDK_POINTER_MOTION_HINT_MASK |
			GDK_BUTTON_PRESS_MASK);
		gtk_signal_connect (GTK_OBJECT (window), "delete_event",
			GTK_SIGNAL_FUNC (close_application), NULL);
		gtk_signal_connect (GTK_OBJECT (window), "button_press_event",
			GTK_SIGNAL_FUNC (shape_pressed),NULL);
		gtk_signal_connect (GTK_OBJECT (window), "button_release_event",
			GTK_SIGNAL_FUNC (shape_released),NULL);
		gtk_signal_connect (GTK_OBJECT (window), "motion_notify_event",
			GTK_SIGNAL_FUNC (shape_motion),NULL);



		gtk_widget_show (window);

		//����skin������
		load_skin(&skinimage, sample_skins[idx]);

		//����һ�����㶨λ����
		fixed = gtk_fixed_new();
		gtk_widget_set_usize(fixed, skinimage.win.w, skinimage.win.h);
		gtk_container_add( GTK_CONTAINER(window), fixed );
		gtk_widget_show( fixed );

		//����ͼ��
		gdk_pixmap = gdk_imlib_move_image(skinimage.win.im1);
		gdk_mask = gdk_imlib_move_mask(skinimage.win.im2);
		pixmap = gtk_pixmap_new( gdk_pixmap, gdk_mask );
		//gdk_window_set_back_pixmap(window->window, gdk_pixmap, 0);
		gtk_fixed_put(GTK_FIXED(fixed), pixmap, 0, 0 );
		gtk_widget_show( pixmap );

		//������������
		scrolled_window = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_policy(
                        GTK_SCROLLED_WINDOW (scrolled_window),
                        GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
		gtk_widget_set_usize(scrolled_window, 
			skinimage.main.w, skinimage.main.h);
		gtk_fixed_put(GTK_FIXED(fixed), scrolled_window, 
			skinimage.main.x, skinimage.main.y);
		gtk_widget_show(scrolled_window);

		//������
		tree = create_tree(scrolled_window);
		gtk_widget_show(tree);
		
		//�Դ�����������
		gdk_window_shape_combine_mask(window->window, gdk_mask,0,0);

		//���ù��
		gdk_window_set_cursor(window->window,
			gdk_cursor_new(GDK_LEFT_PTR));

		//���ô��ڵ�λ��
		gtk_widget_set_uposition(window, 200, 200 );
		//gtk_widget_show(window);
		gtk_main ();
          
		return(0);
	}
