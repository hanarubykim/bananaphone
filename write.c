#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <string.h>

#define KEY 24602

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                              (Linux-specific) */
};

int main(){
  //Use semaphore
  int desc = semget(KEY, 1, 0);
  struct sembuf* s = calloc(sizeof(struct sembuf), 1);
  s->sem_num = 0;
  s->sem_op = -1;
  s->sem_flg = SEM_UNDO;
  int current_stat = semop(desc, s, 1);
  int shmid = shmget(KEY, sizeof(int), 0644);

  int fd = open("a.txt", O_RDWR | O_APPEND);
  char * current = calloc(10000, sizeof(char));
  read(fd, current, 10000);

  // Display last line added to the file
  // Use shared memory to contain size of last line
  int * d = shmat(shmid, 0, 0);
  int length = d[0];
  char * lastLine = current + strlen(current) - length;
  printf("The last line: %s\n", lastLine);

  // Prompt use for the next line
  printf("Add a new line: \n");
  char * toAdd = calloc(1000, sizeof(char));
  fgets(toAdd, 1000, stdin);
  toAdd[strlen(toAdd) - 1] = '\0';
  int nextLineLen = strlen(toAdd);

  // Write that to the file
  write(fd, toAdd, nextLineLen);

  // Update the shared memory
  d[0] = nextLineLen;

  // Release the semaphore
  s->sem_op = 1;
  semop(desc, s, 1);

  return 0;
}
