# Minishell

In this project, we aim to create a custom shell, akin to the Bourne Again Shell (bash), adhering to specific guidelines that limit its functionality. The key capabilities required for this Minishell include:

### Required capabilities

- **Working History:** Implement a functional command history.
- **Quotes Handling:** Manage both single (**`‘ ’`**) and double quotes (**`“ ”`**).
- **Redirections:** Support file input/output redirections (**`<`**, **`>`**, **`<<`**, **`>>`**).
- **Pipes:** Enable the use of pipes (**`|`**) for command chaining.
- **Environment Variables:** Include functionality for handling environment variables.
- **Exit Status:** Check and display the exit status of the last command using **`$?`**.
- **Signal Handling:** Mimic bash behavior for signals. In interactive mode:
    - Ctrl-C: displays a new prompt on a new line
    - Ctrl-D: exits the shell
    - Ctrl-\: does nothing
- **Builtins:** Implement a set of built-in commands.
    - **`echo`** with the **`n`** option.
    - **`cd`** accepting only relative or absolute paths.
    - **`pwd`** (no options) - to display the current working directory.
    - **`export`** (no options) - to set environment variables.
    - **`unset`** (no options) - to remove environment variables.
    - **`env`** (no options) - to display the current environment.
    - **`exit`** (no options) - to terminate the shell.

### General loop of a shell

The shell's fundamental logic consists of three steps:

1. **Read:**
    - Utilize the **`readline()`** function to read commands from the standard input.
2. **Parse:**
    - Separate (tokenization) the input command string into a program and its arguments.
3. **Execute:**
    - Run the parsed command, executing the specified program with the provided arguments.

By adhering to these steps, Minishell can effectively process user commands, offering a streamlined and functional shell experience.

---

## Tokenization

Tokenization is a critical process in parsing a command string, involving the identification and categorization of different elements. he primary goal is to inspect the command string, allocate suitable tokens from a predefined list, and systematically store them in a linked list.Here are the key aspects of the tokenization process:

### **Tokenization Process**

1. **Check and Tag:**
    - Iterate through the command string, checking for the presence of each token type.
    - Whitespaces are skipped during the process
    - Assign the appropriate token to each identified element in the command.
2. **Linked List Storage:**
    - Store the identified tokens in a linked list for efficient organization and retrieval.
3. **End-of-File Token:**
    - Once the entire command string is processed (reaching **`\0`**), append a **`TK_EOF`** token with a `NULL` word to facilitate easy identification of the end of the command later on.
4. ******************************Preliminary Syntax Check:******************************
    - Initial syntax validation to identify potential errors based on the grammar

### **Token Types**

The tokens are categorized into distinct types, each represented by the **`t_tk_kind`** enumeration:

```c
typedef enum e_tk_kind
{
    TK_WORD,         // Represents a general word in the command.
    TK_PIPE,         // Indicates the presence of a pipe (|) in the command.
    TK_OR,           // Represents the logical OR operator.
    TK_AND,          // Represents the logical AND operator.
    TK_SEMICOLON,    // Represents a semicolon (;) in the command.
    TK_OP_PAREN,     // Represents the opening parenthesis (.
    TK_CL_PAREN,     // Represents the closing parenthesis ).
    TK_OPERATOR,     // Denotes "\n"
    TK_REDIRECT,     // Indicates a redirection operator (<, >, <<, >>).
    TK_EOF           // Signifies the end of the command string with a NULL word.
} t_tk_kind;
```

### Our Grammar

An overview of the expected sequence of tokens in a valid syntax.

```
commandline              ::= list
                         |   list ";"
        
list                    ::= conditional
                         |   list ";" conditional
        
conditional             ::= pipeline
                         |   conditional "&&" pipeline
                         |   conditional "||" pipeline
        
pipeline                ::= command
                         |   pipeline "|" command
        
command                 ::= word
                         |   redirection
                         |   command word
                         |   command redirection
                         |   quoted_command
                         |   parenthesized_command

redirection             ::= redirectionop filename

redirectionop           ::= "<"  |  ">"  |  "<2" | "2>"

quoted_command          ::= single_quoted_sequence
                         |   double_quoted_sequence

single_quoted_sequence  ::= "'" quoted_content "'"
double_quoted_sequence  ::= '"' quoted_content '"'

parenthesized_command   ::= "(" list ")"
```

**Syntax Rules:**

- A **`list`** comprises a series of **`conditionals`**, connected by **`;`** or **`&`**.
- A **`conditional`** comprises a series of **`pipelines`**, linked by **`&&`** or **`||`**.
- A **`pipeline`** comprises a series of **`commands`**, linked by **`|`**.
- A **`redirection`** is one of **`<`**, **`>`**, **`<2`** followed by **`EOF`** identifier, or **`2>`**, followed by a **`filename`**.
- A **`quoted_command`** is a command enclosed in either single (**`'`**) or double (**`"`**) quotes.

In general, a command is a series of words representing the program name and its arguments, interspersed with redirection commands.

---

## Parsing
