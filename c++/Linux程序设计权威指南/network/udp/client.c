
	/* File: client.c */

	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>

	int main(int argc, char **argv)
	{
		int fd;
		struct sockaddr_in address;
		int address_len;
		char line[80] = "Client to Server string!\n";
		int n;

		//�����׽ӿ�
		fd = socket(AF_INET, SOCK_DGRAM, 0);

		//����
		bzero(&address, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr("127.0.0.1");
		address.sin_port = htons(1234);
		address_len = sizeof(address);

		//��������
		sendto(fd, line, strlen(line)+1, 0, 
			(struct sockaddr *)&address, sizeof(address)); 

		//��������
		n = recvfrom(fd, line, 80, 0, NULL, NULL);
		printf("received %d:%s", n, line);
	}
