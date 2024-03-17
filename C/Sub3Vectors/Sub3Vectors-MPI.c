/*
Progam that generate two vectors (1 and 2) of random ints in [0,9] and
performs Vector4[i]=Vector1[i]-Vector2[i]-Vector3[i]
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "getmem.h"
#include "argshand.h"
#include "utils.h"
#include <mpi.h>

#define DEBUG 0
#define PRINT 1

/*---------------------------------------------------------------------------*/
void ParametersError()
{
 puts("Options are:");
 puts("\t[ -h To show this help ]");
 puts("\t  -r <n rows>			");
 exit(0);
}

/*---------------------------------------------------------------------------*/
//Init values of a vector of size Rows.
void InitVectorInt(int *pVector, const int Rows)
{ 
 for (int i=0;i<Rows;i++)
     pVector[i]=lrand48()%10;
}

/*---------------------------------------------------------------------------*/
//Print a vector of size Rows
void PrintVectorInt(int *pVector, const int Rows, char * String)
{
 printf("%s -----------------------------------------\n", String);
 for (int i=0;i<Rows;i++)
     printf("%2d,", pVector[i]);
 puts("");
}

/*---------------------------------------------------------------------------*/
//Sub Vector1 and Vector2 and Vector3 in Vector4
void Add2VectorInt(int *pVector1, int *pVector2, int * pVector3, int * pVector4,
                   const int Rows)
{
 for (int i=0;i<Rows;i++)
     pVector4[i]=pVector1[i]-pVector2[i]-pVector3[i];
}

/*---------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
 int Rows;
 int * pVector4   =NULL;
 int * pSubVector1=NULL, * pSubVector2=NULL, * pSubVector3=NULL, * pSubVector4=NULL;
 int NTasks, MyRank; 	//MPI number of task and Rank for current task.
 int *pPosSubV;			//Vector with position each task starts in Vectors.
 int *pSizeSubV;			//Vector with size of subvector.
 int Rem; 				//Remainder
 int AddPos;			//Adding positions.

 //MPI Initialization
 MPI_Init(&argc,&argv);
 MPI_Comm_size(MPI_COMM_WORLD, &NTasks);
 MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);

 if (MyRank==0)	//Task 0--
    {
	 if (ExistArg("-h",argc,argv))
		ParametersError();  

	 if (!ExistArg("-r",argc,argv))
		{
		fputs("Parameter -r is necessary.\n",stderr);
		ParametersError();
		}
	 else
		{
		 Rows = atoi(GetArg("-r",argc,argv));
		 if (Rows <1)
		    {
		     puts("Rows<1");
		     exit(1);
		    }
		} 

	 printf("Rows=%d.\n", Rows);

	 pVector4  = (int *) GetMem(Rows,sizeof(int),"Main:Vector4");

	}

 //All tasks 
 MPI_Bcast(&Rows,1,MPI_INT,0,MPI_COMM_WORLD);
  //Get men and initialize DisplacV and pSizeSubV
 pPosSubV = (int *)GetMem(NTasks,sizeof(int),"All tasks:DisplacV");
 pSizeSubV = (int *)GetMem(NTasks,sizeof(int),"All tasks:pSizeSubV");
 
  Rem=Rows%NTasks; 
 AddPos=0;
 for (int i=0; i<NTasks; i++) 
     {
      pSizeSubV[i] = Rows/NTasks;
      if (Rem > 0) 
         {
          pSizeSubV[i]++;
          Rem--;
         }

     pPosSubV[i] = AddPos;
     AddPos += pSizeSubV[i];
    }
    
 #if (PRINT==1)
 printf("Task %d out of %d, responsible elements: [%d,%d].\n",
      MyRank,NTasks,pPosSubV[MyRank],pPosSubV[MyRank]+pSizeSubV[MyRank]-1);
 #endif
 
 pSubVector1  = (int *) GetMem(pSizeSubV[MyRank],sizeof(int),
                               "SubVector1");
 pSubVector2  = (int *) GetMem(pSizeSubV[MyRank],sizeof(int),
                               "SubVector2");
 pSubVector3  = (int *) GetMem(pSizeSubV[MyRank],sizeof(int),
                               "SubVector3");
 pSubVector4  = (int *) GetMem(pSizeSubV[MyRank],sizeof(int),
                               "SubVector4");
 srand48(MyRank);
 
  //All Init values of SubVector1 and 2
 InitVectorInt (pSubVector1,pSizeSubV[MyRank]);
 InitVectorInt (pSubVector2,pSizeSubV[MyRank]);
 InitVectorInt (pSubVector3,pSizeSubV[MyRank]);
 
 #if (PRINT==1)
 printf("Task %d init vectors:\n", MyRank);
 PrintVectorInt(pSubVector1,pSizeSubV[MyRank],"SubVector1:");
 PrintVectorInt(pSubVector2,pSizeSubV[MyRank],"SubVector2:");
 PrintVectorInt(pSubVector3,pSizeSubV[MyRank],"SubVector3:");
 #endif
 
  //Perform the partial component wise minus
 for (int i=0;i<pSizeSubV[MyRank];i++)
     pSubVector4[i]=pSubVector1[i]-pSubVector2[i]-pSubVector3[i];

 MPI_Gatherv(pSubVector4, pSizeSubV[MyRank], MPI_INT,
             pVector4, pSizeSubV, pPosSubV, 
             MPI_INT,0, MPI_COMM_WORLD);

 free((void *)pSizeSubV);
 free((void *)pPosSubV);
 free((void *)pSubVector4);
 free((void *)pSubVector3);
 free((void *)pSubVector2);
 free((void *)pSubVector1);

 if (MyRank==0)
    {
     #if (PRINT==1)
     PrintVectorInt(pVector4,Rows,"Vector4");
     #endif
     free((void *)pVector4);
    }


 MPI_Finalize();
 return 0;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
