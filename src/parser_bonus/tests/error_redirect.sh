#!/bin/bash

echo "Testing error redirects"
echo
../parser "cat < >"
echo
../parser "cat ! >>>>"
echo
../parser "cat > @"
echo
../parser "cat # > a"
echo
../parser "cat > ||"
echo
../parser "cat > &&"
echo
../parser "cat<<<"
echo
../parser "cat>>>"

