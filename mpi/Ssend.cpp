#include<iostream>
#include<mpi.h>
#include<string.h>

using namespace std;

int main231(int argc,char** argv)
{
	int rank,size;

	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	

	if(rank==0)
	{
		char msg[40]="chetan";
		int len=strlen(msg);
		MPI_Ssend(&len,1,MPI_INT,1,0,MPI_COMM_WORLD);
		MPI_Ssend(msg,len,MPI_CHAR,1,1,MPI_COMM_WORLD);

		MPI_Recv(&len,1,MPI_INT,1,0,MPI_COMM_WORLD,&status);
		MPI_Recv(msg,len,MPI_CHAR,1,1,MPI_COMM_WORLD,&status);
		msg[len]='\0';
		cout<<"\nin rank 0 msg:"<<msg;
			
	}
	else if(rank==1)
	{
		int len;
		char msg[40];
		MPI_Recv(&len,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		MPI_Recv(msg,len,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		msg[len]='\0';
		cout<<"\nin rank 1 msg:"<<msg;

		MPI_Ssend(&len,1,MPI_INT,0,0,MPI_COMM_WORLD);
		MPI_Ssend(msg,len,MPI_CHAR,0,1,MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}
