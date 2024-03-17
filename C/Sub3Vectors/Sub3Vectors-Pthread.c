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
#include <pthread.h>

#define DEBUG 1
#define PRINT 1

//To avoid repeating struct drand48_data.
typedef struct drand48_data StDrand48Data;

//I'll use the same structure to init and to sum the vector.
typedef struct th_args
{
 int *		pVector1;
 int *		pVector2;
 int *		pVector3;
 int *		pVector4;
 int 		Rows;
 int		rows_start;
 int 		n_sub_rows;
 int		Div;
 int 		ThreadId;
} Type_Th_Args;

/*---------------------------------------------------------------------------*/
void ParametersError()
{
 puts("Options are:");
 puts("\t[ -h To show this help ]");
 puts("\t  -r <n rows>			");
 exit(0);
}
//-----------------------------------------------------------------------------
void HowtoShareVector(int ThisTh, int NTh, int NRows, int *start, int *n)
{
 int n_sub_rows= NRows/NTh;			//How many sub rows.
 int n_larger_threads= NRows%NTh;	//Threads with more rows
 int row_start;						//In which row a thread starts.

 if (ThisTh < n_larger_threads)
    { 
     n_sub_rows = n_sub_rows + 1;
     row_start = 0 + ThisTh * n_sub_rows;
    }  
 else 
    if (n_sub_rows > 0)
       row_start = n_larger_threads + ThisTh * n_sub_rows;
  else 
     { // this process has only zero elements
      row_start = -1;
      n_sub_rows  =  0;
     }

 *n		= n_sub_rows;
 *start	= row_start;
}
/*---------------------------------------------------------------------------*/
//Init values of a vector of size Rows.
void * InitVectorInt(void * pTh_Args)
{ 
 Type_Th_Args * pMyData;
 pMyData=(Type_Th_Args *) pTh_Args;
 
 int rows_start, rows_end;
 int * pVector1;
 int * pVector2;
 int * pVector3;
 StDrand48Data RandData;
 long RandNumber1, RandNumber2, RandNumber3;
 
 srand48_r(pMyData->ThreadId,&RandData);
 
 pVector1	= pMyData->pVector1;
 pVector2	= pMyData->pVector2;
 pVector3	= pMyData->pVector3;
 rows_start	= pMyData->rows_start;
 rows_end	= pMyData->rows_start + pMyData->n_sub_rows;

 for (int i=rows_start; i<rows_end; i++)
	 {
	  lrand48_r(&RandData,&RandNumber1);
	  lrand48_r(&RandData,&RandNumber2);
	  lrand48_r(&RandData,&RandNumber3);
	  pVector1[i]=RandNumber1%100;
	  pVector2[i]=RandNumber2%100;
	  pVector3[i]=RandNumber3%100;
	 }
	 
   pthread_exit(NULL);
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
void * Sub3VectorInt(void * pTh_Args)
{
  Type_Th_Args * pMyData;
  pMyData=(Type_Th_Args *) pTh_Args;
  
   // const int dato;
 int rows_start, rows_end;
 int * pVector1, * pVector2, * pVector3, * pVector4;
 
 pVector1	= pMyData->pVector1;
 pVector2	= pMyData->pVector2;
 pVector3	= pMyData->pVector3;
 pVector4       = pMyData->pVector4;
 rows_start	= pMyData->rows_start;
 rows_end	= pMyData->rows_start + pMyData->n_sub_rows;
 
 for (int i=rows_start; i<rows_end; i++)
     pVector4[i]=pVector1[i]-pVector2[i]-pVector3[i];
     
  pthread_exit(NULL);
}

/*---------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
 int Rows;
 int * pVector1, * pVector2, * pVector3, *pVector4;
 int NThreads; 					//Number of threads.
 pthread_t	*pThreads=NULL; 	//Vector of threads. Dynamic memory. - środowisko pThreadów
 //Vector of structs with data to threads. Dynamic memory allocation.
 Type_Th_Args *pTh_Args=NULL;
 int rows_start,n_sub_rows; 	//Thread start at and how many.

 if (ExistArg("-h",argc,argv))
    ParametersError();  

 if (!ExistArg("-r",argc,argv))
    {
    fputs("Parameter -r is neccesary.\n",stderr);
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
    
   if (!ExistArg("-nt",argc,argv))
    {
    fputs("Parameter -nt is neccesary.\n",stderr);
    ParametersError();
    }
 else
    {
     NThreads = atoi(GetArg("-nt",argc,argv)); 
     if (NThreads <=0 )
        {
         puts("NThreads must be > 0 and <= Rows/3.");
         exit(1);
        }
    } 

 printf("Rows=%d.\n", Rows);

 //Init seed of random number generator
 srand48(time(NULL));

 //Calloc de Getmen put data to zeroes
 pVector1  = (int *) GetMem(Rows,sizeof(int),"Main:Vector1");
 pVector2  = (int *) GetMem(Rows,sizeof(int),"Main:Vector2");
 pVector3  = (int *) GetMem(Rows,sizeof(int),"Main:Vector3");
 pVector4  = (int *) GetMem(Rows,sizeof(int),"Main:Vector3");
 
   //Get mem for threads
 pThreads = (pthread_t *)    GetMem(NThreads, sizeof(pthread_t), 
                                    "Main: pThreads");
 pTh_Args = (Type_Th_Args *) GetMem(NThreads, sizeof(Type_Th_Args),
                                    "Main: pTh_Data");
 
  //==========================================================================
 //InitVector in parallel.
   for (int t=0; t<NThreads; t++) 
     {
 	  HowtoShareVector(t,NThreads, Rows, &rows_start, &n_sub_rows);
 	  pTh_Args[t].Rows			= Rows;
 	  pTh_Args[t].rows_start	= rows_start;
 	  pTh_Args[t].n_sub_rows	= n_sub_rows;
 	  pTh_Args[t].ThreadId		= t;
 	  pTh_Args[t].pVector1 = pVector1;
          pTh_Args[t].pVector2 = pVector2;
          pTh_Args[t].pVector3 = pVector3;
          pTh_Args[t].pVector4 = pVector4;

      //By default threads are joinable.
      pthread_create(&pThreads[t],NULL, InitVectorInt,(void *)&pTh_Args[t]);
     }
     
      //Do the threads join
 for (int t=0;t<NThreads; t++)
     {
      pthread_join(pThreads[t], NULL);
     }
//===========================================================================

 //Sum the vector in parallel.

  for (int t=0; t<NThreads; t++) 
     {

         pthread_create(&pThreads[t],NULL, Sub3VectorInt, (void *)&pTh_Args[t]);
     }
     
 //PrintVInt(stdout,pVector1,Rows);
// PrintVInt(stdout,pVector2,Rows);
 //PrintVInt(stdout,pVector3,Rows);

      //Do the threads join
 for (int t=0;t<NThreads; t++)
     {
      pthread_join(pThreads[t], NULL);
     }
// ===============================================================

//PrintVInt(stdout,pVector4,Rows);

 pthread_exit(NULL);
 
 free((void *)pVector4);
 free((void *)pVector3);
 free((void *)pVector2);
 free((void *)pVector1);

 return 0;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
