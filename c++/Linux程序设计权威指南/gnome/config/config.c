
	/* File: config.c */



	/*
	Config File Contents:

	[Global]
	����=20
	�۸�=8900
	Ʒ��=Compaq
	Ӳ��=��ʾ�� ��� ����\\ 
	*/

	#include <gnome.h>

	#define PACKAGE "TestGnome"
	#define VERSION "1.0"

	void save_settings()
	{
		const char *values[] = {"��ʾ��", "���", "���� "};

		gnome_config_push_prefix ("/"PACKAGE"/Global/");

		gnome_config_set_int ("����", 20);
		gnome_config_set_int ("�۸�", 8900);
		gnome_config_set_string ("Ʒ��", "Compaq");
		gnome_config_set_vector("Ӳ��", 3, values);
	
		gnome_config_pop_prefix ();
		gnome_config_sync ();
	}

	void get_settings()
	{
		int i;
		int amount, price;
		char *brand;
		int len;
		char **vec;
	 
                printf("Get Config from file:%s\n",
			gnome_config_get_real_path(PACKAGE));


		gnome_config_push_prefix ("/"PACKAGE"/Global/");
	 
		amount = gnome_config_get_int ("����");
		price = gnome_config_get_int ("�۸�");
		brand = gnome_config_get_string("Ʒ��");
	
		printf("����:%d �۸�:%d Ʒ��:%s\n", amount, price, brand);

		gnome_config_get_vector("Ӳ��", &len, &vec);
		for(i=0; i<len; i++) 
			printf("item:%s\n", vec[i]);

		gnome_config_pop_prefix ();
		gnome_config_sync ();
	
	}



	int main(int argc, char **argv)
	{
                //��ʼ��
                gnome_init(PACKAGE, VERSION, argc, argv);

		save_settings();
		get_settings();

		return 0;
	}
