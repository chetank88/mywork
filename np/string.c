#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define fsize 8


typedef struct header
{
 int foffset;
 int id;
}header;

 

typedef struct packet
{
  header *hd;
  char data[fsize+1];
  struct packet* next;
}packet;
  
packet *head;

void createPacket(char data[fsize],header *hd)
{
   printf("\n%s",data);
   packet *temp;
   temp=head;
   packet *prev;
    if(head->next==NULL)
     {
          temp=(struct packet*)malloc(sizeof(packet));
          head->next=temp;
          strcpy(temp->data,data);
          temp->hd=hd;
          temp->next=NULL;
           
          return;
     }
     while(temp!=NULL)
     {
        prev=temp;
        temp=temp->next;
     }
      temp=(struct packet*)malloc(sizeof(packet));
      prev->next=temp;
      strcpy(temp->data,data);
       temp->hd=hd;
       temp->next=NULL;
   
}

void setheader(int off,char data[fsize])
{
   header *temp=(struct header*)malloc(sizeof(header));
   temp->foffset=off; 
   createPacket(data,temp);
    
}

void displayP()
{
  packet *temp=(struct packet*)malloc(sizeof(packet));
   temp=head->next;
   while(temp!=NULL)
   {
      printf("\n%d %s",temp->hd->foffset,temp->data);
      temp=temp->next;
   }
}
 
void fragmentation(char fragments[fsize+1],char text[])
{
   int a=0,i=0;
   int off=0;
   while(strlen(text)>fsize)
 {
  memcpy(fragments,text,fsize);
   fragments[fsize+1]='\0';
  strcpy(text,&text[fsize]);
  off=a/fsize;
  setheader(off,fragments);  
  a+=fsize;
 }
  strcpy(fragments,text);
  fragments[strlen(text)]='\0';
  setheader(a/fsize,fragments);
 
}

int main()
{
  char text[]="my very elegant mother just showed us nine planets";
  char fragments[fsize+1];
  head=(struct packet*)malloc(sizeof(packet));  
  head->next=NULL;

  fragmentation(fragments,text);
  
  displayP();

}
