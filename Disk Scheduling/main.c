#include <stdio.h>
#include <string.h>
#include "oslabs.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    printf(
        "Usage: %s [fcfs_arrival | fcfs_completion | sstf_arrival | "
        "sstf_completion | look_arrival | look_completion]\n",
        argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "fcfs_arrival") == 0) {
    handle_request_arrival_fcfs_test();
  } else if (strcmp(argv[1], "fcfs_completion") == 0) {
    handle_request_completion_fcfs_test();
  } else if (strcmp(argv[1], "sstf_arrival") == 0) {
    handle_request_arrival_sstf_test();
  } else if (strcmp(argv[1], "sstf_completion") == 0) {
    handle_request_completion_sstf_test();
  } else if (strcmp(argv[1], "look_arrival") == 0) {
    handle_request_arrival_look_test();
  } else if (strcmp(argv[1], "look_completion") == 0) {
    handle_request_completion_look_test();
  } else {
    printf("Unknown test: %s\n", argv[1]);
    return 1;
  }

  return 0;
}