#include <stdio.h>
#include <stdlib.h>
// A control program
//     Take a command line argument to determine if it is
//     creating or removing the resources or viewing the story.
//     If creating (command line argument: -c):
//         Should make the shared memory, semaphore and
//         file (open the file with the truncate flag).
//         Set any values that are needed.
//     If removing (command line argument: -r)
//
//         Remove the shared memory, the semaphore and the story.
//         Display the full contents of the story.
//         This should wait until the semaphore is available.
//
//     If viewing (command line argument: -v)
//         Output the contents of the story file.
//         This mode does not need to interact with the semaphore

int main(){
  char *line = calloc(100, sizeof(char));
  printf("Enter a command!/n");
  fgets(line, 1000, stdin);
  line[strlen(line) - 1] = '/0';

  if(strcmp(line, "-c")){

  }
  else if(strcmp(line, "-r")){

  }
  else if(strcmp(line, "-v")){


  }



  return 0;
}
