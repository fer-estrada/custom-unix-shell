# small unix shell clone

super lightweight shell implementation, for practice

## features
 - prompt interface
 - builtin commands (ls, pwd, cd, echo, cat)
 - basic signal handling (Ctrl-C won't end the shell)
 - 4

## build and run
### dependencies
 - gcc
 - libreadline

```bash
make
make run
```

## notes
this is for the learning experience, so things like piping or background execution might still not be implemented, and even when they are, they might not work correctly. use this program at your own risk
