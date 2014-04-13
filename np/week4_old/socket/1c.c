#include<sys/types.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>


int main()
{
	int cli_soc;
	int len;
	struct sockaddr_in add;
	cli_soc=socket(AF_INET,SOCK_STREAM,0);
	add.sin_family=AF_INET;
	add.sin_addr.s_addr=inet_addr("127.0.0.1");
	add.sin_port= 3240;
	len=sizeof(add);
	int con=connect(cli_soc,(struct sockaddr *)&add,len);
	if(con==-1)
	{
		printf("\nConnection Failed\n");
		exit(0);
	}
	printf("Enter message:\n");
	char c='a';
	while(c!=-1)
	{
		scanf("%c",&c);
		write(cli_soc,&c,1);
	}
	close(cli_soc);
	exit(0);
}
