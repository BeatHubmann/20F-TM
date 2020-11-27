#include <mpi.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits>
#include "cublas_v2.h"
#include "cuda.h"
#include "Blas.H"
#include "Utilities.H"
using namespace std;

extern "C" {
  cudaError_t cudaSetDevice(int device);
  cudaError_t cudaMalloc(void** devPtr,size_t size);
  cudaError_t cudaFree(void* devPtr);
  cudaError_t cudaMemcpy(void* dst,const void* src,size_t count,\
			 cudaMemcpyKind kind);
  cublasStatus_t cublasCreate(cublasHandle_t *handle);
  cublasStatus_t cublasDestroy(cublasHandle_t handle);
  cublasStatus_t cublasDgemm(cublasHandle_t handle,cublasOperation_t transa,\
			     cublasOperation_t transb,int m,int n,int k,\
			     const double *alpha,const double *A,int lda,\
			     const double *B,int ldb,const double *beta,\
			     double *C, int ldc);
}

int main(int argc, char *argv[])
{
    cublasHandle_t handle;
    double t0,T0,t1,T1;
    double *A,*B,*C,*D;
    double *A_dev,*B_dev,*C_dev;
    double alpha = 1.0;
    double beta  = 0.0;
    int i,j,N,IT;
    int no_iteration;

    no_iteration = 10;

    cudaSetDevice(0);

    cublasCreate(&handle);

    for(IT=1;IT<argc;IT++){
    
        N  = atoi(argv[IT]);

	A  = new double[N*N];
	B  = new double[N*N];
	C  = new double[N*N];
	D  = new double[N*N];

	for(i=0;i<N;i++){
	    for(j=0;j<N;j++){
	        A[i+j*N] = (randn(),randn());
		B[i+j*N] = (randn(),randn());
	    }
	}
	
	cudaMalloc((void**)&A_dev,N*N*sizeof(double));
	cudaMalloc((void**)&B_dev,N*N*sizeof(double));
	cudaMalloc((void**)&C_dev,N*N*sizeof(double));

	cudaMemcpy(A_dev,A,N*N*sizeof(double),cudaMemcpyHostToDevice);
	cudaMemcpy(B_dev,B,N*N*sizeof(double),cudaMemcpyHostToDevice);

	T0 = 0.0;
	T1 = 0.0;
	
	for(int iter=0;iter<no_iteration;iter++){
	  
	  t0 = get_time(0.0);
	  c_dgemm('N','N',N,N,N,1.0,A,N,B,N,0.0,D,N);
	  T0 = T0+get_time(t0);

	  t1 = get_time(0.0);
	  cublasDgemm(handle,CUBLAS_OP_N,CUBLAS_OP_N,N,N,N,&alpha,A_dev,N,\
		      B_dev,N,&beta,C_dev,N);
	  cudaMemcpy(C,C_dev,N*N*sizeof(double),cudaMemcpyDeviceToHost);
	  T1 = T1+get_time(t1);
	}

	cudaFree(A_dev);
	cudaFree(B_dev);
	cudaFree(C_dev);

	cout<<"Time: "<<T0/no_iteration<<" "<<T1/no_iteration<<endl;

	delete[] A;
	delete[] B;
	delete[] C;
	delete[] D;
    }
    
    cublasDestroy(handle);
    
    return 0;
}

/************************************************************************************************/
