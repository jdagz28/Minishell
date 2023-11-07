#!/bin/bash

echo "Testing error operators"
echo
../tokenizer "cat ||"
echo
../tokenizer "cat &&"
echo
../tokenizer "cat ;"
echo
../tokenizer "cat |"
echo
../tokenizer "cat && >"
echo
../tokenizer "cat | ||"
echo
../tokenizer "cat ||||"
echo
../tokenizer "cat | ;"
echo
../tokenizer "cat || &&"
echo
../tokenizer "cat || |"
echo
../tokenizer "cat && ;"
