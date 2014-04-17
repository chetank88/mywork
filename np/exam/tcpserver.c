#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>

struct sockaddr_in saddr,cliaddr;

int port,lfd,nfd,num;
char buff[1024];

int main()
{
	lfd=socket(AF_INET,SOCK_STREAM,0);

	printf("\n port no:");
	scanf("%d",&port);
	//getchar();

			saddr.sin_family=AF_INET;	
			saddr.sin_port=htons(port);
		        saddr.sin_addr.s_addr=inet_addr("127.0.0.1");

			if(bind(lfd,(struct sockaddr*)&saddr,sizeof(saddr))==-1)
			{
			perror("bind error");
			exit(1);
			}
                     for(;;)
                     {
			if(listen(lfd,10)==-1)
			{
			perror("listen error");
			exit(1);	
			}

			int len=sizeof(struct sockaddr);
	
			int pid=fork();
                       if(pid==0)
                       {
			if((nfd=accept(lfd,(struct sockaddr*)&cliaddr,&len))==-1)
			{
			perror("accept error");
			exit(1);
			}

			if(num=recv(nfd,buff,sizeof(buff),0)<0)
 			{
				perror("recv error");
				exit(1);
			}
			printf("\nifrom client:%s",buff);
			close(nfd);
                      }
			wait();
		    }
                        close(lfd);
			return 0;
}

