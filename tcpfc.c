#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<fcntl.h>
#include <string.h>
#include <sys/types.h>
#define IP "192.168.25.119" //"192.168.25.123"
#define N 256
#define M 256
int main(int argc, char **argv)
{
 if (argc<4){
printf("usage <filename> <portNo> <serverIP>\n");
exit(1);
}

char *buf=(char *)malloc(sizeof(char)*M);
int len,fd2;
fd2=open(argv[1],O_RDWR | O_CREAT | O_SYNC, 0777);
printf("%s %d\n",argv[1], fd2);
struct sockaddr_in server_addr,client_addr;
int sfd,count, slen=sizeof(server_addr);
char recv_buff[N],send_buff[N]="this is client, send me a response";

sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<=0){
printf("error socket"); exit(1);}
memset(&server_addr, '0', sizeof(server_addr));
memset(&client_addr, '0', sizeof(client_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[3]);//htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[2])); 
connect(sfd,(struct sockaddr*)&server_addr, slen);// BLocking.. 

count=send(sfd, send_buff, N, 0);
len=read(sfd,buf,M);
printf("receiving file...\n");
int j=0;
while(len>0)
{
write(fd2,buf,len);
len=read(sfd,buf,M);
//j++;
//printf("\nwhile len %d %d\n", len,j);
}

close(fd2);
close(sfd);
printf("Done, downloaded is file stored as %s\n", argv[1]);
}

