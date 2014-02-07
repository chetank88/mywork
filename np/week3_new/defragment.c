#include"fragment.h"

char str[50];
packet *pack[50];
int i=0,k=0;
void defrag()
{
	while(k<i)
	strcat(str,pack[k++]->data);
	
}
void recv(packet* p)
{
	pack[p->hd->foffset]=p;
        i++;
}

void displayDP()
{
	printf("\n%s\n",str);
}
