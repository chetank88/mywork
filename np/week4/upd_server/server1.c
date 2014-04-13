#include "serverh.h"

struct sockaddr_in servaddr,cliaddr;
int sfd,connfd;
socklen_t clilen;
char ed[5]="exit";

int len,i=0,r,b,l,port;
char buff[1024],str[1024],c;

void createAndBind()
{

	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd==-1)
	{
	  perror("Socket");
	  exit(-1);
	}
	memset(servaddr.sin_zero,'\0',sizeof(servaddr.sin_zero));
	printf("\n Enter the port no:");
	scanf("%d",&port);
	//printf("\n Port No is %d",port);
        
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(port);
	b=bind(sfd,(struct sockaddr*)&servaddr, sizeof(servaddr));
	if(b==-1)
	{
	  perror("bind");
	  exit(-1);
        }

      clilen=sizeof(cliaddr);

}

int listenservice()
{
     int id=1;
      r=recvfrom(sfd,&id,1,0,(struct sockaddr*)&cliaddr, &clilen);
      return id;
}

void service1()
{
  
 
  while(1)
  {

	r=recvfrom(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr, &clilen);
	buff[r-1]='\0';
        printf("\nReceived from client:%s",buff);
        fflush(stdout);
	if(strcmp(buff,ed)==0)
	{
	   break;
	}
        

	FILE* fd=fopen(buff,"r");

	if(fd==NULL)
	{
          printf("\nfile does not exist");
          fflush(stdout);
	  strcpy(buff,"file does not exist");
	  sendto(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
	}

      else
     {
      
      printf("\nsending to client:");
      fflush(stdout);
      char str[40];
      strcpy(buff,"\0");
      while(fgets(buff,sizeof(buff),fd)!=NULL)
       {
          sendto(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
       }

     }

  }

}

void service2()
{
        r=recvfrom(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr, &clilen);
	//buff[r-1]='\0';
         printf("\n no:%d",r);
         //printf("\n%s",buff);
          int i=0,k=0;
          int len=strlen(buff);
         for(i=len-1;i>=len/2;i--)
           {
               char temp=buff[k];
                buff[k]=buff[i];
                buff[i]=temp; 
                //printf("%c ",buff[k]);
                //printf("%c\n",buff[i]);
		k++;  
           }
           
    sendto(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,clilen);    
  
}

