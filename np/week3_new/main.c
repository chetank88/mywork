#include "fragment.h"



int main()
{
  char text[]="my very elegant mother just showed us nine planets";
  char fragments[fsize+1];
  
  //memcpy(fragments,text,fsize);
  //fragments[8]='\0';
  //printf("%s",fragments);
  fragmentation(fragments,text);
  displayP();
  send();
  defrag();
  displayDP();

}
