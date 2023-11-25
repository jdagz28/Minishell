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
        echo -e "\n\n${TEST_TYPE}"
        CURRENT_TEST_TYPE=$TEST_TYPE
    fi

    printf '\nTest %-2s: %-50s' "$TEST_NUMBER" "\"$TEST_COMMAND\""

    if [ "$TEST_TYPE" == "Invalid Input" ]; then
        { echo -n -e "$TEST_COMMAND" | bash; } 2>&1 | head -n 1 > ./tester/bash_out 
        bash=$?

        { echo -n -e "$TEST_COMMAND" | ./minishell 2> ./tester/ms_out; echo "minishell exit $?"; } > /dev/null
        minishell=$?
    else
        { echo -n -e "$TEST_COMMAND" | bash; } > ./tester/bash_out
        bash=$?

        { echo -n -e "$TEST_COMMAND" | ./minishell > ./tester/ms_out; } > /dev/null; 
        minishell=$?
    fi

    diff -Z ./tester/bash_out ./tester/ms_out > result
    if [ $? -eq 0 ]; then
        echo -e "${GREEN} OKAY${RESET}"
    else
        echo -e "${RED}\toutput diferent${RESET}"
        echo -e "${RED}bash output:${RESET}"
        cat ./tester/bash_out
        echo -e "${GREEN}minishell output:${RESET}"
        cat ./tester/ms_out
    fi

    if [ "$bash" -eq "$minishell" ]; then
        echo -e "${GREEN}exit code OK${RESET}"
    else
        echo -e "${RED}exit code diferent${RESET}"
        echo -e "${RED}\t\tbash exit value: $bash${RESET}"
        echo -e "${RED}\t\tminishell exit value: $minishell${RESET}"
    fi

    rm result
}

#Invalid Input
test 'Invalid Input' 1 'cat < >'
test 'Invalid Input' 2 'cat ! >>>>>'
test 'Invalid Input' 3 'cat > >'
test 'Invalid Input' 4 'cat @ >'
test 'Invalid Input' 8 '< >'
test 'Invalid Input' 9 'cat >'
test 'Invalid Input' 10 'echo "hello"world"'
test 'Invalid Input' 11 '<cat><>output'
test 'Invalid Input' 12 'cat |||||||||||'
test 'Invalid Input' 13 '<cat><>output | ls | cat <<<<<<<<<<'

#Expand
test 'Expansion' 1, 'echo "$USER"'
test 'Expansion' 2, 'echo "$PWD"'
test 'Expansion' 3, 'echo "$USER" $PWD $HOME'

#Basic commands
test 'Basic Commands' 1 'ls'
test 'Basic Commands' 2 'ls -l'
test 'Basic Commands' 3 'ls -la'

#Builtins
test 'Echo Test' 1 'echo                                   hello world'
test 'Echo Test' 2 'echo                       "hello" world'
test 'Echo Test' 3 "echo                        '\$'\$'\$'\$'\$'"
test 'Echo Test' 4 'echo -n hello world'
test 'Echo Test' 5 'echo -n                    $PWD'
test 'Echo Test' 6 'echo -nnnnn $USER'
test 'Echo Test' 7 'echo                   -n             "$USER"'

test 'cd Test' 1 'cd ./src'
test 'cd Test' 2 'cd ../'
test 'cd Test' 3 'cd                                           ./src '

test 'pwd Test' 1 'echo $PWD'
test 'pwd Test' 2 '$PWD'

# test 'env Test' 1 'env'
# test 'env Test' 2 'printenv'

test 'exit Test' 1 'exit 42'
test 'exit Test' 2 'exit abc'
test 'exit Test' 3 'exit -42'
test 'exit Test' 4 'exit 2147483647'
test 'exit Test' 5 'exit -2147483648'
test 'exit Test' 6 'exit 1ab'
test 'exit Test' 7 '                 exit             42'


test 'Redirect Test' 1