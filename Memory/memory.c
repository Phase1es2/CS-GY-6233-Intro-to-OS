#include <stdio.h>
#include "../Disk Scheduling/oslabs.h"

#define SADDR start_address
#define EADDR end_address
#define SS segment_size
#define PID process_id
#define MB MEMORY_BLOCK

struct MB NULLBLOCK = {0, 0, 0, 0};

struct MEMORY_BLOCK best_fit_allocate(int request_size,
                                      struct MEMORY_BLOCK memory_map[MAPMAX],
                                      int* map_cnt, int process_id);
struct MEMORY_BLOCK first_fit_allocate(int request_size,
                                       struct MEMORY_BLOCK memory_map[MAPMAX],
                                       int* map_cnt, int process_id);
struct MEMORY_BLOCK worst_fit_allocate(int request_size,
                                       struct MEMORY_BLOCK memory_map[MAPMAX],
                                       int* map_cnt, int process_id);
struct MEMORY_BLOCK next_fit_allocate(int request_size,
                                      struct MEMORY_BLOCK memory_map[MAPMAX],
                                      int* map_cnt, int process_id,
                                      int last_address);
void release_memory(struct MEMORY_BLOCK freed_block,
                    struct MEMORY_BLOCK memory_map[MAPMAX], int* map_cnt);