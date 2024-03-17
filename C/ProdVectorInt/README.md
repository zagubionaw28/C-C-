# Exam MPI.

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
 * The serial version is attached where with DEGUG=1 the sequential times of the serial code parts that can be parallelized can be obtained.
 * The student must complete the MPÎ version.
 * Program parameters are found in Run.sh.
 * Memory is allocated dynamically by the routines in getmem.h.
 * Input parameters are obtained by routines in arghand.h.
 * Vectors and matrices are printed by the routines in utils.h.
 * It is mandatory to parallelize at least the operation to be performed on the vector. You can optionally parallelize the vector initialization, then you get more mark.
 * A higher grade is obtained if collective communications are made and if they are IN\_PLACE.
 * Run.sh is now prepared for the execution of the serial and parallel programs.
 * Use a small vector to see that it initializes well and the operation on the vector is performed well.
 * When measuring times of the entire program, you must compile without -g or -pg and the PRINT and DEBUG variables must be 0.

- - - 
# Delivery

## Theoretical speed-up of the sequential algorithm.

1. **What number of rows (-r) has been chosen so that the sequential program lasts at least a few seconds?** 50000000
 * The selected value must be used in all tables.

2. **For the sequential program provided, fill out one of the following tables.**
 * You can use the Speed-up.ods spreadsheet to perform calculations.

**If only the operation is parallelized**

| Execution   |     Rows       | 
| ----------- | -------------- |
|T.Sec.       |                |
|T.Oper.      |                | 
|T.CsPar      |                |
|SpA(2)       |                |
|SpA(4)       |                |

**If the initialization of the array(s) and the operation are parallelized**

| Execution   |     Rows       |
| ----------- | -------------- |
|T.Sec        |                |
|T.Init.      |                |
|T.Oper.      |                | 
|T.CsPar      |                |
|SpA(2)       |                |
|SpA(4)       |                |

where:
* T.Sec: The wall-clock time (total time) of the sequential program. Real part of the `$time <program>...`
* T.Init.: The time to initialize the vector.
* T.Oper.: The time to do the operation.
* T.CsPar: The time of the sequential code that will be parallelized.
* SpA(p): The **theoretical** spedd-up according to Amhdal's law for **p** parallel processes.

## Results of the parallel algorithm with MPI

3. **What part(s) have you parallelized from the sequential version?**  INITIALIZE AND OPERATION

4. **Have you used collectives?** Yes

5. **Have you used IN_PLACE?** No

6. **Fill in the following table for the parallel execution carried out in MPI.**
 * You can use the Speed-up.ods spreadsheet to perform calculations.
 * Remember that it is not necessary to measure times within the parallel program.

| Execution   |      Rows      | 
| ----------- | -------------- |
|T(1)         |                |
|T(2)         |                |
|T(4)         |                |
|Sp(1)        |                |
|Sp(2)        |                |
|Sp(4)        |                |

Where
* T(p): The total time (real part of the output `$ time < program > ...`) of the parallel algorithm with **p** processes.
* Sp(p): Real speed-up with **p** parallel processes.

7. **Have yuu do a $ make clean and remove all unnecesary files?**

- - -

&copy; [Leocadio González Casado](https://sites.google.com/ual.es/leo). Dpto, Informática, UAL.
