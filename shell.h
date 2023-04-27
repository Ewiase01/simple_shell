#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

int is_interactive(_aww *pew);
int is_delimiter(char c, char *d);
int is_alpha(int y);
int _atoi(char *s);
#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64
#define PATH_DELIMITER ":"

int _printenv(char **env);
int env_builtin(char **args, char **env);
char *find_command(char *command);
char *build_path(char *dir, char *command);
int execute_command(char **command, char **envp);
int built_exit(char **args);

#endif
