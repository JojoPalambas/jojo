#!/bin/sh

trap "echo; echo Oh come on! Of course you can't kill me like that!" SIGINT
trap "echo; echo I am harder to kill!" SIGQUIT
trap "echo; echo Are you really"
