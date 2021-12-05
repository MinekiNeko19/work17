#include "control.h"

int semid;
int shmid;
int file;

int parse_args(char * line) {
    if (line[0]=='n') {
        // printf("creating semaphore\n");
        create();
        print_err();
    }
    if (line[0]=='y') {
        // printf("removing semaphore\n");
        rem();
        print_err();
    }
    return errno;
}

int create() {
    // semaphore
    semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (semid == -1) {
        semid = semget(KEY,0,0);
    }
    // shared memory
    shmid = shmget(KEY,sizeof(100), IPC_CREAT | IPC_EXCL | 0644);
    if (shmid == -1) {
        shmid = shmget(KEY,0,0);
    }
    // file
    file = open("transcript", O_CREAT | O_TRUNC, 0644);
    return errno;
}

int rem() {
    semid = semget(KEY,0,0);
    semctl(semid,IPC_RMID,0);

    shmid = shmget(KEY,0,0);
    shmctl(shmid,IPC_RMID,0);

    return errno;
}

void print_err() {
    if (errno) {
        printf("error %d: %s\n", errno, strerror(errno));
    }
    errno = 0;
}