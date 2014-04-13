#include "serverh.h"



int main()
{
  createAndBind();
  printf("Listening...");
   fflush(stdout);
  int id=listenservice();

   if(id==1)
    service1();
   else if(id==2)
    service2();


  close(servaddr);
  close(cliaddr); 

 exit(0);
 return 0;
}
