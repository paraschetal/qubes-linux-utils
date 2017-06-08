#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include "fuzzer.h"
#include "libqubes-rpc-filecopy.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  //fuzz
  return 0;
}
