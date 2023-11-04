#!/bin/bash

echo "Testing invalid input"
echo
../tokenizer "cat < >"
echo
../tokenizer "cat ! >>>>"
echo
../tokenizer "cat > @"
echo
../tokenizer "cat # > a"