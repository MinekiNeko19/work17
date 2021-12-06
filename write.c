#include "write.h"

int main() {
  create();

  // access semaphore
  int semd = semget(SEMKEY,0,0);
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1; //setting the operation to down

  semop(semd, &sb, 1); //perform the operation

  // access shared memory
  // int * d;
  // *d = 0;
  int shmd = shmget(SHMKEY,0,0);
  int * d = shmat(shmd,0,0);
  printf("shmd data: %d\n",*d);

  // access transcript
  int file = open("transcript", O_WRONLY | O_APPEND);
  char line[100];
  read(file,line,100);
  printf("Last Line: %s\n",line);
  char input[100];
  printf("Enter Next Line: ");
  fgets(input,99,stdin);
  input[100] = '\n';
  printf("%s\n",input);
  int i = 0;
  while(input[i]) {
    write(file,input+i,1);
    i++;
  }

  // closing the semaphores
  sb.sem_op = 1; //set the operation to up
  semop(semd, &sb, 1); //perform the operation

  // closing shared memory
  shmdt(d);

  // closing file
  close(file);
  
  printf("Finished with the story? (y/n)\n");
  char temp[3];
  fgets(temp,3,stdin);
  parse_args(temp);

  return 0;
}