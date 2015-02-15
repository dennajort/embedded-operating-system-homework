#!/bin/sh

sudo insmod mystat.ko && cat /proc/mystat && sudo rmmod mystat
