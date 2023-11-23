#!/bin/bash

test()
{
    GREEN='\033[0;32m'
    RED='\033[0;31m'
    RESET='\033[0m'

    TEST_TYPE=$1
    TEST_NUMBER=$2
    TEST_COMMAND=$3

    if [ "$TEST_TYPE" != "$CURRENT_TEST_TYPE" ]; then
        echo -e "\n${TEST_TYPE}"
        CURRENT_TEST_TYPE=$TEST_TYPE
    fi

    printf '  Test %-2s: %-50s' "$TEST_NUMBER" "\"$TEST_COMMAND\""

    # Run in bash
    { echo -n -e "$TEST_COMMAND" | bash; } >bash_out 2>&1
    bash=$?

    # Run in minishell
    { echo -n -e "$TEST_COMMAND" | ../minishell 2> ms_out; } > /dev/null
    minishell=$?

    diff bash_out ms_out >> result
    if [ $? -eq 0 ]; then
        echo -e "${GREEN} OKAY${RESET}"
    else
        echo -e "${RED}\toutput diferent${RESET}"
        echo -e "\tbash output:"
        cat bash_out
        echo -e "\tminishell output:"
        cat ms_out
    fi

    if [ "$bash" -eq "$minishell" ]; then
        echo -e "${GREEN} exit code OK${RESET}"
    else
        echo -e "${RED}\texit code diferent${RESET}"
        echo -e "${RED}\t\tbash exit value: $bash${RESET}"
        echo -e "${RED}\t\tminishell exit value: $minishell${RESET}"
    fi
}

#Invalid Input
test 'Invalid Input' 1 'cat < >'
test 'Invalid Input' 2 'cat ! >>>>>'
test 'Invalid Input' 3 'cat > >'
test 'Invalid Input' 4 'cat @ >'
test 'Invalid Input' 5 'cat # > a'