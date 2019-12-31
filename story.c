#include <stdlib.h>
// Will attempt to access the resources using the semaphore
// Once in, it should display the last line added to the file
// (use shared memory to contain the size of the last line).
// Prompt the use for the next line.
// Once a new line is read, write that to the file,
//update the shared memory and then release the semaphore


int main(){
  //Use semaphore

  int fd = open("a.txt", O_RDWR | O_APPEND);
  char * current = calloc(10000, sizeof(char));
  read(fd, current, 10000);

  // Display last line added to the file
  // Use shared memory to contain size of last line

  // Prompt use for the next line
  printf("Add a new line: \n");
  char * toAdd = calloc(1000, sizeof(char));
  fgets(toAdd, 1000, stdin);
  toAdd[strlen(toAdd) - 1] = '\0';
  int nextLineLen = strlen(toAdd);

  // Write that to the file
  write(fd, toAdd, nextLineLen);
  // Update the shared memory

  // Release the semaphore
}
