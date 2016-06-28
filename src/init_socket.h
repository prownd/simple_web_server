#ifndef INIT_SOCKET_H
#define INIT_SOCKET_H
#include<netinet/in.h>
#define BACKLOG  50
#define PORT  8080
int init_socket(int * listen_fd,struct sockaddr_in * server_addr);
#endif // INIT_SOCKET_H
