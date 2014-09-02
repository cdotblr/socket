#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define N 1024
#define IP "192.168.25.119" //"192.168.25.123"
#define PORT 5000
int main(int argc, char **argv)
{
if(argc<3)
{
printf("Usage <ServerIP> <PortNo>\n");
exit(1);
}


struct sockaddr_in server_addr,client_addr;
int sfd,count, slen=sizeof(server_addr);
char recv_buff[N],send_buff[N]="this is client, send me a response";

sfd=socket(AF_INET,SOCK_STREAM,0);
memset(&server_addr, '0', sizeof(server_addr));
memset(&client_addr, '0', sizeof(client_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);//htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[2])); 
connect(sfd,(struct sockaddr*)&server_addr, slen);// BLocking.. 

count=send(sfd, send_buff, N, 0);
count=recv(sfd, recv_buff, N, 0);
printf("%s\n",recv_buff);
close(sfd);
sleep(3);
}

