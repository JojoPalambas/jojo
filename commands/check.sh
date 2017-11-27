#!/bin/bash

green="\e[0;32m"
red="\e[0;31m"
white="\e[0;37m"

touch output

function check_rootfiles
{
    filecount=$(ls -l | wc -l)
    filecount=$(($filecount - 2))

    if [ $filecount -lt $1 ]; then
        echo -e "- ${red}Too few files in the root${white}"
    elif [ $filecount -gt $1 ]; then
        echo -e "- ${red}Too many files in the root${white}"
    else
        echo -e "- ${green}Right number of files in the root${white}"
    fi   
}

function check_exist
{
    for arg in $*; do
        if [ -e $arg ]; then
            echo -e "- ${green}$arg exists${white}"
        else
            echo -e "- ${red}$arg does not exist${white}"
        fi
    done
}

function check_log
{
    goal=$(($1 * 20))
    lognum=$(git log --oneline | wc -l)

    if [ $lognum -lt $goal ]; then
        echo -e "- ${red}$lognum / $goal commits detected${white}"
    else
        echo -e "- ${green}$lognum / $goal commits detected${white}"
    fi
}

function check_unwanted
{
    touch temp
    for ext in $*; do
        find -name "*$ext" > temp
        if [ -z $(cat temp) ]; then
            echo -e "- ${green}No $ext file detected${white}"
        else
            echo -e "- ${red}$(cat temp | wc -l) $ext file(s) detected:${white}"
            for line in $(cat temp); do
                echo -e "-> ${red}$line${white}"
            done
        fi
    done
    rm temp
}

function check_80cols
{
    for file in $*; do
        if [ $file = "output" ]; then
            continue
        fi
        if [ -d $file ]; then
            check_80cols $file/*
        else
            IFS=$'\n'
            grep -E -n .{80}.+ $file > output
            if [ $(cat output | wc -w) = 0 ]; then
                echo -e "- ${green}No line exceeding 80 cols in $file${white}"
            else
                echo -e "- ${red}80+ cols in $file:${white}"
                for line in $(cat output); do
                    echo -e "--> ${red}$line${white}"
                done
            fi
            IFS=$' \t\n'
        fi
    done
}

function check_trailing_whitespaces
{
    for file in $*; do
        if [ $file = "output" ]; then
            continue
        fi
        if [ -d $file ]; then
            check_trailing_whitespaces $file/*
        else
            IFS=$'\n'
            grep -E -n "[[:space:]]$" $file > output
            if [ $(cat output | wc -w) = 0 ]; then
                echo -e "- ${green}No trailing whitespace in $file${white}"
            else
                echo -e "- ${red}Trailing whitespace or tab in $file:${white}"
                for line in $(cat output); do
                    echo -e "--> ${red}$line${white}"
                done
            fi
            IFS=$' \t\n'
        fi
    done
}

function check_tabs
{
    echo -e "${red}Not implemented ${green}yet${white}"
}

function check_indent
{
    echo -e "${red}Not implemented ${green}yet${white}"
}

echo
echo "----- Beginning of the file tree check -----"
echo

echo "--- Checking submission tree structure"
check_rootfiles 6
check_exist AUTHORS README TODO tests src Makefile
echo

echo "--- Checking git sanity"
check_log 2
echo

echo "--- Checking unwanted files"
check_unwanted .o .swp
echo

echo "--- Checking coding style"
check_80cols *
check_trailing_whitespaces *
check_indent *
echo

echo "-------- End of the file tree check --------"
echo

rm output
