#include<iostream>
#include<mpi.h>
#include<string.h>

using namespace std;


int search(char arr[],char key[])
{
	char temp[40][40];
	int x=0,y=0;

	for(int i=0;i<strlen(arr);i++)
	{
		while(arr[i]!=' ')
		{
			temp[x][y++]=arr[i];
		}
		x++;
		y=0;
	}

	   for(int i=0;i<x;i++)
			if(strcmp(temp[i],key)==0)
				return 1;
	
		return 0;
}



int main(int argc,char** argv)
{
	int rank,size;

	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	

	if(rank==0)
	{
		char msg[40]="my name is khan country";
		char key[10]="khan";
		int lenstr=strlen(msg);
		int lenkey=strlen(msg);
		int k=0;
		int pos[40]={0};
		int spaceCount=0;
		for(int i=0;i<lenstr;i++)
		{
			if(msg[i]==' ')
			{
				
				pos[spaceCount++]=i;
			}
		}

		int divPos=pos[spaceCount/2]+1;
		int length=lenstr-divPos;
		MPI_Ssend(&length,1,MPI_INT,1,0,MPI_COMM_WORLD);
		MPI_Ssend(&msg[divPos],length,MPI_CHAR,1,1,MPI_COMM_WORLD);
		MPI_Ssend(&key,1,MPI_INT,1,2,MPI_COMM_WORLD);
		MPI_Ssend(key,lenkey,MPI_CHAR,1,3,MPI_COMM_WORLD);

		//MPI_Recv(&len,1,MPI_INT,1,0,MPI_COMM_WORLD,&status);
		//MPI_Recv(msg,len,MPI_CHAR,1,1,MPI_COMM_WORLD,&status);
		//msg[len]='\0';
		//cout<<"\nin rank 0 msg:"<<msg;
			
	}
	else if(rank==1)
	{
		int len=0,divPos=0;
		char msg[40],key[10];
		MPI_Recv(&divPos,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		MPI_Recv(msg,divPos,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		MPI_Recv(&len,1,MPI_INT,0,2,MPI_COMM_WORLD,&status);
		MPI_Recv(key,len,MPI_CHAR,0,3,MPI_COMM_WORLD,&status);

		//int res=search(msg,key);
		//if(res==1)
			cout<<"\n element found "<<msg<<" "<<key;
	}

	MPI_Finalize();

	return 0;
}
