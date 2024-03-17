/*
Program that generate three vectors (1 and 2 and 3)  of random ints in [0,9] and performs vector3[i]=min{vector1[i],vector2[i]}.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <mpi.h>
#include "getmem.h"
#include "argshand.h"
#include "utils.h"

#define PRINT 0
#define DEBUG 0

/*---------------------------------------------------------------------------*/
void ParametersError()
{
	puts("Options are:");
	puts("\t[ -h To show this help ]");
	puts("\t  -r <n rows>			");
	exit(0);
}

/*---------------------------------------------------------------------------*/
// Init values of two vectors of size Rows.
void Init3VectorInt(int *pVector1, int *pVector2, int *pVector3, const int Rows)
{
	for (int i = 0; i < Rows; i++)
	{
		pVector1[i] = lrand48() % 10;
		pVector2[i] = lrand48() % 10;
		pVector3[i] = lrand48() % 10;
	}
}

/*---------------------------------------------------------------------------*/
// Min{Vector1,Vector2}->Vector3
void Prod3VectorInt(int *pVector1, int *pVector2, int *pVector3, int *pVector4,
				   const int Rows)
{
	for (int i = 0; i < Rows; i++)
		pVector4[i] = (pVector1[i] * pVector2[i] * pVector3[i]);
}

/*---------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
	int Rows;
	int *subVector1, *subVector2, *subVector3, *subVector4;
	int *pVector4;
	int NTasks, myRank;
	int *subVectorSize;
	int restRows;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &NTasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

	subVectorSize =  (int *)GetMem(NTasks,sizeof(int),"All tasks:pSizeSubV");

	if (myRank == 0)
	{
		if (ExistArg("-h", argc, argv))
			ParametersError();

		if (!ExistArg("-r", argc, argv))
		{
			fputs("Parameter -r is neccesary.\n", stderr);
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
		#if (PRINT == 1)
				printf("Rows=%d.\n", Rows);
		#endif

	}
	pVector4 = (int *) GetMem(Rows, sizeof(int),"Main:Vector3");

	// ---- MAIN MPI -----
	MPI_Bcast(&Rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
	// printf("Hello from %d with Rows: %d\n", myRank, Rows);
	
	restRows = Rows % NTasks; 
	for (int i = 0; i < NTasks; i++) 	
	{		
		subVectorSize[i] = Rows/NTasks;
		if (restRows > 0) 
			{
			subVectorSize[i]++;
			restRows--;
			}
	}


	// :: INIT 1, 2 VECTOR ::
	#if (DEBUG == 1)
		struct timeval tv1, tv2, tv3, tv4;
		struct timezone tz;
		gettimeofday(&tv1, &tz);
	#endif

	srand48(0 + myRank);

	subVector1 = (int *) GetMem(subVectorSize[myRank],sizeof(int),"Main:Vector1");
	subVector2 = (int *) GetMem(subVectorSize[myRank],sizeof(int),"Main:Vector2");
	subVector3 = (int *) GetMem(subVectorSize[myRank],sizeof(int),"Main:Vector3");
	subVector4 = (int *) GetMem(subVectorSize[myRank],sizeof(int),"Main:Vector4");

	Init3VectorInt(subVector1, subVector2, subVector3, subVectorSize[myRank]);

	if (PRINT==1) {
		printf("my rank: %d\n", myRank);
		PrintVInt(stdout, subVector1, subVectorSize[myRank]);
		PrintVInt(stdout, subVector2, subVectorSize[myRank]);
		PrintVInt(stdout, subVector3, subVectorSize[myRank]);
	}


	#if (DEBUG == 1)
		gettimeofday(&tv2, &tz);
	#endif

	#if (DEBUG == 1)
		gettimeofday(&tv3, &tz);
	#endif

	// :: MIN OPERATION ::

	Prod3VectorInt(subVector1, subVector2, subVector3, subVector4, subVectorSize[myRank]);

	MPI_Gather(subVector4, subVectorSize[myRank], MPI_INT, 
				pVector4, subVectorSize[myRank], MPI_INT, 0,
	 			MPI_COMM_WORLD);



	#if (DEBUG == 1)
		gettimeofday(&tv4, &tz);
		double TInitV = (tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec) * 1e-6;
		printf("Time to initialize the vector         = %12.4g sec\n", TInitV);
		double TSumV = (tv4.tv_sec - tv3.tv_sec) + (tv4.tv_usec - tv3.tv_usec) * 1e-6;
		printf("Time to add the vector's elements     = %12.4g sec\n", TSumV);
		printf("Time to initialize and add the vector = %12.4g sec\n",
			TInitV + TSumV);
	#endif

	if (myRank == 0 && PRINT==1) {
		PrintVInt(stdout, pVector4, Rows);
	}

	MPI_Finalize();
	return 0;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
