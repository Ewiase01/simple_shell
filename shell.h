#ifndef SHELL_H
#define SHELL_H

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Prototypes */
void prompt(void);
void tokenize(char *line, char **args);
int execute(char **args);
void sighandler(int sig_num);

#endif /* SHELL_H */
