#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Function to add a line of input into history using buffer
void add_to_history(char *history[], char *buffer, int *index, int *count) {
  // Making sure old string is not overwritten and is freed first
  if (history[*index] != NULL) {
    free(history[*index]);
  }
  // Duplicating string into history
  history[*index] = strdup(buffer);
  // Updating index by wrapping around the size of history and updating count
  *index = (*index + 1) % 5;
  if (*count < 5) {
    (*count)++;
  }
}
// Function to print out the last 5 inputs
void print_history(char *history[], int index, int count) {
  int start = (index + (5 - count)) % 5;
  // Loop to print out the correct 5 inputs
  for (int i = 0; i < count; i++) {
    int position = (start + i) % 5;
    printf("%s", history[position]);
  }
}
int main() {
  char *history[5] = {NULL};
  int index = 0;
  int count = 0;
  char *buffer = NULL;
  size_t buffer_size = 0;
  while (1) {
    printf("Enter input: ");
    // Incase getline returns -1 for an error
    if (getline(&buffer, &buffer_size, stdin) == -1) {
      break;
    }
    // Making sure printing occurs when "print" is the latest input
    add_to_history(history, buffer, &index, &count);
    if (strcmp(buffer, "print\n") == 0) {
      print_history(history, index, count);
    }
  }
  // Cleaning up
  free(buffer);
  for (int i = 0; i < 5; i++) {
    free(history[i]);
  }
  return 0;
}
