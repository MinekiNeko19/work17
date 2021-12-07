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
        // print_err();
        semd = semget(SEMKEY, 1, 0);
    }
    union semun us;
    us.val = 1;
    int r = semctl(semd, 0, SETVAL, us);
    // printf("Semaphore value: %d\n", r);

    // shared memory
    int shmd = shmget(SHMKEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0644);
    // printf("shmd: %d\n", shmd);
    if (shmd == -1) {
        // print_err();
        shmd = shmget(SHMKEY, 0, 0);
    }

    // file
    int file = open("transcript", O_CREAT | O_TRUNC, 0644);
    // printf("file: %d\n",file);
    if (file == -1) {
        // print_err();
        file = open("transcript", O_RDWR);
    }
    close(file);
}

void rem() {
    int semd = semget(SEMKEY,0,0);
    // print_err();
    semctl(semd,IPC_RMID,0);

    int shmd = shmget(SHMKEY,0,0);
    // print_err();
    shmctl(shmd,IPC_RMID,0);

    int file = open("transcript", O_RDONLY);
    struct stat sb;
    stat("transcript", &sb);
    char txt[sb.st_size];
    // printf("size of transcript: %ld\n", sb.st_size);
    read(file,txt,sb.st_size);
    int i = 0;
    while (i < sb.st_size) {
        // printf("txt[%i]: %c\n",i,txt[i]);
        printf("%c",txt[i]);
        i++;
    }
    // printf("Compared to:\n%s\n",txt);
}

void print_err() {
   printf("error %d: %s\n", errno, strerror(errno));
   errno = 0;
}

int main(int argc, char *argv[]) {
    parse_args(argv[1]);
    return 0;
}