#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
  if (argc != 3) {
      printf( "usage: ./cs238p <file1> <file2>\n");
      exit(0);
  }
  /* Open file descriptors */
  int input_fd = open(argv[1], O_RDONLY);
  if (input_fd < 0) {
      printf("Cannot open file %s for reading\n", argv[1]);
      exit(0);
  }
  int output_fd = open(argv[2], O_WRONLY | O_CREAT);
  if (output_fd < 0) {
      printf("Cannot open file %s for writing\n", argv[2]);
      exit(0);
  }
  int num_read = 0;
  int num_write = 0;
  char buf[1024];
  /* Copy Logic */
  while ((num_read = read(input_fd, buf, sizeof(buf))) > 0) {
     num_write = write(output_fd, buf, num_read);
     if (num_write < 0) {
         printf("Write Error\n");
         exit(0);
     }
  } 
  if (num_read < 0) {
      printf("Read Error\n");
      exit(0);
  }
  /* Close file descriptors */
  if (close(input_fd) || close(output_fd)) {
      printf("Close error\n");
      exit(0);
  }
  printf("%s has been successfully copied into %s\n", argv[1], argv[2]);
  exit(0);
}
