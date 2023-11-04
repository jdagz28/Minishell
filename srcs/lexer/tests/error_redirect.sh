#!/bin/bash

echo "Testing error redirects"
echo
../tokenizer "cat < >"
echo
../tokenizer "cat ! >>>>"
echo
../tokenizer "cat > @"
echo
../tokenizer "cat # > a"
echo
../tokenizer "cat > ||"
echo
../tokenizer "cat > &&"
echo
../tokenizer "cat<<<"
echo
../tokenizer "cat>>>"

