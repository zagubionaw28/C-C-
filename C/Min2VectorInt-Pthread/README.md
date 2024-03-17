# Exam OpenMP and PThreads.

# To be filled in by the student/group
 * Name and surname of student  : 
 * Group of activities          :

## Architecture:
 * Microprocessor:
 * Number of cores:
 * Number of threads per core:
 * Has hyperthreading (SMT) enabled in BIOS:
 * HDD/SSD:
 * RAM:
 * Virtual machine is used:
    - Number of cores:
    - RAM:
    - HDD capacity:

## Instructions:
 * In the attached sequential version. Sequential times of the sequential code parts that can be parallelized and the T.Cspar can be obtained with DEGUG=1.
   * The student must develop the OpenMP and PThread versions.
   * Both must be pass. OMP is 30% and PTh is 70% of the grade.
   * The program parameters are found in Run.sh, but the number of iterations must be established so that the sequential lasts at least a few seconds.
   * Memory is allocated dynamically by the routines in getmem.h.
   * Input parameters are obtained by routines in arghand.h.
   * Vectors and matrices are printed by the routines in utils.h.
   * The initialization of the random data array(s) and the operation on the array(s) can be parallelized.
   * It is mandatory to parallelize at least the operation on the array(s). Higher mark is obtained if the random initialization of the array(s) is also parallelized.
   * For the random initialization of the array(s), lrand48\_r() (integers) or drand48\_r() (double) will be used for parallel versions if that routine is parallelized. The pseudorandom sequence seed of each thread is initialized to the thread identifier. If the random initialization of the array(s) is not parallelized, lrand48() will be used and the seed of the pseudorandom sequence will be 0.
   * **Both vector are initialized in the same routine** to have them different. In the routine the seed is set first.
   * Run.sh must be completed for serial and parallel execution.
   * Use a small iteration size to ensure that it initializes well and operation are correct.
   * When measuring times of the entire program, you must compile without -g or -pg and the PRINT and DEBUG variables must be 0.


- - - 
# Delivery

## Theoretical speed-up of the sequential algorithm.

1. **What number of rows (-r) has been chosen so that the sequential program lasts at least a few seconds?**
 * The selected value must be used in all tables.  50000000

2. **For the sequential program provided, fill out one of the following tables.**
 * You can use the Speed-up.ods spreadsheet to perform calculations.

**If only the operation is parallelized**

| Execution   |     Rows       | 
| ----------- | -------------- |
|T.Sec.       |  0.846      |
|T.Oper.      | 0.1602      | 
|T.CsPar      | 0.1602      |
|SpA(2)       | 1.10458284371328 |
|SpA(4)       | 1.16553006819591  |

**If the initialization of the array(s) and the operation are parallelized**

| Execution   |     Rows       |
| ----------- | -------------- |
|T.Sec        |   0.846        |
|T.Init.      |  0.6547     |
|T.Oper.      |   0.1602      | 
|T.CsPar      |  0.8149     |
|SpA(2)       | 1.92908448295519   |
|SpA(4)       | 3.60268284893005  |

where:
* T.Sec: The wall-clock time (total time) of the sequential program. Real part of the `$time <program>...`
* T.Init.: The time to initialize the vector.
* T.Oper.: The time to do the opration.
* T.CsPar: The time of the sequential code that will be parallelized.
* SpA(p): The **theoretical** spedd-up according to Amhdal's law for **p** parallel threads.

- - -
## Results of the parallel algorithm with OpenMP

3. **What part(s) have you parallelized from the sequential version?**  

4. **Fill in the following table for the parallel execution carried out in OpenMP.**
 * You can use the Speed-up.ods spreadsheet to perform calculations.
  * Remember that it is not necessary to measure times within the parallel program.

| Execution   |      Rows      | 
| ----------- | -------------- |
|T(1)         |                |
|T(2)         |                |
|T(4)         |                |
|Sp(1)		  |                |
|Sp(2)		  |                |
|Sp(4)        |                |

Where
* T(p): The total time (real part of the output `$ time < program > ...`) of the parallel algorithm with **p** threads.
* Sp(p): Real speed-up with **p** parallel threads.

- - -
## Results of parallel algorithm with PThreads

5. **What part(s) have you parallelized from the sequential version?** inicizalization and operations

6. **Fill in the following table for the parallel execution carried out in Pthreads.**
 * You can use the Speed-up.ods spreadsheet to perform calculations.

| Execution   |     Rows       | 
| ----------- | -------------- |
|T(1)         |  0.649    |
|T(2)         | 0.739      |
|T(4)         | 1.401  |
|Sp(1)		  |  1.14479025   |
|Sp(2)		  | 1.14479025710419  |
|Sp(4)        | 0.603854389721627  |

Where
* T(p): The total time (real part of the output `$ time < program > ...`) of the parallel algorithm with **p** threads.
* Sp(p): Real speed-up with **p** parallel threads.

7. **Have yuu do a $ make clean and remove all unnecesary files?**

- - -

&copy; [Leocadio González Casado](https://sites.google.com/ual.es/leo). Dpto, Informática, UAL.
