#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "fuzzer.h"
#include "libqubes-rpc-filecopy.h"
#include "ioall.h"
#include "crc32.h"

void display_error(const char *fmt, va_list args)
{
  return;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  
  const char* in_filename = "/tmp/in";
  const char* out_filename = "/tmp/out";
  FILE* in_file = fopen(in_filename, "wb+");
  int in_fd = fileno(in_file);
  write_all(in_fd, data, size);

  FILE* out_file = fopen(out_filename, "wb+");
  int out_fd = fileno(out_file);
  
  dup2(out_fd, STDOUT_FILENO);

  qfile_pack_init();
  register_error_handler(display_error);
  do_fs_walk(in_filename, 0);
  
  fclose(in_file);
  fclose(out_file);
  
  return 0;
}
