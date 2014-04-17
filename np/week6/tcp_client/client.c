#include "stdio.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "string.h"
#include "stdlib.h"

struct sockaddr_in clientaddr;
socklen_t clientlen;

int len,listenfd,connfd,i=0,r,co,port;
char buff[1000],c;
char ed[5]="exit";

void create()
{
listenfd=socket(AF_INET,SOCK_STREAM,0);
if(listenfd==-1)
{
perror("socket");
exit(-1);
}
memset(clientaddr.sin_zero,'\0',sizeof(clientaddr.sin_zero));
printf("\n\tCLIENT\n");
printf("\n Enter the port no:");
scanf("%d",&port);
getc(stdin);
printf("\n Port No is : %d",port);
clientaddr.sin_family=AF_INET;
clientaddr.sin_addr.s_addr=inet_addr("127.0.0.2");
clientaddr.sin_port=htons(port);



}

int selectService()
{
   int id=1;
    
     printf("\n1.get file content\n2. reverse string");
     printf("\nenter the service id:");
     scanf("%d",&id);
     getc(stdin);
     //sendto(listenfd,&id,1,0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
     //connect(listenfd,());
    if (connect(listenfd, (struct sockaddr *)&clientaddr,
sizeof(struct sockaddr)) == -1) {
perror("connect");
exit(1);
}
     send(listenfd,&id,1, 0);
   return id;
}

void getFileContents()
{
  while(1)
  {
	printf("\n Enter file name:");

	fgets(buff, sizeof(buff), stdin);
	buff[strlen(buff)-1]='\0';
	
	//sendto(listenfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
        send(listenfd,buff,sizeof(buff), 0);
	if(strcmp(buff,ed)==0)
	{
	break;
	}

	//r=recvfrom(listenfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr, &clientlen);
          r=recv(listenfd,buff,sizeof(buff),0);
	printf("\n From Server:%s\n",buff);
	strcpy(buff,"\0");
	
   }
}

void reverseString()
{
        printf("\n Enter the string:");

	fgets(buff, sizeof(buff), stdin);
	buff[strlen(buff)-1]='\0';
	
	//sendto(listenfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
          send(listenfd,buff,sizeof(buff), 0);
	/*if(strcmp(buff,ed)==0)
	{
	break;
	}*/

	//r=recvfrom(listenfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr, &clientlen);
        recv(listenfd,buff,sizeof(buff), 0);
	printf("\n From Server:%s\n",buff);
}

int main()
{

  create();

 int id=selectService();

 if(id==1)
   getFileContents();
 if(id==2)
   reverseString();

close(listenfd);
exit(0);
return 0;
}


