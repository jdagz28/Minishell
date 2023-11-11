#!/bin/bash

echo "Testing valid argument sequence"
echo
../parser "command"
echo
../parser "command arg1 arg2"
echo
../parser "command 1 | command 2"
echo
../parser "< infile command | command > outfile"
echo
../parser "command << heredoc | command > outfile"
echo
../parser "command ; command"
echo
../parser "command && command; command"
