#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
int main()
{
	int ser_soc,cli_soc,ser_len,cli_len;
	struct sockaddr_in ser_add;
	struct sockaddr_in cli_add;	
	ser_soc=socket(AF_INET,SOCK_STREAM,0);
	ser_add.sin_family=AF_INET;
	ser_add.sin_addr.s_addr=inet_addr("127.0.0.1");
	ser_add.sin_port = 3240;
	ser_len=sizeof(ser_add);
	bind(ser_soc,(struct sockaddr *)&ser_add,ser_len);
	listen(ser_soc,2);
	printf("Recv from client:\n");
	while(1)
	{
		char c;
		cli_len=sizeof(cli_add);
		cli_soc=accept(ser_soc,(struct sockaddr *)&cli_add,&cli_len);
		while(read(cli_soc,&c,1))
		{
			printf("%c",c);
		}
		close(cli_soc);
		printf("\nConnection terminated");
	}
}
