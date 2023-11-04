#!/bin/bash

echo "Error word tests"
echo
../tokenizer 'echo "hello"world"'
echo
../tokenizer 'echo "hello\\\"'
echo
../tokenizer 'echo \\x'