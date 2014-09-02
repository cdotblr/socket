#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#define N 1024
#define L 5
#define IP "127.0.0.1"
#define PORT 5000
int main(int argc, char **argv)
{

if(argc<2)
{
printf("Usage <portNo>\n");
exit(1);
}

int count,slen;
char recv_buff[N],send_buff[N],ipa[N];

struct sockaddr_in server_addr, client_addr;
memset(&server_addr, '0', sizeof(server_addr));
slen=sizeof(server_addr);

int sfd,commsfd,j=0;

sfd=socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);// inet_addr(IP);
    server_addr.sin_port = htons(atoi(argv[1])); 

bind(sfd, (struct sockaddr*) &server_addr, sizeof(server_addr)); 
listen(sfd,L); // Non-BLocking.. 
while(1){
       commsfd=accept(sfd,(struct sockaddr*) &client_addr,&slen);// BLocking.. 
        j++;
	if(fork()==0){
		close(sfd);	
		count=recv(commsfd, recv_buff, 1024,0);
		printf("client %d: %s\n",j,recv_buff);
                sleep(3);
		memset(ipa,'0',N);
		bzero(send_buff,N);		
		strcpy(ipa,inet_ntoa(client_addr.sin_addr));
		strcpy(send_buff, "server:Roger, your IP is ");
		strcat(send_buff,ipa);
		count=send(commsfd, send_buff, 1024,0);
		sleep(1);
		count=send(commsfd, send_buff, 1024,0);
		printf("session over for client %d\n",j);
		close(commsfd);
		exit(0);
		}
	close(commsfd);
	}//while
}

