#include <stdio.h>
#include <stdlib.h>

static int lock = 0;

void acquire_lock() {
  printf("aquiring lock... ");
  if (lock != 0) {
    printf("failed\n");
    abort();
  }
  lock++;
  printf("success\n");
}

void release_lock() {
  printf("releasing lock... ");
  if (lock != 1) {
    printf("failed\n");
    abort();
  }
  lock--;
  printf("success\n");
}
