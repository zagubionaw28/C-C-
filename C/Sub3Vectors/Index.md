
Example of execution in a console per task for debugging:
```console
$ mpirun -np 4 --oversubscribe xterm -fa 'Monospace' -fs 14 -hold -e Add2VectorInt-MPI -r 10
```

## Programs: 
1. Add2VectorInt.c: Sequential program that adds two random integer vectors of equal size into another integer vector.
2. Add2VectorInt-MPI.c: The vectors are initialized by task 0 and the addition is done in parallel.
3. Add2VectorInt-MPI-InPlace.c: Same as Add2VectorInt-MPI, but task 0 does the IN_PLACE addition operations, so it does not need to get memory for the subvectors.
4. Add2VectorInt-MPI-ParInit.c: The vectors are initialized by each task and the addition is done in parallel.
5. Add2VectorInt-MPI-ParInit-InPlace.c: The vectors are initialized by each task and the addition is done in parallel, but task 0 does the addition in pVector3 IN_PLACE.

## Executions:

```console
$ time Add2VectorInt -r 500000000 
Rows=500000000.
Vectors initialization time            =         6.31 sec
Time to add the vectors                =       0.8198 sec
Time to initialize and add the vectors =         7.13 sec

real	0m7,352s
user	0m5,857s
sys	0m1,485s
```

```console
$ time mpirun -np 4 Add2VectorInt-MPI -r 500000000 
Rows=500000000.

real	0m9,314s
user	0m32,614s
sys	0m4,521s
```
**It takes longer to send and receive the vectors than to process them sequentially.**

```console
$ time mpirun -np 4 Add2VectorInt-MPI-InPlace -r 500000000 
Rows=500000000.

real	0m8,633s
user	0m30,438s
sys	0m3,993s
```

**With IN_PLACE, you save sending, but it is still slower than sequential.**

```console
$ time mpirun -np 4 Add2VectorInt-MPI-ParInit -r 500000000 
Rows=500000000.

real	0m2,945s
user	0m9,432s
sys	0m2,274s
```
**Parallelize the start of the vectors improves the time.**

```console
$ time mpirun -np 4 Add2VectorInt-MPI-ParInit-InPlace -r 500000000 
Rows=500000000.

real	0m2,648s
user	0m8,359s
sys	0m2,167s
```
**In addition, by doing it IN_PLACE we save sending.**
