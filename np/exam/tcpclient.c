#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>

struct sockaddr_in cliaddr;
int lfd,num,port,len;
char buff[1024];

int main()
{
	lfd=socket(AF_INET,SOCK_STREAM,0);

	printf("\nport no:");
	scanf("%d",&port);
	getchar();
	cliaddr.sin_family=AF_INET;
	cliaddr.sin_port=htons(port);
	cliaddr.sin_addr.s_addr=INADDR_ANY; 

	len=sizeof(struct sockaddr);
	if(connect(lfd,(struct sockaddr*)&cliaddr,len)==-1)
	{
		perror("connect");
		exit(1);
	}
	printf("\n enter the text:");
	gets(buff);

	if( num=send(lfd,buff,sizeof(buff),0)<0)
	{ perror("send error");
          exit(1);
	}
	printf("\n sent success");
	printf("\nout now");
	return 0;
}

