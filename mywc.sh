#!/bin/sh

wc $1 <<< $(cat $2)
