#!/bin/bash

make Product3Vectors


echo "-----------------------------------------"
echo "Min2VectorInt Pthread TEST"
echo "-----------------------------------------"
time mpirun -np 4 ./Product3Vectors-MPI -r 10

echo "-----------------------------------------"
echo "Min2VectorInt Pthread : 50KK"
echo "-----------------------------------------"
time mpirun -np 1 ./Product3Vectors-MPI -r 50000000

echo "-----------------------------------------"
echo "Min2VectorInt Pthread : 50KK"
echo "-----------------------------------------"
time mpirun -np 2 ./Product3Vectors-MPI -r 50000000

echo "-----------------------------------------"
echo "Min2VectorInt Pthread : 50KK"
echo "-----------------------------------------"
time mpirun -np 4 ./Product3Vectors-MPI -r 50000000




