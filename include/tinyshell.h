#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#define ANSI_COLOR_RED     "\x1b[91m"  // bright red
#define ANSI_COLOR_GREEN   "\x1b[92m"  // bright green
#define ANSI_COLOR_YELLOW  "\x1b[93m"  // bright yellow
#define ANSI_COLOR_BLUE    "\x1b[94m"  // bright blue
#define ANSI_COLOR_MAGENTA "\x1b[95m"  // bright magenta
#define ANSI_COLOR_CYAN    "\x1b[96m"  // bright cyan
#define ANSI_COLOR_RESET   "\x1b[0m"

//input.c
int start_shell();