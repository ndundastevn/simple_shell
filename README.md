## Simple Shell OS

This is a project for the creation of a simple Unix shell using C language. It is meant to replicate the basic functionalities of the Bourne shell (sh). 

The shell supports the execution of basic commands such as ls, echo, pwd, cat, and more. It also includes the implementation of custom built-in commands like cd, exit, env, setenv, and unsetenv.

### Requirements

* Ubuntu 20.04 LTS
* GCC version 4.8.4

### Usage

To compile the shell, run the following command:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

To launch the shell in interactive mode, simply run the compiled file:

```
./hsh
```

To run the shell in non-interactive mode, you can use the following syntax:

```
echo "ls -l" | ./hsh
```

### Built-in Commands

* `cd`: change current working directory
* `exit`: exit the shell
* `env`: display the current environment variables
* `setenv`: initialize a new environment variable, or modify an existing one
* `unsetenv`: remove an environment variable

### Example Usage

```
$ ./hsh
$ ls -la
total 40
drwxrwxr-x 3 vagrant vagrant  4096 Apr 14 20:05 .
drwxr-xr-x 5 vagrant vagrant  4096 Apr 14 19:51 ..
-rw-rw-r-- 1 vagrant vagrant   235 Apr 14 20:04 AUTHORS
-rw-rw-r-- 1 vagrant vagrant   249 Apr 14 20:05 shell.c
-rwxrwxr-x 1 vagrant vagrant 13048 Apr 14 20:05 hsh
$ cd ..
$ pwd
/home/vagrant/simple_shell
$ exit
$
```

### Files

* 1-main.c: main function, signal handling and helper functions
*
*
* shell.h: header file containing function prototypes, struct definitions and macros

### Authors

* Erick Buka (erickobuka@gmail.com)
* Ndunda Stephen (ndundastevn@gmail.com)
