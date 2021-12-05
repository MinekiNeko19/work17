#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

#define KEY 24602

int parse_args(char * line);
int create();
int rem();
void print_err();