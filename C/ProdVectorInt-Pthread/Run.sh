#!/bin/bash

make all

echo "-----------------------------------------"
echo "ProdVectorInt sequrential"
echo "-----------------------------------------"
time ./ProdVectorInt -r 10

echo "-----------------------------------------"
echo "ProdVectorInt PTH"
echo "-----------------------------------------"
time ./ProdVectorInt-PTH -nt 4 -r 10

