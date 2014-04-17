#include<stdlib.h>
#include<stdio.h>
#include<netinet/in.h>
#include<string.h>


struct sockaddr_in caddr,saddr;
int lfd,nfd,port,num;
char buff[1024];

int main()
{
	lfd=socket(AF_INET,SOCK_DGRAM,0);

	printf("\nport no:");
	scanf("%d",&port);
	getchar();
      
	memset(caddr.sin_zero,'\0',8);
	caddr.sin_family=AF_INET;
	caddr.sin_port=htons(port);
	caddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	printf("\nenter the text:");
	gets(buff);

        int len=sizeof(saddr);
	if( num=sendto(lfd,buff,sizeof(buff),0,(struct sockaddr*)&caddr,sizeof(caddr))<0)
	{
		printf("\nsend error");
		exit(-1);
	}
	printf("\nsent success");

	return 0;
}
