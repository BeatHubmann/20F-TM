#include <mpi.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits>
#include "Blas.H"
#include "Utilities.H"

using namespace std;

int main(int argc, char *argv[])
{
    int mpi_size,mpi_rank;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&mpi_size);
    MPI_Comm_rank(MPI_COMM_WORLD,&mpi_rank);

    MPI_Status status;
    double t0,T0;
    double *A,*B,*C;
    int IP,IT;
    int i,j,N,N_loc;
    int no_iteration;

    no_iteration = 10;

    for(IT=1;IT<argc;IT++){
    
        N     = atoi(argv[IT]);
	N_loc = ceil((double)N/mpi_size);

	A  = new double[N*N];
	
	if(!mpi_rank){
	
	    B  = new double[N*N];
	    C  = new double[N*N];

	    for(i=0;i<N;i++){
	        for(j=0;j<N;j++){
		    A[i+j*N] = (randn(),randn());
		    B[i+j*N] = (randn(),randn());
		}
	    }
	    
	    for(IP=1;IP<mpi_size;IP++){
	        MPI_Send(A,N*N,MPI_DOUBLE,IP,2*(IP-1),MPI_COMM_WORLD);
		MPI_Send(&B[IP*N*N_loc],N*(min(N,(IP+1)*N_loc)-IP*N_loc),MPI_DOUBLE,IP,\
			 2*(IP-1)+1,MPI_COMM_WORLD);
	    }
	    
	}else{
	  
	    B = new double[N_loc*N];
	    C = new double[N_loc*N];

	    MPI_Recv(A,N*N,MPI_DOUBLE,0,2*(mpi_rank-1),MPI_COMM_WORLD,&status);
	    MPI_Recv(B,N*(min(N,(mpi_rank+1)*N_loc)-mpi_rank*N_loc),MPI_DOUBLE,\
		     0,2*(mpi_rank-1)+1,MPI_COMM_WORLD,&status);
	  
	}

	T0 = 0.0;
	
	for(int iter=0;iter<no_iteration;iter++){

	    t0    = get_time(0.0);
	    
	    c_dgemm('N','N',N,min(N,(mpi_rank+1)*N_loc)-mpi_rank*N_loc,N,1.0,A,	\
		    N,B,N,0.0,C,N);

	    if(mpi_rank){
	      
	        MPI_Send(C,N*(min(N,(mpi_rank+1)*N_loc)-mpi_rank*N_loc),MPI_DOUBLE,\
			 0,mpi_rank,MPI_COMM_WORLD);
		
	    }else{
	      
	        for(IP=1;IP<mpi_size;IP++){
		    MPI_Recv(&C[IP*N_loc*N],N*(min(N,(IP+1)*N_loc)-IP*N_loc),MPI_DOUBLE,\
			     IP,IP,MPI_COMM_WORLD,&status);
		}
	    }
	    
	    T0 = T0+get_time(t0);
	}

	delete[] A;
	delete[] B;
	delete[] C;
    }

    printf("mpi_rank %i: %lg (s)\n",mpi_rank,T0/no_iteration);
    
    MPI_Finalize();
    
    return 0;
}

/************************************************************************************************/
