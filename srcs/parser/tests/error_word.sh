#!/bin/bash

echo "Error word tests"
echo
../parser 'echo "hello"world"'
echo
../parser 'echo "hello\\\"'
echo
../parser 'echo \\x'