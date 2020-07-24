#!/bin/bash

program_path=../tinyCompiler
red="\033[38;2;255;0;0m"
green="\033[38;2;0;255;0m"
results=0

g_start=$(date +%s%N)

function test
{
    start=$(date +%s%N)
    output=$($program_path "$1")
    dif=$(echo "scale=4;($(date +%s%N) - $start)/1000000000" | bc)

    if [ "$output" = "" ]
    then
        nasm -f elf64 output.asm
        gcc -no-pie output.o
        output=$(./a.out)
    fi

    if [ "${dif:0:1}" = "." ]
    then
        printf " 0%ss |" $dif
    else
        printf " %ss |" $dif
    fi

    if [ "$output" = "$2" ]
    then
        echo -e " -$green OK \e[0m-      $1"
    else
        results=1
        echo -e " -$red ERROR \e[0m-   $1 $output"
    fi
}

gcc_path=$(command -v gcc)
nasm_path=$(command -v nasm)

if [ "$nasm_path" = "" ]
then
    echo "error: to run this script, nasm must be installed"
    exit 0
fi
if [ "$gcc_path" = "" ]
then
    echo "error: to run this script, gcc must be installed"
    exit 0
fi

echo "--------------------------------------------------------------------"
echo " Start program testing"
echo "--------------------------------------------------------------------"

if [ -f $program_path ]
then
    test "0" "0"
    test "1+1" "2"
    test "1+(2*3)" "7"
    test "2*3+4" "10"
    test "2*3-4*5" "-14"
    test "50/10" "5"
    test "3/2" "1"
    test "1/3" "0"
    test "6-3/2" "5"
    test "(2+3)*(4-5)" "-5"
    test "1+2+3+4+5+6+7+8+9+10+11+12+13+14+15+16+17" "153"
    test "12*(32)" "384"
    test "12 * (   32   )" "384"
    test "1+2*4+3*3" "18"
    test "1*3*1*4+2*4-3*3" "11"
    test "12(32)" "error: syntax error"
    test "5++" "error: syntax error"
    test "532/" "error: syntax error"
    test "()234" "error: syntax error"
    test "word" "error: unknown character"
else
    results=1
    echo ""
    echo "    $program_path: No such file"
    echo ""
fi

echo "--------------------------------------------------------------------"

g_dif=$(echo "scale=4;($(date +%s%N) - $g_start)/1000000000" | bc)
if [ "${g_dif:0:1}" = "." ]
then
    printf " 0%ss |" $g_dif
else
    printf " %ss |" $g_dif
fi

if [ $results -eq 1 ]
then
    echo -e " results:$red fail\e[0m"
else
    echo -e " results:$green success\e[0m"
fi

echo "--------------------------------------------------------------------"

rm output.o output.asm a.out