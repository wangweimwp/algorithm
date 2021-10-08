#!/bin/sh

CROSS_COMPILE=arm-fullhanv3-linux-uclibcgnueabi
SRC=src/*.c
INC=inc/

$CROSS_COMPILE-gcc -o hellow_world hellow_world.c $SRC -I $INC
