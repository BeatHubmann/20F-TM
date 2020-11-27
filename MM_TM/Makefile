include ./make.inc

DEBUG       =     

INCLUDEDIR  = $(INCCUD) 
LIBS	    = $(LAPACK) $(LINKS) -fopenmp $(MPI) $(F90_LIBS)

CC_FILES    = GreenSolver.o Utilities.o

OMP_code: GreenSolver_openmp.o Utilities.o
	$(LOADER) GreenSolver_openmp.o Utilities.o $(LOADFLAGS) $(LIBS) -lm -o $@$

MPI_code: GreenSolver_mpi.o Utilities.o
	$(LOADER) GreenSolver_mpi.o Utilities.o $(LOADFLAGS) $(LIBS) -lm -o $@$

CUDA_code: GreenSolver_cuda.o Utilities.o
	$(LOADER) GreenSolver_cuda.o Utilities.o $(LOADFLAGS) $(LIBS) $(CUDA) -lm -o $@$

.C.o:
	$(MPICXX) -c $< $(CXXFLAGS) $(DEBUG) -fopenmp $(OMEN_FLAGS) $(INCLUDEDIR)

clean:	
	rm -f *.o *.c *.h *_code
