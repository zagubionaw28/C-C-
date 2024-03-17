/*
Program that generate two vectors (1 and 2)  of random ints in [0,9] and performs vector3[i]=min{vector1[i],vector2[i]}.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "getmem.h"
#include "argshand.h"
#include "utils.h"
#include <pthread.h>

#define PRINT 0
#define DEBUG 0

typedef struct drand48_data DrandData;

typedef struct Min2VectorInt_args
{
   long StartingRow, EndingRow;
   int * pVector1, * pVector2, * pVector3;
   int ThreadId;
} Min2VectorInt_args;


/*---------------------------------------------------------------------------*/
void ParametersError()
{
 puts("Options are:");
 puts("\t[ -h To show this help ]");
 puts("\t  -r <n rows>			");
 exit(0);
}

/*---------------------------------------------------------------------------*/
//Init values of two vectors of size Rows.
void * Init2VectorInt(void * pTh_Args)
{ 
 Min2VectorInt_args * pMyData;
 pMyData = (Min2VectorInt_args *) pTh_Args;
 DrandData RandData;
 long rand1, rand2;

 srand48_r(pMyData->ThreadId, &RandData);

 for (long i = pMyData -> StartingRow ; i < pMyData -> EndingRow; i++)
     {
      lrand48_r(&RandData, &rand1);
      lrand48_r(&RandData, &rand2);
      pMyData -> pVector1[i]= rand1 % 10;
      pMyData -> pVector2[i]= rand2 % 10;
     }

 pthread_exit(NULL);
}


/*---------------------------------------------------------------------------*/
//Min{Vector1,Vector2}->Vector3
void * Min2VectorInt(void * pTh_Args)
{
   Min2VectorInt_args * pMyData;
   pMyData = (Min2VectorInt_args *) pTh_Args;

   for (long i = pMyData -> StartingRow; i < pMyData -> EndingRow; i++) {
      pMyData -> pVector3[i]=(pMyData -> pVector1[i]<pMyData -> pVector2[i])?pMyData -> pVector1[i]:pMyData -> pVector2[i];
   }

   pthread_exit(NULL);
}


/*---------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
 long Rows, remainingRows;
 int NThreads, *vectorStart, *vectorEnd;
 int * pVector1, * pVector2, * pVector3;
 pthread_t	*pThreads=NULL;
 Min2VectorInt_args *pTh_Args=NULL;

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

 #if (PRINT==1)
   printf("Rows=%ld.\n", Rows);
 #endif


 // START PTH-VERSION
 printf("Thread number: %d\n\n", NThreads);


 pThreads = (pthread_t *) GetMem(NThreads, sizeof(pthread_t), 
                                 "Main: pThreads");
 //Get mem for args to threads.
 pTh_Args = (Min2VectorInt_args *) GetMem(NThreads, 
                                           sizeof(Min2VectorInt_args),
                                           "Main: ppTh_Args");

 pVector1  = (int *) GetMem(Rows,sizeof(int),"Main:Vector1");
 pVector2  = (int *) GetMem(Rows,sizeof(int),"Main:Vector2");
 pVector3  = (int *) GetMem(Rows,sizeof(int),"Main:Vector3");

 vectorStart  = (int *) GetMem(NThreads,sizeof(int),"Main:vectorStart");
 vectorEnd  = (int *) GetMem(NThreads,sizeof(int),"Main:vectorEnd");
 

 remainingRows = Rows;
 for (int t = 0; t < NThreads; t++) {
   if (t == 0) {
      vectorStart[t] = 0;
      vectorEnd[t] = Rows / NThreads;
   }
   else {
      vectorStart[t] = vectorEnd[t - 1];
      vectorEnd[t] = vectorStart[t] + Rows / NThreads;
   }
   if (remainingRows % NThreads != 0) {
      vectorEnd[t]++;
      remainingRows--;
   }
 }

 for (int t = 0; t < NThreads; t++) {
   pTh_Args[t].StartingRow = vectorStart[t];
   pTh_Args[t].EndingRow = vectorEnd[t];
   pTh_Args[t].pVector1 = pVector1;
   pTh_Args[t].pVector2 = pVector2;
   pTh_Args[t].pVector3 = pVector3;
   pTh_Args[t].ThreadId = t;
   pthread_create(&pThreads[t], NULL, Init2VectorInt, (void *) &pTh_Args[t]);
   
   printf("Task number %d have rows to do from %ld to %ld\n", t, pTh_Args[t].StartingRow, pTh_Args[t].EndingRow);
 }

 for (int t = 0; t < NThreads; t++) {
   pthread_create(&pThreads[t], NULL, Min2VectorInt, (void *) &pTh_Args[t]);
 }

 for (int t = 0; t < NThreads; t++) {
   pthread_join(pThreads[t], NULL);
 }

 if (PRINT == 1) {
   printf("\nvector 1: ");
   for (int i = 0; i < Rows; i++) printf("%d, ", pVector1[i]);
   printf("\n");

   printf("vector 2: ");
   for (int i = 0; i < Rows; i++) printf("%d, ", pVector2[i]);
   printf("\n");
   
   printf("vector 3: ");
   for (int i = 0; i < Rows; i++) {
      printf("%d, ", pVector3[i]);
   }
 }

 #if (DEBUG==1)
 struct timeval tv1,tv2,tv3,tv4; struct timezone tz;
 gettimeofday(&tv1, &tz);
 #endif

 #if (DEBUG==1)
 gettimeofday(&tv2, &tz);
 #endif
 
 #if (DEBUG==1)
 gettimeofday(&tv3, &tz);
 #endif
  
 #if (DEBUG==1)
 gettimeofday(&tv4, &tz);
 double TInitV = (tv2.tv_sec- tv1.tv_sec) + (tv2.tv_usec-tv1.tv_usec)*1e-6;
 printf("Time to initialize the vector         = %12.4g sec\n", TInitV);
 double TSumV =  (tv4.tv_sec- tv3.tv_sec) + (tv4.tv_usec-tv3.tv_usec)*1e-6;
 printf("Time to add the vector's elements     = %12.4g sec\n", TSumV);
 printf("Time to initialize and add the vector = %12.4g sec\n", 
         TInitV+TSumV);
 #endif

 pthread_exit(NULL);
 
 free(pVector1);
 free(pVector2);
 free(pVector3);
 free(vectorStart);
 free(vectorEnd);
 free(pThreads);
 free(pTh_Args);
 return 0;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
