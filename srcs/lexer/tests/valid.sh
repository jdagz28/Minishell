#!/bin/bash

echo "Testing valid argument sequence"
echo
../tokenizer "command"
echo
../tokenizer "command arg1 arg2"
echo
../tokenizer "command 1 | command 2"
echo
../tokenizer "< infile command | command > outfile"
echo
../tokenizer "command << heredoc | command > outfile"
echo
../tokenizer "command ; command"
echo
../tokenizer "command && command; command"
