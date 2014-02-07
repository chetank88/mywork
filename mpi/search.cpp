#include<iostream>
#include<mpi.h>
#include<string.h>

using namespace std;

int search(int arr[],int key,int n)
{
	
		for(int i=0;i<n;i++)
		{
			if(arr[i]==key)
			{
				return i+1;
			}
		}
		return 0;
}

int main012(int argc,char** argv)
{
	int rank,size;

	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	

	if(rank==0)
	{
	  int n,arr[40],key=-1;

	    fflush(stdout);
		fflush(stdin);
		cout<<"\nenter the no of elements";
		cin>>n;

		cout<<"\nenter the elements";
		for(int i=0;i<n;i++)
		{
			cin>>arr[i];
		}

		cout<<"\nenter the search key:";
		cin>>key;

		MPI_Ssend(&n,1,MPI_INT,1,0,MPI_COMM_WORLD);
		MPI_Ssend(&arr[n/2],n/2,MPI_INT,1,1,MPI_COMM_WORLD);
		MPI_Ssend(&key,1,MPI_INT,1,2,MPI_COMM_WORLD);
		int res=search(arr,key,n/2);

		if(res!=0)
		{
			cout<<"\nelement found in process 0 at pos:"<<res;
		}
		int res1=0;
		MPI_Recv(&res1,1,MPI_INT,1,3,MPI_COMM_WORLD,&status);

		if(res1==0 && res==0)
		{
			cout<<"\nelement not found";
		}
		
			
	}
	else if(rank==1)
	{
		int n,key=-1;
		int buf[40];
		MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		MPI_Recv(buf,n,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		MPI_Recv(&key,1,MPI_INT,0,2,MPI_COMM_WORLD,&status);

		int res=search(buf,key,n/2);

		if(res!=0)
		{
			cout<<"\nelement found in process 1 at pos:"<<res*2;
		}

		MPI_Ssend(&res,1,MPI_INT,0,3,MPI_COMM_WORLD);
		
	}

	MPI_Finalize();

	return 0;
}
