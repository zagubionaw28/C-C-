#!/bin/bash

export Rows=500000000

make all

echo "-----------------------------------------"
echo "Add2VectorInt sequential"
echo "-----------------------------------------"
time ./Sub3Vectors -r $Rows


echo "-----------------------------------------"
echo "-----------------------------------------"
echo "-----------------------------------------"

echo "-----------------------------------------"
echo "Sub3Vectors MPI 1 Init in parallel"
echo "-----------------------------------------"
time mpirun -np 1 ./Sub3Vectors-MPI -r $Rows

echo "-----------------------------------------"
echo "Sub3Vectors MPI 2 Init in parallel"
echo "-----------------------------------------"
time mpirun -np 2 ./Sub3Vectors-MPI -r $Rows

echo "-----------------------------------------"
echo "Sub3Vectors MPI 4 Init in parallel"
echo "-----------------------------------------"
time mpirun -np 4 ./Sub3Vectors-MPI -r $Rows

echo "-----------------------------------------"
echo "Sub3Vectors-PTh -r $Rows 1"
echo "-----------------------------------------"
time ./Sub3Vectors-Pthread -r $Rows -nt 1

echo "-----------------------------------------"
echo "Sub3Vectors-PTh -r $Rows 2"
echo "-----------------------------------------"
time ./Sub3Vectors-Pthread -r $Rows -nt 2

echo "-----------------------------------------"
echo "Sub3Vectors-PTh -r $Rows 4"
echo "-----------------------------------------"
time ./Sub3Vectors-Pthread -r $Rows -nt 4
