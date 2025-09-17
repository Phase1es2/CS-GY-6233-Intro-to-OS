#include <stdio.h>
#include <string.h>
#include "../Disk Scheduling/oslabs.h"

#define SADDR start_address
#define EADDR end_address
#define SS segment_size
#define PID process_id
#define MB MEMORY_BLOCK
/**
 * struct MEMORY_BLOCK best_fit_allocate(int request_size,
                                      struct MEMORY_BLOCK memory_map[MAPMAX],
                                      int* map_cnt, int process_id);
 */

void set_mb(struct MB* inb, int start_address, int end_address,
            int segment_size, int process_id) {
  (*inb).SADDR = start_address;
  (*inb).EADDR = end_address;
  (*inb).SS = segment_size;
  (*inb).PID = process_id;
}

void print_block(const char* label, struct MB b) {
  printf("%s[SADDR: %d, EADDR: %d, SS: %d, PID: %d]\n", label, b.SADDR, b.EADDR,
         b.SS, b.PID);
}

void print_map(const char* label, struct MB memory_map[], int map_cnt) {
  if (map_cnt == 0) {
    printf("%sEmpty Map!\n", label);
    return;
  }
  for (int i = 0; i < map_cnt; i++) {
    char entry[64];
    snprintf(entry, sizeof(entry), "%s[%d] ", label, i);
    print_block(entry, memory_map[i]);
  }
  printf("%smap_cnt: %d\n", label, map_cnt);
}

void best_fit_allocate_test() {
  struct MB memory_map[MAPMAX];
  struct MB b1, b2, b3, b4, returned_block;
  int map_cnt = 0;
  int request_size, PID;

  memset(memory_map, 0, sizeof memory_map);

  set_mb(&b1, 0, 1023, 1024, 0);
  memory_map[map_cnt++] = b1;
  request_size = 10, PID = 32;

  returned_block = best_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q1 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;
  set_mb(&b1, 0, 19, 20, 10);
  set_mb(&b2, 20, 39, 20, 0);
  set_mb(&b3, 40, 49, 10, 20);
  set_mb(&b4, 50, 1023, 974, 0);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;

  request_size = 20, PID = 40;

  returned_block = best_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q2 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;

  set_mb(&b1, 0, 19, 20, 10);
  set_mb(&b2, 20, 39, 20, 0);
  set_mb(&b3, 40, 49, 10, 20);
  set_mb(&b4, 50, 1023, 974, 30);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;

  request_size = 30, PID = 40;

  returned_block = best_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q3 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;

  set_mb(&b1, 0, 19, 20, 10);
  set_mb(&b2, 20, 39, 20, 20);
  set_mb(&b3, 40, 54, 15, 0);
  set_mb(&b4, 55, 1023, 969, 30);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;

  request_size = 10, PID = 40;

  returned_block = best_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q3 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");
}

void first_fit_allocate_test() {
  struct MB memory_map[MAPMAX];
  struct MB b1, b2, b3, b4, returned_block;
  int map_cnt = 0;
  int request_size, PID;
  memset(memory_map, 0, sizeof memory_map);
  set_mb(&b1, 0, 1023, 1024, 0);
  memory_map[map_cnt++] = b1;
  request_size = 10, PID = 32;

  returned_block = first_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q1 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;
  set_mb(&b1, 0, 19, 20, 10);
  set_mb(&b2, 20, 39, 20, 0);
  set_mb(&b3, 40, 49, 10, 20);
  set_mb(&b4, 50, 1023, 974, 0);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;

  request_size = 20, PID = 40;

  returned_block = first_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q2 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;
  set_mb(&b1, 0, 19, 20, 10);
  set_mb(&b2, 20, 39, 20, 0);
  set_mb(&b3, 40, 49, 10, 20);
  set_mb(&b4, 50, 1023, 974, 30);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;

  request_size = 30, PID = 40;

  returned_block = first_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q3 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;

  set_mb(&b1, 0, 19, 20, 0);
  set_mb(&b2, 20, 39, 20, 20);
  set_mb(&b3, 40, 54, 15, 0);
  set_mb(&b4, 55, 1023, 969, 0);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;

  request_size = 15, PID = 40;

  returned_block = first_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q4 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");
}

void worst_fit_allocate_test() {
  struct MB memory_map[MAPMAX];
  struct MB b1, b2, b3, b4, returned_block;
  int map_cnt = 0;
  int request_size, PID;

  memset(memory_map, 0, sizeof memory_map);

  set_mb(&b1, 0, 1023, 1024, 0);
  memory_map[map_cnt++] = b1;
  request_size = 10, PID = 32;

  returned_block = worst_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q1 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;
  set_mb(&b1, 0, 19, 20, 10);
  set_mb(&b2, 20, 39, 20, 0);
  set_mb(&b3, 40, 49, 10, 20);
  set_mb(&b4, 50, 1023, 974, 30);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;

  request_size = 20, PID = 40;

  returned_block = worst_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q2 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;

  set_mb(&b1, 0, 19, 20, 10);
  set_mb(&b2, 20, 39, 20, 0);
  set_mb(&b3, 40, 49, 10, 20);
  set_mb(&b4, 50, 1023, 974, 30);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;

  request_size = 30, PID = 40;

  returned_block = worst_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q3 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;

  set_mb(&b1, 0, 19, 20, 0);
  set_mb(&b2, 20, 39, 20, 20);
  set_mb(&b3, 40, 54, 15, 30);
  set_mb(&b4, 55, 1023, 969, 0);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;

  request_size = 10, PID = 40;

  returned_block = worst_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q4 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");
}

