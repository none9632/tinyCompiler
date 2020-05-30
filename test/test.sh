#!/bin/bash

program_path=../tinyCompiler
red="\033[38;2;255;0;0m"
green="\033[38;2;0;255;0m"
results=0

function test
{
    $program_path "$1"
    nasm -f elf64 output.asm
    gcc -no-pie output.o
    output=$(./a.out)

    if [ "$output" = "$2" ]
    then
        echo -e " <$green OK \e[0m>       $1 $output"
    else
        results=1
        echo -e " <$red ERROR \e[0m>    $1 $output"
    fi
}

echo "--------------------------------------------------------------------"
echo " Start program testing"
echo "--------------------------------------------------------------------"

if [ -e $program_path ]
then
    test "0" "0"
    test "1+1" "2"
    test "1+(2*3)" "7"
    test "2*3+4" "10"
    test "2*3+4*5" "26"
    test "50/10" "5"
    test "3/2" "1"
    test "6*3/2" "9"
    test "(2+3)*(4+5)" "45"
    test "1+2+3+4+5+6+7+8+9+10+11+12+13+14+15+16+17" "153"
    test "12*(32)" "384"
    test "12 * (   32   )" "384"
    test "1+2*4+3*3" "18"
    test "1*3*1*4+2*4+3*3" "29"
else
    results=1
    echo ""
    echo "    $program_path: No such file"
    echo ""
fi

echo "--------------------------------------------------------------------"

if [ $results -eq 1 ]
then
    echo -e " results:$red fail\e[0m"
else
    echo -e " results:$green success\e[0m"
fi

echo "--------------------------------------------------------------------"
