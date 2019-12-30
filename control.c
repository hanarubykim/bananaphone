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
union sema{
  int val;
}

//     If creating (command line argument: -c):
//         Should make the shared memory, semaphore and
//         file (open the file with the truncate flag).
//         Set any values that are needed.
void creating(){
  printf("Creating the story!\n");
  // Make the shared memory
  int shmid = shmget(KEY, sizeof(int), 0644 | IPC_CREAT);
  // Make the semaphore
  int semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  // Set semaphore values
  sema s;
  s.val = 1;
  int stat = semctl(semid, 0, SETVAL, s);
  if(stat == -1){
    printf("Error! %s\n", strerror(errno));
    return 1;
    }
  //Make file
  int fd = open("a.txt", O_CREAT | O_TRUNC, 0644);
  if(fd == -1){
    printf("Error! %s\n", strerror(errno));
    return 1;
  }
  return 0;
}

void removing(){


}

void viewing(){

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

//     If removing (command line argument: -r)
//
//         Remove the shared memory, the semaphore and the story.
//         Display the full contents of the story.
//         This should wait until the semaphore is available.
//
//     If viewing (command line argument: -v)
//         Output the contents of the story file.
//         This mode does not need to interact with the semaphore
