
#############################################################################
# Set the following options
#############################################################################

# Platform
ifeq ($(BUILD_TYPE),)
	BUILD_TYPE = ethz-gnu64
endif

#############################################################################
# Should not need to edit below, unless adding new platform
#############################################################################

# Default values which might be overridden
MAKE     = make
AR       = ar
ARFLAGS  = ruv
AR_FLAGS = ruv
RANLIB   = ranlib

# Platform/compiler specific definitions

ifeq ($(BUILD_TYPE),ethz-gnu64)
        OMEN_FLAGS    = -DAdd_ -D__MINMAX -Wno-write-strings
	GNU64	      = ./gnu64/
	MPIHOME	      = ./mpich-3.3.2/
	MKLHOME       = ./mkl/lib/intel64/
	CUDAHOME      = ./cuda/
        LOADER        = $(MPIHOME)/bin/mpic++
        MPICXX        = $(MPIHOME)/bin/mpic++
	NVCC	      = $(CUDAHOME)/bin/nvcc
        CXXFLAGS      = -g -DMPICH_IGNORE_CXX_SEEK
        LOADFLAGS     = -g -L$(GNU64)/lib64 -lgfortran
	NVCCFLAGS     = -arch=compute_60 -code=sm_60
        CUDA_SDK      = 3
        COMMONFLAGS   = -DCUDA_SDK=$(CUDA_SDK)       
 	F90_LIBS      = -L$(GNU64)/lib64 -lgfortran -Wl,-rpath,L$(GNU64)/lib64
        LAPACK        = -L$(MKLHOME) -lmkl_gf_lp64 -lmkl_sequential -lmkl_core -Wl,-rpath -Wl,$(MKLHOME)
        LINKS         = -Wl,-rpath -Wl,$(GNU64)/lib64
        OPENMP        = -fopenmp
	export LD_LIBRARY_PATH=$(GNU64)/lib64:$(INTEL64)/lib
endif

INCCUD	      = -I$(CUDAHOME)/include
CUDA          = -L$(CUDAHOME)/lib64 -lcuda -lcudart -lcublas -Wl,-rpath,$(CUDAHOME)/lib64

SMFLAG        = $(OPENMP)
