#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#define N 1024

int main(int argc, char **argv)
{
if(argc<2)
{
printf("Usage: <portNo>\n");
exit(1);
}
struct sockaddr_in server_addr,clientAddr;
memset(&server_addr, '0', sizeof(server_addr));
int sfd,count,slen=sizeof(server_addr);
char recv_buff[N],send_buff[N]="server:Roger", msg[N];

sfd=socket(AF_INET,SOCK_DGRAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
bind(sfd, (struct sockaddr*) &server_addr, sizeof(server_addr)); 

while(1){
	count=recvfrom(sfd, recv_buff, 1024, 0, (struct sockaddr*)&clientAddr, &slen);

	strcpy(msg,inet_ntoa(clientAddr.sin_addr));
	strcat(msg, ": ");
	printf("%s\n",strcat(msg,recv_buff));
	sleep(2);	
	count=sendto(sfd, send_buff, 1024, 0,(struct sockaddr*)&clientAddr, slen);
	}
}

