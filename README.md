```C

                             _____ _             ____  _          _ _ 
                            |_   _(_)_ __  _   _/ ___|| |__   ___| | |
                              | | | | '_ \| | | \___ \| '_ \ / _ \ | |
                              | | | | | | | |_| |___) | | | |  __/ | |
                              |_| |_|_| |_|\__, |____/|_| |_|\___|_|_|
                                           |___/

                               --a minimalist shell made from scratch--

```

**TinyShell** is a base repo created due to my interest for OS-development under linux env. I recently switched onto a linux distro & after making some researchs on OS-dev projects ideas, minishell always came on top as a good beginner project for discovering linux internals and i never took the time to create one so let's go...

>[!Important]
>This repo contains samples I wroted. It may not be perfect so don't blame me if you see potentials errors.

>[!Warning]
>I had habit to use C under windows env so don't blame me if you see Windows synthax haha.

## Core features 

🟢 **Command lexing & parsing** : using lexer synhtax interpretation + quote handling + AST implementation for commands parsing.

🟢 **Signals interruptions handling** : handling interruptions

🟢 **Builtin functions** : base builtins functions `exit, echo, clear, history, pwd`

🟢 **Working on custom core functions** like `ls, cat, mkdir` etc for bringing more fun instead of calling execvp => creating my own programs.

🔴 **Command execution** : main core command execution

🔴 **Handling more options** : >>, <<, &&

🔴 **Handling env :** Handling environment variables


<br>

## Running tinyshell 

`make && ./tinyshell`

<br>

## Links & ressources

<a href="https://github.com/zwan074/technical-books/blob/master/Advanced.Programming.in.the.UNIX.Environment.3rd.Edition.0321637739.pdf" target="_blank">Advanced programming in the unix environment</a>

<a href="https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218" target="_blank">ManBell 42 minishell project</a>

<a href="https://medium.com/basecs/leveling-up-ones-parsing-game-with-asts-d7a6fc2400ff" target="_blank">AST Algorithm</a>
