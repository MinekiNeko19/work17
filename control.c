#include "control.h"

int parse_args(char * line) {
    if (line[0] == 'c') {
        create();
        // print_err();
    }
    if (line[0]=='r') {
        rem();
        // print_err();
    }
    return errno;
}

void create() {
    // semaphone
    int semd = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (semd == -1) {
        // printf("error %d: %s\n", errno, strerror(errno));
        semd = semget(SEMKEY, 1, 0);
    }
    union semun us;
    us.val = 1;
    int r = semctl(semd, 0, SETVAL, us);
    printf("Semaphore value: %d\n", r);

    // shared memory
    int shmd = shmget(SHMKEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0644);
    if (shmd == -1) {
        // printf("error %d: %s\n", errno, strerror(errno));
        shmd = shmget(SHMKEY, 0, 0);
    }
    // int * data = shmat(shmd,0,0);
    // *data = 0;
    // printf("shmd: %d\tdata: %d\n",shmd, *data);
    // shmdt(data);

    // file
    int file = open("transcript", O_CREAT | O_EXCL | O_TRUNC, 0644);
    if (file == -1) {
        // printf("error %d: %s\n", errno, strerror(errno));
        file = open("transcript", O_RDWR);
    }
    close(file);
}

void rem() {
    int semd = semget(SEMKEY,0,0);
    if (semd == -1) {
        // printf("error %d: %s\n", errno, strerror(errno));
        semd = semget(SEMKEY, 1, 0);
    }
    semctl(semd,IPC_RMID,0);

    int shmd = shmget(SHMKEY,0,0);
    if (shmd == -1) {
        // printf("error %d: %s\n", errno, strerror(errno));
        shmd = shmget(SHMKEY, 1, 0);
    }
    shmctl(shmd,IPC_RMID,0);

    int file = open("transcript", O_RDONLY);
    struct stat sb;
    stat("transcript", &sb);
    char txt[sb.st_size];
    read(file,txt,sb.st_size-1);
    printf("%s\n",txt);
}

void print_err() {
   
}

int main(int argc, char *argv[]) {
    parse_args(argv[1]);
    return 0;
}