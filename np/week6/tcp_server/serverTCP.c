#include "serverh.h"
//.23
struct sockaddr_in servaddr,cliaddr;
int sfd,connfd;
socklen_t clilen;
char ed[5]="exit";

int len,i=0,r,b,l,port,list;
char buff[1024],str[1024],c;
int new_fd=-1;

void createAndBind()
{

	sfd=socket(AF_INET,SOCK_STREAM,0);
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
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(port);
	b=bind(sfd,(struct sockaddr*)&servaddr, sizeof(servaddr));
	if(b==-1)
	{
	  perror("bind");
	  exit(-1);
        }
	
	printf("\nBind success\n");
        fflush(stdout);
	//printf("\nListening...");
      clilen=sizeof(cliaddr);
    
      //printf("\nListening...");
	
        list = listen(sfd, 10);
       if (list== -1) {
      perror("listen");
      exit(1);
    }
      printf("\nListening...");
	
	new_fd = accept(sfd, (struct sockaddr*)&cliaddr,&clilen);
  if (new_fd == -1) {
          perror("accept");
          exit(-1);
   }
printf("\nAccept success\n");
    


}

int listenservice()
{

    int id=1;
      r=recv(new_fd, &id,1, 0);
      return id;
}

void service1()
{
  
 
  while(1)
  {

	//r=recvfrom(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr, &clilen);
        r=recv(new_fd,buff,sizeof(buff),0);
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
	  //sendto(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
           send(new_fd,buff,sizeof(buff), 0);
	}

      else
     {
      
      printf("\nsending to client:");
      fflush(stdout);
      char str[40];
      strcpy(buff,"\0");
      while(fgets(buff,sizeof(buff),fd)!=NULL)
       {
          //sendto(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
            send(new_fd,buff,sizeof(buff), 0);
       }

     }

  }

}

void service2()
{
        //r=recvfrom(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr, &clilen);
	r=recv(new_fd,buff,sizeof(buff), 0);
	//buff[r-1]='\0';
         printf("\n from clienr:%s",buff);
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
           
    //sendto(sfd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,clilen);    
      send(new_fd,buff,sizeof(buff), 0);
  
}

