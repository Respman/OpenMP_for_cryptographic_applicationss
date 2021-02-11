#! /usr/bin/env bash

g++ ./main.cpp -lcrypto -lssl -l:libcryptopp.a -fopenmp
time ./a.out
