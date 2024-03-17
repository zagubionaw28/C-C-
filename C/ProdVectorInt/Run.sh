#!/bin/bash

make all

echo "-----------------------------------------"
echo "ProdVectorInt sequrential"
echo "-----------------------------------------"
time ./ProdVectorInt -r 10

echo "-----------------------------------------"
echo "ProdVectorInt sequrential 50KK"
echo "-----------------------------------------"
time ./ProdVectorInt -r 5000000000

echo "-----------------------------------------"
echo "ProdVectorInt MPI"
echo "-----------------------------------------"
time mpirun -np 4 ./ProdVectorInt-MPI -r 10

echo "-----------------------------------------"
echo "ProdVectorInt MPI 50KK"
echo "-----------------------------------------"
time mpirun -np 1 ./ProdVectorInt-MPI -r 5000000000

echo "-----------------------------------------"
echo "ProdVectorInt MPI 50KK"
echo "-----------------------------------------"
time mpirun -np 2 ./ProdVectorInt-MPI -r 5000000000

echo "-----------------------------------------"
echo "ProdVectorInt MPI 50KK"
echo "-----------------------------------------"
time mpirun -np 4 ./ProdVectorInt-MPI -r 5000000000
