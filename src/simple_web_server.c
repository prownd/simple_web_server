#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include "init_socket.h"
#include "http_session.h"
#include "get_time.h"
int main(int argc,char* argv[])
{
	int listen_fd;
	int connect_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	bzero(&server_addr,sizeof(struct sockaddr_in));
	bzero(&client_addr,sizeof(struct sockaddr_in));
	if(init_socket(&listen_fd,&server_addr)==-1)
	{
		perror("init_socket() error,in simple_web_server");
		exit(EXIT_FAILURE);
	}
	socklen_t addrlen=sizeof(struct sockaddr_in);
	char * client_ip=NULL;
	pid_t pid;
	while(1)
	{
		if((connect_fd=accept(listen_fd,(struct sockaddr *)&client_addr,&addrlen))==-1)
		{
			perror("accept () error in simple_web_server.c");
			continue;
		}
		if((pid=fork())>0)
		{
			close(connect_fd);
			continue;
		}else if(pid==0)
		{
			close(listen_fd);
			client_ip=inet_ntoa(client_addr.sin_addr);
			printf("pid %d process http session from %s:%d \n",getpid(),client_ip,htons(client_addr.sin_port));
			if(http_session(&connect_fd,&client_addr)==-1)
			{
				perror("http_session () error in simpel_web_server.c");
				shutdown(connect_fd,SHUT_RDWR);
				printf("pid %d loss connection to %s \n",getpid(),inet_ntoa(client_addr.sin_addr));
				exit(EXIT_FAILURE);

			}
			printf("pid %d close connection to %s \n",getpid(),inet_ntoa(client_addr.sin_addr));
			shutdown(connect_fd,SHUT_RDWR);
			exit(EXIT_SUCCESS);
		}else
		{
			perror("fork() error in simple_web_server.c");
			exit(EXIT_FAILURE);
		}
	}
	shutdown(listen_fd,SHUT_RDWR);
	return 0;
}
