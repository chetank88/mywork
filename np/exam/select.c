#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>

struct sockaddr_in myadd,cliadd;
int lfd,nfd,port=7000,fdmax,nbytes;
char buff[1024];
fd_set master,readfd;


void create()
{
  lfd=socket(AF_INET,SOCK_STREAM,0);
  if(lfd==-1)
	{
		perror("error in socket creation");
		exit(-1);
	}

  printf("\nenter the port no:");
  scanf("%d",&port);

  myadd.sin_family=AF_INET;
  myadd.sin_port=htons(port);
  myadd.sin_addr.s_addr=INADDR_ANY;

 if(bind(lfd,(struct sockaddr*)&myadd,sizeof(myadd))==-1)
  {
    perror("\nerror in binding");
    exit(-1);
  }
  printf("\nBind successful");

}

void initfdset()
{
 FD_ZERO(&master);
 FD_ZERO(&readfd);
 fdmax=lfd;
 FD_SET(lfd,&master);
}

void lsten()
{
  if(listen(lfd,10)==-1)
  { 
   perror("listen");
   exit(-1);
 }
 int i=0;
  for(;;)
	{
          readfd=master;
           if(select(fdmax+1,&readfd,NULL,NULL,NULL)==-1)
		{
			perror("select");
			exit(-1);
		}
	  for( i=0;i<=fdmax;i++)
		{
   		   if(FD_ISSET(i,&readfd))
		   {
 		     if(i==lfd)
		     {
		        int len	=sizeof(cliadd);
			if((nfd=accept(lfd,(struct sockaddr*)&cliadd,&len))==-1)
			  {
  				perror("accept");
				exit(-1);		
			  }
			else
			{
				FD_SET(nfd,&master);
				if(nfd>fdmax)
					fdmax=nfd;
			}
			printf("selectserver: new connection on %d port",port);
		     }
		    else
		    {
 			if((nbytes=recv(i,buff,sizeof(buff),0))<=0)
			{
		    		if(nbytes==0)
				printf("\n client closed the connection");
				FD_CLR(i,&master);
			}
			else
			{
				printf("\n from client:%s",buff);
				fflush(stdout);
			}
			
		   }	
	      }
	   }
	}  
}

int main()
{
create();
initfdset();
printf("\n LISTEN");
lsten();
return 0;
}
