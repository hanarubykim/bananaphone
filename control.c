#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys.ipc.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define KEY 24601

union semun {
  int                 val;      /*  Value for SETVAL                */
  struct semid_ds    *buf;      /*  Buffer for IPC_STAT, IPC_SET    */
  unsigned short     *array;    /*  Array for GETALL, SETALL        */
  struct seminfo     *__buf;    /*  Buffer for IPC_INFO             */
};

void creating(){
  printf("Creating the story!\n");
  // Make the shared memory
  int shmid = shmget(KEY, sizeof(int), 0644 | IPC_CREAT);
  // Make the semaphore
  int semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  // Set semaphore values
  union semun s;
  s.val = 1;
  int stat = semctl(semid, 0, SETVAL, s);
  if(stat == -1){
    printf("Error! %s\n", strerror(errno));
    return 1;
    }
  // Make text file
  int fd = open("a.txt", O_CREAT | O_TRUNC, 0644);
  if(fd == -1){
    printf("Error! %s\n", strerror(errno));
    return 1;
  }
  return 0;
}

void viewing(){
  // Output the contents of the story file.
  int fd = open("a.txt", O_RDONLY);
  char * text = calloc(sizeof(char), 10000);
  read(fd, text, 10000);
  printf("Story Time!\n%s", text);
  free(text);
}

void removing(){
  printf("Removing...\n");
  int ridsema = semget(KEY, 1, 0644);
  struct sembuf* temp = calloc(sizeof(struct sembuf), 1);
  temp->sem_num = 0;
  temp->sem_op = -1;
  temp->sem_flg = SEM_UNDO;
  int stat = semop(ridsema, temp, 1);
  free(temp);
  // Display the story
  viewing();
  // Remove the shared memory, the semaphore, and the story
  int shmid = shmget(KEY, sizeof(int), 0644);
  shmctl(smid, IPC_RMID, '\0');
  // Remove the semaphore
  semctl(ridsema, 0, IPC_RMID);
  // Remove the story
  remove("a.txt");
}

int main(){
  char *line = calloc(100, sizeof(char));
  printf("Enter a command!/n");
  fgets(line, 1000, stdin);
  line[strlen(line) - 1] = '/0';

  if(strcmp(line, "-c") == 0){
    creating();
  }
  else if(strcmp(line, "-r") == 0){
    removing();
  }
  else if(strcmp(line, "-v") == 0){
    viewing();
  }
  else{
    printf("Woopsie daisies! Try something different./n");
  }
  return 0;
}
