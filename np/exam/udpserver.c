#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>

struct sockaddr_in saddr,caddr;
int lfd,nfd,port;
char buff[1024];

int main()
{
	printf("\nport no:");
	scanf("%d",&port);
	getchar();
	lfd=socket(AF_INET,SOCK_DGRAM,0);

	memset(saddr.sin_zero,'\0',8);
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(port);
        saddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	if(bind(lfd,(struct sockaddr*)&saddr,sizeof(saddr))==-1)
	{
		perror("bind");
		exit(1);
	}
	
	printf("\nbind successful");
 	int len=sizeof(caddr); 
        int num=recvfrom(lfd,buff,sizeof(buff),0,(struct sockaddr*)&caddr,&len);
        printf("\n telnet:%s",buff);
	
	return 0;

}
