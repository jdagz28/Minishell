#!/usr/bin/expect -f

# Set variables
set minishell "./minishell"
set infile "test_cmd"
set outfile "output_file"

# Check if output_file exists and remove it
if {[file exists $outfile]} {
    file delete $outfile
}

# Open input file for reading
set fp [open $infile r]

# Spawn minishell
spawn $minishell
sleep 1

# Log all output to a file
log_file -a $outfile

# Wait for minishell prompt
expect "minishell> "

# Read and execute commands line by line
while {[gets $fp cmd] != -1} {
    send -- "$cmd\r"
    expect "minishell> "
}

# Send EOF (Ctrl+D) to indicate the end of commands
send -- "\004"

# Close the input file
close $fp

# Wait for minishell to finish
expect eof
