#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
struct header {
  uint64_t size;
  struct header *next;
};
// print_out function
void print_out(char *format, void *data, size_t data_size) {
  char buf[256];
  ssize_t len = snprintf(buf, 256, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data
                                                       : *(void **)data);
  write(STDOUT_FILENO, buf, len);
}
int main() {
  // increasing heap size to 256 bytes
  void *start = sbrk(256);
  // create block headers
  struct header *block1 = (struct header *)start;
  struct header *block2 = (struct header *)((char *)start + 128);
  // initialize headers
  block1->size = 128;
  block1->next = NULL;
  block2->size = 128;
  block2->next = block1;
  // initialize block data
  void *data1 = (char *)block1 + sizeof(struct header);
  void *data2 = (char *)block2 + sizeof(struct header);
  // filling data1 with 0's and data2 with 1's
  memset(data1, 0, 128 - sizeof(struct header));
  memset(data2, 1, 128 - sizeof(struct header));
  // print info from headers
  print_out("Block 1 address: %p\n", &block1, sizeof(block1));
  print_out("Block 2 address: %p\n", &block2, sizeof(block2));
  print_out("Block 1 size: %lu\n", &block1->size, sizeof(block1->size));
  print_out("Block 1 next: %p\n", &block1->next, sizeof(block1->next));
  print_out("Block 2 size: %lu\n", &block2->size, sizeof(block2->size));
  print_out("Block 2 next: %p\n", &block2->next, sizeof(block2->next));
  // print block data
  write(STDOUT_FILENO, "Block 1 data:\n", 14);
  for (int i = 0; i < 128 - sizeof(struct header); i++) {
    char buf[32];
    int len = snprintf(buf, sizeof(buf), "%d\n", ((unsigned char *)data1)[i]);
    write(STDOUT_FILENO, buf, len);
  }
  write(STDOUT_FILENO, "Block 2 data:\n", 14);
  for (int i = 0; i < 128 - sizeof(struct header); i++) {
    char buf[32];
    int len = snprintf(buf, sizeof(buf), "%d\n", ((unsigned char *)data2)[i]);
    write(STDOUT_FILENO, buf, len);
  }
  write(STDOUT_FILENO, "\n", 1);
  return 0;
}
