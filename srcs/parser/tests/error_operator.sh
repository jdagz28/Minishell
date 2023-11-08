#!/bin/bash

echo "Testing error operators"
echo
../parser "cat ||"
echo
../parser "cat &&"
echo
../parser "cat ;"
echo
../parser "cat |"
echo
../parser "cat && >"
echo
../parser "cat | ||"
echo
../parser "cat ||||"
echo
../parser "cat | ;"
echo
../parser "cat || &&"
echo
../parser "cat || |"
echo
../parser "cat && ;"
