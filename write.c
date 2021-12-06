#include "write.h"

int main() {
  // access semaphore
  int semd = semget(SEMKEY,0,0);
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1; //setting the operation to down

  semop(semd, &sb, 1); //perform the operation

  // access shared memory
  int shmd = shmget(SHMKEY,0,0);
  int * d = shmat(shmd,0,0);
  printf("shmd data: %d\n",*d);

  // access transcript
  int file = open("transcript", O_RDWR | O_APPEND);

  // read last line of transcript
  struct stat s;
  stat("transcript", &s);
  char txt[s.st_size];
  read(file,txt,s.st_size-2);
  txt[s.st_size] = '\n';
  // printf("%s\n", txt);

  char line[100];
  int j = s.st_size-1 - *d;
  int x = 0;
  while (txt[j]) {
    line[x] = txt[j];
    x++;
    j++;
  }
  printf("Last Line: %s\n",line);

  // input
  char input[100];
  printf("Enter Next Line: ");
  fgets(input,99,stdin);
  input[100] = '\n';
  printf("%s\n",input);


  // write input into transcript
  *d = 0;
  int i = 0;
  while(input[i]) {
    write(file,input+i,1);
    (*d)++;
    i++;
  }

  // closing the semaphores
  sb.sem_op = 1; //set the operation to up
  semop(semd, &sb, 1); //perform the operation

  // closing shared memory
  shmdt(d);

  // closing file
  close(file);
  
  // printf("Finished with the story? (y/n)\n");
  // char temp[3];
  // fgets(temp,3,stdin);
  // parse_args(temp);

  return 0;
}