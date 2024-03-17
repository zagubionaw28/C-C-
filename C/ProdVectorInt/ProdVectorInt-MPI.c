/*
Program returns the product of the elements of a vector of ints
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <mpi.h>
#include "getmem.h"
#include "argshand.h"
#include "utils.h"

#define DEBUG 0
#define PRINT 0

/*---------------------------------------------------------------------------*/
void ParametersError()
{
	puts("Options are:");
	puts("\t[ -h To show this help ]");
	puts("\t  -r <n rows>			");
	exit(0);
}

/*---------------------------------------------------------------------------*/
// Init values of a vector of size Rows.
void InitVectorInt(int *pVector, const int Rows)
{
	for (int i = 0; i < Rows; i++) {
		pVector[i] = lrand48() % 10 + 1;
	}
}

/*---------------------------------------------------------------------------*/
// Print a vector of size Rows
void PrintVectorInt(int *pVector, const int Rows, char *String)
{
	printf("%s -----------------------------------------\n", String);
	for (int i = 0; i < Rows; i++)
		printf("%2d,", pVector[i]);
	puts("");
}

/*---------------------------------------------------------------------------*/
// Product of elements of a vector
void ProdVectorInt(int *pVector, const int Rows, int *Prod)
{
	int LocalProd = 1;
	for (int i = 0; i < Rows; i++)
		LocalProd *= pVector[i];
	*Prod = LocalProd;
}

/*---------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
	int Rows;
	int Prod = 1;
	// MPI
	int *subVector, *subVectorSize, *subProd;
	int NTasks, myRank;
	int restRows;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &NTasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);


	if (myRank == 0) {
		if (ExistArg("-h", argc, argv))
			ParametersError();

		if (!ExistArg("-r", argc, argv))
		{
			fputs("Parameter -r is necessary.\n", stderr);
			ParametersError();
		}
		else
		{
			Rows = atoi(GetArg("-r", argc, argv));
			if (Rows < 1)
			{
				puts("Rows<1");
				exit(1);
			}
		}
	}

	srand48(time(NULL) + myRank);

	MPI_Bcast(&Rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	subProd = (int *) GetMem(NTasks,sizeof(int),"Main:Vector");
	subVectorSize =  (int *)GetMem(NTasks,sizeof(int),"All tasks:pSizeSubV");

	restRows = Rows % NTasks; 
	for (int i = 0; i < NTasks; i++) 	
	{		
		subVectorSize[i] = Rows/NTasks;
		if (restRows > 0) 
			{
			subVectorSize[i]++;
			restRows--;
			}
		subProd[i] = 1;
	}

#if (DEBUG == 1)
	struct timeval tv1, tv2, tv3, tv4;
	struct timezone tz;
	gettimeofday(&tv1, &tz);
#endif
	// Init values of Vector
	subVector = (int *) GetMem(subVectorSize[myRank],sizeof(int),"Main:Vector");
	InitVectorInt(subVector, subVectorSize[myRank]);

#if (DEBUG == 1)
	gettimeofday(&tv2, &tz);
#endif

#if (PRINT == 1)
	PrintVectorInt(subVector, Rows, "Vevtor1");
#endif

#if (DEBUG == 1)
	gettimeofday(&tv3, &tz);
#endif

	ProdVectorInt(subVector, subVectorSize[myRank], &subProd[myRank]);
	if (PRINT == 1) {
		printf("Product of %d process = %d\n", myRank, subProd[myRank]);
	}
	MPI_Reduce(&subProd[myRank], &Prod, 1,
			MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
	if (myRank == 0 && PRINT == 1) {
		printf("\nfinal prod: %d", Prod);
	}

#if (DEBUG == 1)
	gettimeofday(&tv4, &tz);
	double TInitV = (tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec) * 1e-6;
	printf("A = Time to initialize the vector         = %12.4g sec\n", TInitV);
	double TSumV = (tv4.tv_sec - tv3.tv_sec) + (tv4.tv_usec - tv3.tv_usec) * 1e-6;
	printf("B = Time to do the operation in the vector= %12.4g sec\n", TSumV);
	printf("A+B                                       = %12.4g sec\n",
		   TInitV + TSumV);
#endif

#if (PRINT == 1)
	printf("Prod=%d.\n", Prod);
#endif

	free(subVector);
	free(subVectorSize);
	free(subProd);
	MPI_Finalize();
	return 0;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
