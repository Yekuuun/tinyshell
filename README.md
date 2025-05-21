```C

                             _____ _             ____  _          _ _ 
                            |_   _(_)_ __  _   _/ ___|| |__   ___| | |
                              | | | | '_ \| | | \___ \| '_ \ / _ \ | |
                              | | | | | | | |_| |___) | | | |  __/ | |
                              |_| |_|_| |_|\__, |____/|_| |_|\___|_|_|
                                           |___/

                               --a minimalist shell made from scratch--

```

**TinyShell** is a minimal & custom-built Unix shell written in pure C. It represent my first "unix" project after switching from Windows dev. It supports essential shell functionnalities with builtin commands & custom binaries.

>[!Important]
>This repo contains samples I wroted. It may not be perfect so don't blame me if you see potentials errors.

>[!Warning]
>I had habit to use C under windows env so don't blame me if you see Windows synthax haha.

## ✨ Core features 

🟢 **Command lexing & parsing** : using lexer synhtax interpretation + quote handling + AST implementation for commands parsing.

🟢 **Signals interruptions handling** : handling interruptions like CTRL-c etc.

🟢 **Builtin functions** : base builtins functions `exit, echo, clear, history, pwd`

🟢 **Working on custom core functions** like `ls, cat, mkdir` etc for bringing more fun instead of calling execvp => creating my own programs.

🟢 **Command execution** : main core command execution using native programs. (i tried to upgrade the experience using my custom binaries in `/bin`)

🔴 **Handling more options** : >>, <<, &&

🔴 **Root detection** : detects if current user is in root mode

🔴 **Handling env** : Handling environment variables

🔴 **Auto-completion** : adding auto-completion with tab


<br>

## ▶️ Running tinyshell 

`make && ./tinyshell`

<br>

## Links & ressources

<a href="https://github.com/zwan074/technical-books/blob/master/Advanced.Programming.in.the.UNIX.Environment.3rd.Edition.0321637739.pdf" target="_blank">Advanced programming in the unix environment</a>

<a href="https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218" target="_blank">ManBell 42 minishell project</a>

<a href="https://medium.com/basecs/leveling-up-ones-parsing-game-with-asts-d7a6fc2400ff" target="_blank">AST Algorithm</a>
