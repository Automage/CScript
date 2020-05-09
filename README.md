# CScript

An interpreter for 'C scripts' which can be executed directly in your shell.

## Installation

Clone the repository and run the Makefile. Move the `cs` executable to your bin if you wish.

## Usage

C scripts are designed to be similar in use to bash scripts, with the exception of using the C programming language. The syntax of these scripts have been modified from standard C syntax to best serve their purpose of creating quick and concise tools, while being fimiliar enough such that there is no extra overhead in getting accustomed to writing them. 

The anatomy of a C script is as follows:

```
#!<path-to-cs-exec>
<includes>
<definitions>
<main code>
<functions>
```

Notice how there is no need for a main function declaration, only the code within. To provide further flexibilty and reduce the number of brain cycles spent on complying to C standards, the interpreter is also able to execute scripts where any of mentioned components of the script are meshed. For example, the following format would still be recognized:

```
#!<path-to-cs-exec>
<functions>
<includes>
<main code>
<definitions>
<more functions>
<more main code>
```

Note that if function A calls function B, function B should be placed before function A.  

By including a shebang at the top of the script and ensuring executable permissions, the C script may be executed just as you would execute a bash script. An example script can be found [here](script_test).
