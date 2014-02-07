#include<iostream>
#include<mpi.h>
#include<string.h>

using namespace std;

int sumRow(int arr[],int n)
{
	int sum=0;
	
		for(int i=0;i<n;i++)
		{
			sum+=arr[i];
		}
		return sum;
}


int main000(int argc,char** argv)
{
	int rank,size;

	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	

	if(rank==0)
	{
		int n,arr[40][40],sum=0,ttsum=0,col[40]={0};

	    fflush(stdout);
		fflush(stdin);
		cout<<"\nenter the matrix size";
		cin>>n;

		cout<<"\nenter the elements";
		for(int i=0;i<n;i++)
		{
	      for(int j=0;j<n;j++)
		
			cin>>arr[i][j];
		}

		for(int i=1;i<n;i++)
		{
			MPI_Ssend(&n,1,MPI_INT,i,0,MPI_COMM_WORLD);
		    MPI_Ssend(arr[i],n,MPI_INT,i,1,MPI_COMM_WORLD);
		}

		ttsum+=sumRow(arr[0],n);

		for(int i=1;i<n;i++)
		{

	      	MPI_Recv(&sum,1,MPI_INT,i,3,MPI_COMM_WORLD,&status);
			ttsum+=sum;
		}
		
		cout<<"\ntotal row sum="<<ttsum;

		for(int i=1;i<n;i++)
		{
			for(int j=0;j<n;j++)
	      	 {
			  MPI_Recv(&sum,1,MPI_INT,i,j,MPI_COMM_WORLD,&status);
		      col[j]+=sum;
			 }
			
		}
		ttsum=0;
		for(int i=0;i<n;i++)
		 {
			 col[i]+=arr[0][i];
			 ttsum+=col[i];
		 }



		 cout<<"\ncolumn sum is:"<<ttsum;
		

			
	}
	else
	{
		int n,key=-1;
		int buf[40];
		MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		MPI_Recv(buf,n,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		

		int res=sumRow(buf,n);


		MPI_Ssend(&res,1,MPI_INT,0,3,MPI_COMM_WORLD);

		for(int i=0;i<n;i++)
		  MPI_Ssend(&buf[i],1,MPI_INT,0,i,MPI_COMM_WORLD);
		
	}

	MPI_Finalize();

	return 0;
}
