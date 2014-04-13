#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int sockfd, fromlen;
  char buffer[100];
  struct sockaddr_in my_addr, client_addr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
      printf("Error: The socket could not be created!\n");
      exit(EXIT_FAILURE);
  }
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(80);
  my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  if (bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1)
  {
      printf("Error: The binding could not be established!\n");
      exit(EXIT_FAILURE);
  }
  client_addr.sin_family = AF_INET;
  client_addr.sin_port = htons(80);
  client_addr.sin_addr.s_addr = inet_addr("127.0.0.2");
  fromlen = sizeof(struct sockaddr);
  if (recvfrom(sockfd, buffer, 100, 0, (struct sockaddr*)&client_addr, &fromlen) == -1)
  {
      printf("Error: The message could not be recieved!\n");
      exit(EXIT_FAILURE);
  }
  else
  {
      printf("Message: %s\n", buffer);
  }
  close(sockfd);
  return 0;
}
