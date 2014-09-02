#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int i;
    struct hostent *he, *ve;
    struct in_addr **addr_list;

    if (argc != 2) {
        fprintf(stderr,"usage: hostname\n");
        return 1;
    }

    if ((he = gethostbyname(argv[1])) == NULL) {  // get the host info
        herror("gethostbyname");
        return 2;
    }

    printf("Official name is: %s\n", he->h_name);
    printf("IP addresses:\n");
    addr_list = (struct in_addr **)he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++) {
        printf("%s \n", inet_ntoa(*addr_list[i]));
    }
    printf("\n");

struct in_addr ipaddr;
char addr[100];
//inet_pton(AF_INET, "209.15.13.134", &ipaddr);
//ipaddr.s_addr=inet_addr("209.15.13.134");
//printf("Host name: %s\n",  inet_ntoa(ipaddr));
//ve = gethostbyaddr(&ipaddr, sizeof(ipaddr), AF_INET);
//ipaddr=(struct in_addr) *(ve->h_addr);
//addr_list = (struct in_addr *)he->h_addr;
//printf("Host name: %s\n",  inet_ntoa(ipaddr));

    return 0;
}
