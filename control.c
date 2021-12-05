#include "control.h"

int semid;

int parse_args(char * line) {
    if (line[0]=='n') {
        printf("creating semaphore\n");
        create();
        print_err();
    }
    if (line[0]=='y') {
        printf("removing semaphore\n");
        rem();
        print_err();
    }
    return errno;
}

int create() {
    semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    return semid;
}

int rem() {
    semid = semget(KEY,0,0);
    semctl(semid,IPC_RMID,0);
    return semid;
}

void print_err() {
    if (errno) {
        printf("error %d: %s\n", errno, strerror(errno));
    }
    errno = 0;
}