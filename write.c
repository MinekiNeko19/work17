#include "write.h"

int main() {
  char temp[3];
  fgets(temp,3,stdin);
  parse_args("c");

  // access semaphore
  int semd = semget(KEY,0,0);
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1; //setting the operation to down

  semop(semd, &sb, 1); //perform the operation


  // closing the semaphores
  sb.sem_op = 1; //set the operation to up
  semop(semd, &sb, 1); //perform the operation
  parse_args("r");

  return 0;
}