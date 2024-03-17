# Training exam: MPI. 

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
 * The sequential version is attached where with DEGUG=1 the sequential times of the serial code parts that will be parallelized can be obtained.
 * The student must complete the MPÎ version.
 * Program parameters are found in Run.sh.
 * Memory is allocated dynamically by the routines in getmem.h.
 * Input parameters are obtained by routines in arghand.h.
 * Vectors and matrices are printed by the routines in utils.h.
 * It is mandatory to parallelize at least the sum. Vector initialization can be optionally parallelized.
 * More mark is obtained if collective communications are made and if they are IN_PLACE
 * Run.sh is now prepared for the execution of the serial and parallel programs.
 * Use a small vector to see that it initializes well and adds well.
 * When measuring times of the entire program, you must compile without -g or -pg and the PRINT and DEBUG variables must be 0.

- - -

# Entrega

## Speed-up teórico del algoritmo secuencial.

# Delivery

## Theoretical speed-up of the sequential algorithm.

1. **For the provided sequential program, fill out the following tables..**
 * You can use the Speed-up.ods spreadsheet to perform calculations.
 * If the size of vector -r 1e-9 takes too long, you can choose a value that makes the sequential version last at least seconds.
 * This value must be used in all tables.


**If it is parallelized only in sum** 

| Execución   | -r 500000000  | 
| ----------- | -------------- |
|T.Sec        |  8.492         |
|T.Add.       |  1.614         | 
|T.CsPar      |  1.614         |
|SpA(2)       |1.10500975927131|
|SpA(4)       | 1.166243219116 |

**If the initialization of the vector and the sum are parallelized** 

| Execución   | -r 500000000  | 
| ----------- | -------------- |
|T.Sec        |  8.492         |
|T.Inic.      |  6.652         |
|T.Add.       |  1.614         | 
|T.CsPar      |  8.265         |
|SpA(2)       |1.94792980846427|
|SpA(4)       |3.7030415349395 |

where:
* T.Sec: The wall-clock time (total time) of the sequential program. Real part of the `$time <program>...`
* T.Init.: The time to initialize the vector.
* T.Add: The time to add the vector.
* T.CsPar: The time of the sequential code that will be parallelized.
* SpA(p): The **theoretical** spedd-up according to Amhdal's law for **p** parallel threads.


## Results of the parallel algorithm with MPI

2. **What part(s) have you parallelized from the sequential version?** Only sum;

3. **Have you used collectives?** Yes;

4. **¿Have you used IN_PLACE?** No;

5. ****Fill in the following table for the parallel execution carried out in MPI.**
* You can use the Speed-up.ods spreadsheet to perform calculations.

| Execución   | -r 500000000  | 
| ----------- | -------------- |
|T(1)         |   18.667       |
|T(2)         |   33.735       |
|T(4)         |   21.371      |
|Sp(1)		  | 0.454920447849146    |
|Sp(2)		  | 0.251726693345191 |
|Sp(4)        | 0.39736090964391   |

Where
* T(p): The total time (real part of the output `$ time < program > ...`) of the parallel algorithm with **p** tasks.
* Sp(p): Real speed-up with **p** parallel tasks.


- - -

&copy; [Leocadio González Casado](https://sites.google.com/ual.es/leo). Dpto, Informática, UAL.
