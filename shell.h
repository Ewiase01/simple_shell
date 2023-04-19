#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 1024
#define TOKEN_DELIM " \t\r\n\a"

/* Function prototypes */

int main(void);
void shell_loop(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
int launch(char **args);

#endif /* SHELL_H */
