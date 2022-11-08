#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "t_file_info.h"

file_info t_file_constructor(void) {
  file_info file_ptr = malloc(sizeof(t_file_info));
  return file_ptr;
}

void t_file_destructor(file_info this) {
  free(this->name);
  free(this->typeflag);
  free(this->linkname);
  free(this->magic);
  free(this->version);
  free(this->uname);
  free(this->gname);
  free(this->prefix);
  free(this);
}

int t_file_initialize(file_info this) {
  this->name = malloc(100 * sizeof(char));
  this->mode = 0;
  this->uid = 0;
  this->gid = 0;
  this->size = 0;
  this->mtime = 0;
  this->chksum = 0;
  this->typeflag = malloc(2 * sizeof(char));
  this->linkname = malloc(100 * sizeof(char));
  this->magic = malloc(6 * sizeof(char));
  this->version = malloc(2 * sizeof(char));
  this->uname = malloc(32 * sizeof(char));
  this->gname = malloc(32 * sizeof(char));
  this->devmajor = 0;
  this->devminor = 0;
  this->prefix = malloc(155 * sizeof(char));
  return 0;
}

file_info get_file_info(file_info this, char *filename) {
  struct stat filestat;
  int stat_result;

  if(stat(filename, &filestat) == -1) {
    printf("Unable to get file properties\n");
  }
  else {
    this->mode = filestat.st_mode;
    printf("file mode: %ld\n", this->mode);
  }
  return this;
}

////main function for testing above functions
int main(int argc, char **argv) {

  //Test t_file_constructor and t_file_initialize
  file_info file_1 = t_file_constructor();
  t_file_initialize(file_1);

  //Test get_file_info
  if(argc > 1) {
    printf("%s\n", argv[1]);
    file_1 = get_file_info(file_1, argv[1]);
  }
  else {
    printf("No inputs, skipping get_file_info test\n");
  }
  
  t_file_destructor(file_1);
  return 0;
}