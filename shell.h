#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdbool.h>

void display_prompt(void);
extern char **environ;
ssize_t get_line(char **input, size_t *len, FILE *file);
void is_env(char **argv);
char **tokenize(char *input);
void exec_ve(char **argv);
void is_exit(char **argv, char *input);
char *get_path(char **argv);
char *str_tok(char *str, const char *delim);
void free_memory(char *input, char **argv);
bool is_all_spaces(char *input, ssize_t read);

#endif
