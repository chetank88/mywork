#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>

int main()
{
  int sockfd, fromlen;
  char buffer[100];
  struct sockaddr_in their_addr,server_addr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
      printf("Error: The socket could not be created!\n");
      exit(EXIT_FAILURE);
  }
  their_addr.sin_family = AF_INET;
  their_addr.sin_port = htons(80);
  their_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

 if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) 
   {
        perror("connect");
        exit(1);
    }


  if (send(new_fd, "Hello, world!\n", 14, 0) == -1)
     perror("send");

  close(sockfd);
  return 0;
}
