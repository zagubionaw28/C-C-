# Exam MPI.

# To be filled in by the student/group
 * Name and surname of student  : Artur Jakubowski
 * Group of activities          :

## Architecture:
 * Microprocessor: Intel(R) Core(TM) i5-7400 CPU @ 3.00GHz
 * Number of cores: 4
 * Number of threads per core: 1
 * Has hyperthreading (SMT) enabled in BIOS: No
 * HDD/SSD:
 * RAM: 8GB
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

1. **What number of rows (-r) has been chosen so that the sequential program lasts at least a few seconds?**
 * The selected value must be used in all tables.
 ```
 500000000
 ```

2. **For the sequential program provided, fill out one of the following tables.**
 * You can use the Speed-up.ods spreadsheet to perform calculations.

**If only the operation is parallelized**

| Execution   |     Rows       | 
| ----------- | -------------- |
|T.Sec.       |    5.711       |
|T.Oper.      |    1.194       | 
|T.CsPar      |    1.194       |
|SpA(2)       |1.1167383652718 |
|SpA(4)       |1.18596199771571|

**If the initialization of the array(s) and the operation are parallelized**

| Execution   |     Rows       |
| ----------- | -------------- |
|T.Sec        |    5.711       |
|T.Init.      |    4.397       |
|T.Oper.      |    1.194       | 
|T.CsPar      |    5.592       |
|SpA(2)       |  1.95917667238422|
|SpA(4)       |  3.76466710613052|

where:
* T.Sec: The wall-clock time (total time) of the sequential program. Real part of the `$time <program>...`
* T.Init.: The time to initialize the vector.
* T.Oper.: The time to do the operation.
* T.CsPar: The time of the sequential code that will be parallelized.
* SpA(p): The **theoretical** spedd-up according to Amhdal's law for **p** parallel processes.

## Results of the parallel algorithm with MPI

3. **What part(s) have you parallelized from the sequential version?**
```
Initialization and operation
```

4. **Have you used collectives?**
```
Yes
```

5. **Have you used IN_PLACE?**
```
No
```

6. **Fill in the following table for the parallel execution carried out in MPI.**
 * You can use the Speed-up.ods spreadsheet to perform calculations.
 * Remember that it is not necessary to measure times within the parallel program.

| Execution   |      Rows      | 
| ----------- | -------------- |
|T(1)         |      6.089     |
|T(2)         |      3.323     |
|T(4)         |      1.949     |
|Sp(1)        |0.93792084086056|
|Sp(2)        |1.71862774601264|
|Sp(4)        |2.93022062596203|

Where
* T(p): The total time (real part of the output `$ time < program > ...`) of the parallel algorithm with **p** processes.
* Sp(p): Real speed-up with **p** parallel processes.

7. **Have yuu do a $ make clean and remove all unnecesary files?**

- - -

&copy; [Leocadio González Casado](https://sites.google.com/ual.es/leo). Dpto, Informática, UAL.
