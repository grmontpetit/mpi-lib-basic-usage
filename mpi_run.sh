#!/bin/sh

mpirun --hostfile ./hostfile -np 8 ./lab01_partie1 "$1" "$2" "$3"
