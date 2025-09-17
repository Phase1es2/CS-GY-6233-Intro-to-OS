#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "../Disk Scheduling/oslabs.h"

#define SADDR start_address
#define EADDR end_address
#define SS segment_size
#define PID process_id
#define MB MEMORY_BLOCK

struct MB NULLBLOCK = {0, 0, 0, 0};

struct MEMORY_BLOCK best_fit_allocate(int request_size,
                                      struct MEMORY_BLOCK memory_map[MAPMAX],
                                      int* map_cnt, int process_id) {
  int idx = -1, free_size = INT_MAX;
  for (int i = 0; i < (*map_cnt); i++)
    if (!memory_map[i].PID && memory_map[i].SS >= request_size &&
        free_size > memory_map[i].SS) {
      idx = i;
      free_size = memory_map[i].SS;
    }

  printf("idx: %d", idx);
  struct MB temp_mmap[MAPMAX];
  memcpy(temp_mmap, memory_map, sizeof(struct MB) * MAPMAX);

  struct MB returned_block, free_block;

  if (~idx && memory_map[idx].SS == request_size) {
    printf("ind this \n");
    memory_map[idx].PID = process_id;
    returned_block = memory_map[idx];
  } else if (~idx && memory_map[idx].SS > request_size) {
    int left = memory_map[idx].SS - request_size;
    printf("start_idx: %d\n", memory_map[idx].SS);
    returned_block = (struct MB){memory_map[idx].SADDR,
                                 memory_map[idx].SADDR + request_size - 1,
                                 request_size, process_id};
    free_block =
        (struct MB){memory_map[idx].SADDR + request_size,
                    memory_map[idx].SADDR + request_size + left - 1, left, 0};
    memory_map[idx] = returned_block;
    memory_map[idx + 1] = free_block;
    int tot = (*map_cnt) - left + 1;

    for (int i = 0; i < tot; i++)
      memory_map[idx + 2 + i] = temp_mmap[i + idx + 1];
    ++(*map_cnt);
  } else {
    printf("out here\n");
    returned_block = NULLBLOCK;
  }

  return returned_block;
}
struct MEMORY_BLOCK first_fit_allocate(int request_size,
                                       struct MEMORY_BLOCK memory_map[MAPMAX],
                                       int* map_cnt, int process_id) {
  return NULLBLOCK;
}
struct MEMORY_BLOCK worst_fit_allocate(int request_size,
                                       struct MEMORY_BLOCK memory_map[MAPMAX],
                                       int* map_cnt, int process_id) {
  return NULLBLOCK;
}
struct MEMORY_BLOCK next_fit_allocate(int request_size,
                                      struct MEMORY_BLOCK memory_map[MAPMAX],
                                      int* map_cnt, int process_id,
                                      int last_address) {
  return NULLBLOCK;
}
void release_memory(struct MEMORY_BLOCK freed_block,
                    struct MEMORY_BLOCK memory_map[MAPMAX], int* map_cnt) {
  return;
}