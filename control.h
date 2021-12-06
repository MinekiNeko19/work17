#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define SEMKEY 24602
#define SHMKEY 24603

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};

// struct sembuf {
//   short sem_op;
//   short sem_num;
//   short sem_flag;
// };

int parse_args(char * line);
void create();
void rem();
void print_err();