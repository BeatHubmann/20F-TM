#include <math.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits>
#include <omp.h>
#include "Blas.H"
#include "Utilities.H"

using namespace std;

int main(int argc, char *argv[])
{
    int size,rank;

    double t0,t1,t2,T0,T1,T2;
    double *A,*B,*C,*D,*E;
    int i,j,N,IT;
    int no_iteration;

    no_iteration = 10;

    for(IT=1;IT<argc;IT++){
    
        N  = atoi(argv[IT]);

	A   = new double[N*N];
	B   = new double[N*N];
	C   = new double[N*N];
	D   = new double[N*N];
	E   = new double[N*N];

	for(i=0;i<N;i++){
	    for(j=0;j<N;j++){
	        A[i+j*N] = (randn(),randn());
		B[i+j*N] = (randn(),randn());
	    }
	}
	
	T0 = 0.0;
	T1 = 0.0;
	T2 = 0.0;
	
	for(int iter=0;iter<no_iteration;iter++){

	    t0    = get_time(0.0);
	    c_dgemm('N','N',N,N,N,1.0,A,N,B,N,0.0,C,N);
	    T0    = T0+get_time(t0);

	    t1    = get_time(0.0);
	    for(j=0;j<N;j++){
	        c_dgemv('N',N,N,1.0,A,N,&B[j*N],1,0.0,&D[j*N],1);
	    }
	    T1    = T1+get_time(t1);

	}
	
	for(int iter=0;iter<no_iteration;iter++){

	    t2    = get_time(0.0);
	    #pragma omp parallel for
	    for(j=0;j<N;j++){
	        c_dgemv('N',N,N,1.0,A,N,&B[j*N],1,0.0,&E[j*N],1);
	    }
	    T2    = T2+get_time(t2);
	    
	}

	cout<<"Time: "<<T0/no_iteration<<" "<<T1/no_iteration<<" "<<T2/no_iteration<<endl;
	
	delete[] A;
	delete[] B;
	delete[] C;
	delete[] D;
	delete[] E;
    }

    return 0;
}

/************************************************************************************************/
