#!/bin/bash

make Min2VectorInt

echo "-----------------------------------------"
echo "Min2VectorInt sequential : TEST"
echo "-----------------------------------------"
time ./Min2VectorInt -r 10

echo "-----------------------------------------"
echo "Min2VectorInt sequential : 50KK"
echo "-----------------------------------------"
time ./Min2VectorInt -r 50000000


echo "-----------------------------------------"
echo "Min2VectorInt Pthread : 50KK"
echo "-----------------------------------------"
time ./Min2VectorInt-PTH -nt 1 -r 50000000

echo "-----------------------------------------"
echo "Min2VectorInt Pthread : 50KK"
echo "-----------------------------------------"
time ./Min2VectorInt-PTH -nt 2 -r 50000000


echo "-----------------------------------------"
echo "Min2VectorInt Pthread TEST"
echo "-----------------------------------------"
time ./Min2VectorInt-PTH -nt 4 -r 16

echo "-----------------------------------------"
echo "Min2VectorInt Pthread : 50KK"
echo "-----------------------------------------"
time ./Min2VectorInt-PTH -nt 4 -r 50000000


# echo "-----------------------------------------"
# echo "Min2VectorInt Pthread-part version TEST"
# echo "-----------------------------------------"
# time ./MIn2VectorInt-PTH-part -nt 4 -r 16

# echo "-----------------------------------------"
# echo "Min2VectorInt Pthread-part version : 50KK"
# echo "-----------------------------------------"
# time ./MIn2VectorInt-PTH-part -nt 4 -r 50000000


