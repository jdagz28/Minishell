#!/bin/bash

echo "Testing invalid input"
echo
../parser "cat < >"
echo
../parser "cat ! >>>>"
echo
../parser "cat > @"
echo
../parser "cat # > a"