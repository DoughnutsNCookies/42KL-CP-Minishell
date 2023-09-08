# 42KL-CP-Minishell
Minishell involves building a shell in C, akin to bash.

The existence of shells is linked to the very existence of IT.

At the time, all developers agreed that communicating with a computer using aligned 1/0 switches was seriously irritating.

It was only logical that they came up with the idea of creating a software to com- municate with a computer using interactive lines of commands in a language somewhat close to the human language.

Thanks to Minishell, I've been able to travel through time and come back to problems people faced when Windows didn’t exist.


## Project Demo
![Project Demo](https://github.com/DoughnutsNCookies/42KL-CP-Minishell/blob/main/readmeAssets/Minishell-gif.gif)


## Mandatory
**General Guidelines**
- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable based on the `PATH` variable or using a relative or an absolute path.
- Not interpret unclosed quotes or special characters which are not required by the subject such as `\` or `;`.
- Handle `’` which should prevent the shell from interpreting the meta-characters in the quoted sequence.
- Handle `"` which should prevent the shell from interpreting the meta-characters in the quoted sequence except for `$`.

**Redirections**
- `<` should redirect input.
- `>` should redirect output.
- `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
- `>>` should redirect output in append mode.

**Signals**
- Handle `ctrl-C`, `ctrl-D` and `ctrl-\` which should behave like in bash.
- In interactive mode
    - `ctrl-C` displays a new prompt on a new line.
    - `ctrl-D` exits the shell.
    - `ctrl-\` does nothing.

**Builtins**
- `echo` with option -n
- `cd` with only a relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options


**Others**
- Implement `|`, the output of each command in the pipeline is connected to the input of the next command via a pipe.
- `Environment variables` which should expand to their values
- Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.


## Bonus
`&&` (AND operator):
- The `&&` operator is used to execute the command on its right only `if the command on its left succeeds` or returns an exit status of 0.
- If the command on the left fail or returns a non-zero exit status, the command on the right will not be executed.

`||` (OR operator):
- The `||` operator is used to execute the command on its right only `if the command on its left fails` or returns an exit status of 0.
- If the command on the left succeeds or returns an exit status of 0, the command on the right will not be executed.

`()` (Subshells)
- `()` can also be used to run commands in a subshell, which is a separate instance of the shell environment.
- Variables defined or modified within a subshell do not affect the parent shell.

Example of using parentheses to create a subshell:
```
(export A="hi" && echo $A) && echo $A
```

In this case, the output will be
```
hi


```
Notice that the second line is `empty`. This is due to the `export` command being ran in the subshell, so the main shell did not have the variable `A` exported.

`*` (Wildcard)
- `*` is a wildcard that matches any sequence of characters (including none) in a filename or directory path.
- It can be used in commands like `ls`, `cp`, `mv`, `rm`, and others to perform operations on multiple files or directories that match a specific pattern.
- For example, `*.txt` would match all files with a `.txt` extension


## Authors
- [@DoughnutsNCookies](https://www.github.com/DoughnutsNCookies)
- [@MTLKS](https://www.github.com/MTLKS)