void next_fit_allocate_test() {
  struct MB memory_map[MAPMAX];
  struct MB b1, b2, b3, b4, b5, returned_block;
  int map_cnt = 0;
  int request_size, PID, last_address;

  memset(memory_map, 0, sizeof memory_map);
  set_mb(&b1, 0, 1023, 1024, 0);
  memory_map[map_cnt++] = b1;

  request_size = 10, PID = 32, last_address = 0;

  returned_block =
      next_fit_allocate(request_size, memory_map, &map_cnt, PID, last_address);
  print_map("Q1 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;

  set_mb(&b1, 0, 19, 20, 10);
  set_mb(&b2, 20, 39, 20, 0);
  set_mb(&b3, 40, 49, 10, 20);
  set_mb(&b4, 50, 1023, 974, 30);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;

  request_size = 20, PID = 40, last_address = 0;

  returned_block = worst_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q2 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;

  set_mb(&b1, 0, 19, 20, 10);
  set_mb(&b2, 20, 39, 20, 0);
  set_mb(&b3, 40, 49, 10, 20);
  set_mb(&b4, 50, 1023, 974, 30);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;

  request_size = 30, PID = 40, last_address = 0;

  returned_block = worst_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q3 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;

  set_mb(&b1, 0, 19, 20, 0);
  set_mb(&b2, 20, 39, 20, 20);
  set_mb(&b3, 40, 54, 15, 0);
  set_mb(&b4, 55, 74, 20, 30);
  set_mb(&b5, 75, 1023, 949, 0);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;
  memory_map[map_cnt++] = b5;

  request_size = 30, PID = 40, last_address = 2;

  returned_block = worst_fit_allocate(request_size, memory_map, &map_cnt, PID);

  print_map("Q3 ", memory_map, map_cnt);
  print_block("Returned ", returned_block);
  puts("----------------------------------------------------------");
}

void release_memory_test() {
  struct MB memory_map[MAPMAX];
  struct MB b1, b2, b3, b4, b5, free_block, returned_block;
  int map_cnt = 0;
  int request_size, PID, last_address;

  memset(memory_map, 0, sizeof memory_map);
  set_mb(&b1, 0, 7, 8, 12);
  set_mb(&b2, 8, 15, 8, 0);
  set_mb(&b3, 16, 23, 8, 13);
  set_mb(&b4, 24, 27, 4, 0);
  set_mb(&b5, 28, 29, 2, 11);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;
  memory_map[map_cnt++] = b5;

  set_mb(&free_block, 16, 23, 8, 13);
  release_memory(free_block, memory_map, &map_cnt);

  print_map("Q1 ", memory_map, map_cnt);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;
  set_mb(&b1, 0, 19, 20, 0);
  set_mb(&b2, 20, 39, 20, 20);
  set_mb(&b3, 40, 54, 15, 40);
  set_mb(&b4, 55, 74, 20, 30);
  set_mb(&b5, 75, 1023, 949, 0);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;
  memory_map[map_cnt++] = b5;

  set_mb(&free_block, 20, 39, 20, 20);
  release_memory(free_block, memory_map, &map_cnt);

  print_map("Q2 ", memory_map, map_cnt);
  puts("----------------------------------------------------------");

  memset(memory_map, 0, sizeof memory_map);
  map_cnt = 0;
  set_mb(&b1, 0, 19, 20, 0);
  set_mb(&b2, 20, 39, 20, 20);
  set_mb(&b3, 40, 54, 15, 40);
  set_mb(&b4, 55, 74, 20, 30);
  set_mb(&b5, 75, 1023, 949, 0);
  memory_map[map_cnt++] = b1;
  memory_map[map_cnt++] = b2;
  memory_map[map_cnt++] = b3;
  memory_map[map_cnt++] = b4;
  memory_map[map_cnt++] = b5;

  set_mb(&free_block, 55, 74, 20, 30);
  release_memory(free_block, memory_map, &map_cnt);

  print_map("Q3 ", memory_map, map_cnt);
  puts("----------------------------------------------------------");
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf(
        "Usage: %s [best_fit | first_fit | worst_fit | "
        "next_fit | release_memory]\n",
        argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "best_fit") == 0) {
    best_fit_allocate_test();
  } else if (strcmp(argv[1], "first_fit") == 0) {
    first_fit_allocate_test();
  } else if (strcmp(argv[1], "worst_fit") == 0) {
    worst_fit_allocate_test();
  } else if (strcmp(argv[1], "next_fit") == 0) {
    next_fit_allocate_test();
  } else if (strcmp(argv[1], "release_memory") == 0) {
    release_memory_test();
  } else {
    printf("Unknown test: %s\n", argv[1]);
    return 1;
  }

  return 0;
}