#include "control.h"

int parse_args(char * line) {
    if (line[0] == 'c') {
        create();
        print_err();
    }
    if (line[0]=='r') {
        rem();
        print_err();
    }
    return errno;
}

void create() {
    // semaphone
    int semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (semd == -1) {
        printf("error %d: %s\n", errno, strerror(errno));
        semd = semget(KEY, 1, 0);
    }
    union semun us;
    us.val = 1;
    int r = semctl(semd, 0, SETVAL, us);
    printf("Semaphore value: %d\n", r);

    // shared memory
    // file
}

void rem() {
    int semd = semget(KEY,0,0);
    if (semd == -1) {
        printf("error %d: %s\n", errno, strerror(errno));
        semd = semget(KEY, 1, 0);
    }
    semctl(semd,IPC_RMID,0);
}

void print_err() {
   
}