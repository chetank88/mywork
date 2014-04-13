#include "stdio.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "string.h"
#include "stdlib.h"

extern struct sockaddr_in servaddr,cliaddr;
extern int sfd,connfd;
extern socklen_t clilen;
extern char ed[5];

void createAndBind();
void service1();
void service2();
