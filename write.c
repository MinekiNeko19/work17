#include "write.h"

int main() {
  parse_args("c");

  // access semaphore
  int semd = semget(SEMKEY,0,0);
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1; //setting the operation to down

  semop(semd, &sb, 1); //perform the operation

  // access shared memory
  int shmd = shmget(SHMKEY,0,0);
  int * data = shmat(shmd,0,0);
  printf("shmd data: %d\n",*data);

  // access transcript
  int file = open("transcript", O_APPEND);
  // char line[100];
  // read(file,line,*data);
  // printf("Last Line: %s\n",line);
  char input[100];
  printf("Enter Next Line: ");
  fgets(input,99,stdin);
  input[100] = '\0';
  write(file,input,100);

  // closing the semaphores
  sb.sem_op = 1; //set the operation to up
  semop(semd, &sb, 1); //perform the operation

  // closing shared memory
  shmdt(data);

  // closing file
  close(file);
  
  printf("Finished with the story? (y/n)\n");
  char temp[3];
  fgets(temp,3,stdin);
  parse_args(temp);

  return 0;
}