//http://gribblelab.org/CBootcamp/12_Compiling_linking_Makefile_header_files.html
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#ifndef fsize
#define fsize 8
#endif

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

extern packet *head;

void fragmentation(char fragments[fsize+1],char text[]);
void createPacket(char data[fsize],header *hd);
void setheader(int off,char data[fsize]);
void displayP();
void send();
void recv(packet* p);
void defrag();
void displayDP();
