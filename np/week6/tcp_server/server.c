#include "stdio.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "string.h"
#include "stdlib.h"
int main()
{
int len,sfd,connfd,i=0,r,b,l,port;
char buff[1024],str[1024],c;
struct sockaddr_in servaddr,cliaddr;
socklen_t clilen;
sfd=socket(AF_INET,SOCK_DGRAM,0);
if(sfd==-1)
{
perror("Socket");
exit(-1);
}
memset(servaddr.sin_zero,'\0',sizeof(servaddr.sin_zero));
printf("\n Enter the port no:");
scanf("%d",&port);
getc(stdin);
printf("\n Port No is %d",port);
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_port=htons(port);
b=bind(sfd,(struct sockaddr*)&servaddr, sizeof(servaddr));
if(b==-1)
{
perror("bind");
exit(-1);
}
char ed[5]="exit";
clilen=sizeof(cliaddr);
while(1)
{
r=recvfrom(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr, &clilen);
buff[r-1]='\0';

//buff[r]=0;
printf("\n Client:%s",buff);
printf("\n Server:%s",buff);

sendto(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
if(strcmp(buff,ed)==0)
{
break;
}
}
exit(0);
return 0;
}

