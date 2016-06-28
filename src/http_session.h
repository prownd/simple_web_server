#ifndef HTTP_SESSION_H
#define HTTP_SESSION_H
#include<netinet/in.h>
#define RECV_BUFFER_SIZE 1024
#define SEND_BUFFER_SIZE 1050000
#define URI_SIZE 128
#define TIME_OUT_SEC 10
#define TIME_OUT_USEC 0
#define FILE_OK 200
#define FILE_FORBIDEN 403
#define FILE_NOT_FOUND 404
#define UNALLOW_METHOD 405
#define FILE_TOO_LARGE 413
#define URI_TOO_LONG 414
#define UNSUPPORT_MIME_TYPE 415
#define UNSUPPORT_HTTP_VERSION 505
#define FILE_MAX_SIZE 1048576
#define DOCUMENT_ROOT  "html/"
#define ALLOW  "Allow:Get"
#define SERVER "Server:simple_web_server(0.1 Alpha)/linux"
int http_session(int * connect_fd,struct sockaddr_in * client_addr);
int is_http_protocol(char* msg_from_client);
char * get_uri(char* req_header,char* uri_buf);
int get_uri_status(char* uri);
char* get_mime_type(char* uri);
int get_file_disk(char* uri,unsigned char* entity_buf);
int set_rep_status();
int set_error_information(unsigned char* send_buf,int errorno);
int reply_normal_information(unsigned char* send_buf,unsigned char* file_buf,int file_size,char* mime_type);
#endif 
