
	/* File: server.c */

	#include <stdio.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>

	int main(int argc, char **argv)
	{
		int fd;
		int address_len;
		struct sockaddr_in address;
		int listenfd;

		//�����׽ӿ�
		fd = socket(AF_INET, SOCK_STREAM, 0);

		//�󶨵�ַ�Ͷ˿�
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = htonl(INADDR_ANY);
		address.sin_port = htons(1234);
		address_len = sizeof(address);
		bind(fd, (struct sockaddr *)&address, address_len);

		//�����׽ӿڶ���
		listenfd = listen(fd, 64);

		while(1) {
			struct sockaddr_in client_address;
			int len;
			int client_sockfd;
			char *data = "Server to Client String!\n";
			char data2[100];
			pid_t pid;

			printf("waiting...");
			fflush(stdout);

			//�ȴ�
			len = sizeof(client_address);
			client_sockfd = accept(fd, 
				(struct sockaddr *)&client_address, &len);

			//�����ӽ���
			if( (pid = fork()) == 0){	//child
				close(listenfd);
				//��������
				bzero((void *)data2, 100);
				readline(client_sockfd, (void *)data2, 100);
				printf("server read line:%s", data2);

				//��������
				writen(client_sockfd,(void *)data,strlen(data));
				printf("server send line:%s", data);

				//�ر����Ӳ����˳�
				close(client_sockfd);
				exit(0);

			}
			close(client_sockfd);		//parent
		}
	}

