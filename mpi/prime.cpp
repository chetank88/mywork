#include<mpi.h>
#include<iostream>
#include<math.h>

using namespace std;

int checkP(int ele)
{
		for(int i=2;i*i<=ele;i++)
		{
			 if(ele%i==0)
				 return 0;
		}
		return 1;
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
		int arr[60];
		int p=size*2;
		
		int asize=sizeof(arr)/sizeof(arr[0]);
		printf("enter the array elements:");
	   fflush(stdout);
		for(int i=0;i<p;i++)
		{
			 cin>>arr[i];
		}
		fflush(stdin);

		cout<<"\n";
		
		int x=0;
		int i=0;
		int noOfOddProcc=size/2;
		int noOfElementsProcessed=size*2/noOfOddProcc;
		int lastProcess=noOfElementsProcessed+size*2-noOfElementsProcessed*noOfOddProcc;
		for(i=1;i<noOfOddProcc*2-1;i=i+2)
		{
			
			MPI_Send(&noOfElementsProcessed,1,MPI_INT,i,1,MPI_COMM_WORLD);
			MPI_Send(&arr[x],noOfElementsProcessed,MPI_INT,i,0,MPI_COMM_WORLD);
			x=x+noOfElementsProcessed;
		}
		   MPI_Send(&lastProcess,1,MPI_INT,i,1,MPI_COMM_WORLD);
		   MPI_Send(&arr[x],lastProcess,MPI_INT,i,0,MPI_COMM_WORLD);
			
	    int prm[60];
		int nonprm[60];
		int val=0,val1=0;
         for(i=1;i<size;i=i+2)
		{
		  MPI_Recv(&val,1,MPI_INT,i,1,MPI_COMM_WORLD,&status);
		  MPI_Recv(prm,val,MPI_INT,i,2,MPI_COMM_WORLD,&status);
		  MPI_Recv(&val1,1,MPI_INT,i,3,MPI_COMM_WORLD,&status);
		  MPI_Recv(nonprm,val1,MPI_INT,i,4,MPI_COMM_WORLD,&status);

		    cout<<"\nprime:";
		    for(int j=0;j<val;j++)
		   {cout<<prm[j]<<" ";}
		    cout<<"\n non prime:";
		    for(int j=0;j<val1;j++)
		   {  cout<<nonprm[j]<<" ";}
		 }

		 
	}
	else if(rank%2 !=0)
	{
		int n=0,nbuff[60],k=0,j=0;
		int prm[60];
		int nonprm[60];
		MPI_Recv(&n,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		MPI_Recv(nbuff,n,MPI_INT,0,0,MPI_COMM_WORLD,&status);

		for(int i=0;i<n;i++)
		{
			if(checkP(nbuff[i]))
			{
				prm[k++]=nbuff[i]; 

			}
			else
			{
				nonprm[j++]=nbuff[i]; 
			}
		}
		
		MPI_Send(&k,1,MPI_INT,0,1,MPI_COMM_WORLD);
		MPI_Send(&prm,k,MPI_INT,0,2,MPI_COMM_WORLD);
	
		MPI_Send(&j,1,MPI_INT,0,3,MPI_COMM_WORLD);
		MPI_Send(&nonprm,j,MPI_INT,0,4,MPI_COMM_WORLD);
		
	}
	
	
	MPI_Finalize();
	return 0;

}

/*
 /*MPI_Recv(&val,1,MPI_INT,i,1,MPI_COMM_WORLD,&status);
		  MPI_Recv(prm,val,MPI_INT,i,2,MPI_COMM_WORLD,&status);
		  MPI_Recv(&val1,1,MPI_INT,i,3,MPI_COMM_WORLD,&status);
		  MPI_Recv(nonprm,val1,MPI_INT,i,4,MPI_COMM_WORLD,&status);

		    cout<<"\nprime:";
		    for(int j=0;j<val;j++)
		   {cout<<prm[j]<<" ";}
		    cout<<"\n non prime:";
		    for(int j=0;j<val1;j++)
		   {  cout<<nonprm[j]<<" ";}

		 else
	{
		/*int n=0,nbuff[6];
		MPI_Recv(&n,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		MPI_Recv(nbuff,n,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		cout<<"bye\n";
	}
		   
		   
*/

