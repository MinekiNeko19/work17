#include "write.h"

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};

int main() {
    // access resources in semaphone
    parse_args("n");
    int semid = semget(KEY,0,0);
    int shmid = shmget(KEY,0,0);
    int file = open("transcript", O_RDONLY | O_WRONLY | O_APPEND);
    write(file,"help\n", 5);

    printf("semid: %d\tshmid: %d\n", semid,shmid);
    // parse_args("y");
    // close(file);  

    // display last line added to file

    // prompt for next line

    // write to file and shared mem

    // temporary test code
    // char input[100];
    // fgets(input, 3 , stdin);
    // printf("%c\n",input[0]);
    // parse_args(input);

    
}
int writing(char * line) {
    return 0;
}