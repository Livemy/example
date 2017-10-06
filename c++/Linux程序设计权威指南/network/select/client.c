
	/* File: client.c */

	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>

	int main(int argc, char **argv)
	{
		int fd;
		struct sockaddr_in address;
		int address_len;
		int rtval;
		char *data = "Client to Server string!\n";
		char data2[100];
		int len;

		//�����׽ӿ�
		fd = socket(AF_INET, SOCK_STREAM, 0);

		//����
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr("127.0.0.1");
		address.sin_port = htons(1234);
		address_len = sizeof(address);

		rtval = connect(fd, (struct sockaddr *)&address, address_len);
		if(rtval == -1) exit(1);

		//��������
		writen(fd, (void *)data, strlen(data));
		printf("sent line:%s", data);

		//��������
		len = readline(fd, (void *)data2, 100);
		printf("readline:%s", data2);

		printf("client exit.\n");
		//�ر�
		close(fd);
	}
