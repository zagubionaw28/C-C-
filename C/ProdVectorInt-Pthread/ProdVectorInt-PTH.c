/*
Program returns the product of the elements of a vector of ints
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "getmem.h"
#include "argshand.h"
#include "utils.h"
#include <pthread.h>

#define DEBUG 0
#define PRINT 0

typedef struct drand48_data DrandData;

typedef struct ProdVectorInt_args
{
   long StartingRow, EndingRow;
   int * pVector;
   long * globalProduct;
   pthread_mutex_t mutex;
   int ThreadId;
} ProdVectorInt_args;

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
void * InitVectorInt(void * pTh_Args)
{ 
 ProdVectorInt_args * pMyData;
 pMyData = (ProdVectorInt_args *) pTh_Args;
 DrandData RandData;
 long rand1;

 for (long i = pMyData -> StartingRow; i < pMyData -> EndingRow; i++){
   lrand48_r(&RandData, &rand1);
   pMyData -> pVector[i] = lrand48() % 10 + 1;
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
//Product of elements of a vector
void * ProdVectorInt(void * pTh_Args)
{
 ProdVectorInt_args * pMyData;
 pMyData = (ProdVectorInt_args *) pTh_Args;

 long localProd = 1;
 for (long i = pMyData -> StartingRow; i < pMyData -> EndingRow; i++) 
     localProd *= pMyData -> pVector[i];
   
 printf("Local product of task %d = %ld\n", pMyData -> ThreadId, localProd);
 pthread_mutex_lock(&(pMyData -> mutex));
 *(pMyData -> globalProduct) *= localProd;
 pthread_mutex_unlock(&(pMyData -> mutex));
 pthread_exit(NULL);
}

/*---------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
 long Rows, remainingRows;
 int NThreads, *vectorStart, *vectorEnd;
 int * pVector;
 long globalProduct = 1;
 pthread_t	*pThreads=NULL;
 ProdVectorInt_args *pTh_Args=NULL;
 pthread_mutex_t mutex;

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
   

 // START PTH-VERSION
 printf("Thread number: %d\n\n", NThreads);

 pThreads = (pthread_t *) GetMem(NThreads, sizeof(pthread_t), 
                                 "Main: pThreads");
 //Get mem for args to threads.
 pTh_Args = (ProdVectorInt_args *) GetMem(NThreads, 
                                           sizeof(ProdVectorInt_args),
                                           "Main: ppTh_Args");

 pVector = (int *) GetMem(Rows, sizeof(int), "Main: pVector");

 pthread_mutex_init(&mutex, NULL);

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
 
 
 #if (DEBUG==1)
 struct timeval tv1,tv2,tv3,tv4; struct timezone tz;
 gettimeofday(&tv1, &tz);
 #endif
 
for (int t = 0; t < NThreads; t++) {
   pTh_Args[t].StartingRow = vectorStart[t];
   pTh_Args[t].EndingRow = vectorEnd[t];
   pTh_Args[t].pVector = pVector;
   pTh_Args[t].globalProduct = &globalProduct;
   pTh_Args[t].mutex = mutex;
   pTh_Args[t].ThreadId = t;
   pthread_create(&pThreads[t], NULL, InitVectorInt, (void *) &pTh_Args[t]);
   
   printf("Task number %d have rows to do from %ld to %ld\n", t, pTh_Args[t].StartingRow, pTh_Args[t].EndingRow);
 }

 #if (DEBUG==1)
 gettimeofday(&tv2, &tz);
 #endif

 #if (PRINT==1)
 PrintVectorInt(pVector,Rows,"Vevtor1");
 #endif
 
 #if (DEBUG==1)
 gettimeofday(&tv3, &tz);
 #endif
 
 for (int t = 0; t < NThreads; t++) {
   pthread_create(&pThreads[t], NULL, ProdVectorInt, (void *) &pTh_Args[t]);
 }

 for (int t = 0; t < NThreads; t++) {
   pthread_join(pThreads[t], NULL);
 }

 printf("final Product: %ld", globalProduct);
 
 #if (DEBUG==1)
 gettimeofday(&tv4, &tz);
 double TInitV = (tv2.tv_sec- tv1.tv_sec) + (tv2.tv_usec-tv1.tv_usec)*1e-6;
 printf("A = Time to initialize the vector         = %12.4g sec\n", TInitV);
 double TSumV =  (tv4.tv_sec- tv3.tv_sec) + (tv4.tv_usec-tv3.tv_usec)*1e-6;
 printf("B = Time to do the operation in the vector= %12.4g sec\n", TSumV);
 printf("A+B                                       = %12.4g sec\n", 
         TInitV+TSumV);
 #endif
 
 #if (PRINT==1)
 printf("Prod=%d.\n",Prod);
 #endif

 pthread_exit(NULL);
 free((void *)pVector);

 return 0;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
