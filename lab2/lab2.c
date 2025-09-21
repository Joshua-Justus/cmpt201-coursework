#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
  char *buff = NULL;
  size_t size = 0;
  ssize_t num_char;
  while (1) {
    printf("Enter some programs to run. \n");
    num_char = getline(&buff, &size, stdin);
    // removing trailing newline character
    if (buff[num_char - 1] == '\n') {
      buff[num_char - 1] = '\0';
    }
    // Exiting when "exit" is typed
    if (strcmp(buff, "exit") == 0) {
      printf("Exiting, bye bye :) \n");
      break;
    }
    // Continuing if empty string is passed
    if (strlen(buff) == 0) {
      printf("Nothing inputted so continuing. \n");
      continue;
    }
    pid_t pid = fork();
    if (pid < 0) {
      // if fork fails
      perror("fork failure");
      continue;
    }
    if (pid == 0) {
      // child process
      printf("Entering Child process. \n");
      execl(buff, buff, (char *)NULL);
      // if execl fails
      perror("execl failure");
      _exit(0);
    } else {
      // parent process
      int status;
      waitpid(pid, &status, 0);
      printf("Parent process is back. \n");
    }
  }
  free(buff);
}
