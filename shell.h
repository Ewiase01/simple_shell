#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define BUFFER_SIZE 1024


int print_env(char **env
int env_builtin(char **args, char **env)
int _puts(char *str)
char *find_command(char *command)
char *build_path(char *dir, char *command)
int execute_command(char **command, char **envp)
int built_exit(char **args)
int main(int argc, char *argv[], char *envp[]);
void change_directory(char *path);
int main(int argc, char *argv[]);
void *_memcpy(void *dest, const void *src, size_t n)
void execute_command(char **args);
char *_getline(void)

#endif
