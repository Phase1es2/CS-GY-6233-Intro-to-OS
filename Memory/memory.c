#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "oslabs.h"

#define SADDR start_address
#define EADDR end_address
#define SS segment_size
#define PID process_id
#define MB MEMORY_BLOCK

// default NULLBLOCK = [start_address: 0, end_address: 0, segment_size: 0, process_id: 0]

struct MB NULLBLOCK = {0, 0, 0, 0};

struct MEMORY_BLOCK best_fit_allocate(int request_size,
                                      struct MEMORY_BLOCK memory_map[MAPMAX],
                                      int* map_cnt, int process_id) {
  // finds the candidate memory blocks that can be allocated
  // and chooses the one whose size is closest to the requested size.
  int idx = -1, free_size = INT_MAX;
  for (int i = 0; i < (*map_cnt); i++)
    if (!memory_map[i].PID && memory_map[i].SS >= request_size &&
        free_size > memory_map[i].SS) {
      idx = i;
      free_size = memory_map[i].SS;
    }
  struct MB temp_mmap[MAPMAX];
  memcpy(temp_mmap, memory_map, sizeof(struct MB) * MAPMAX);

  struct MB returned_block, free_block;

  //  free block found is exactly of the same size as the requested size
  if (~idx && memory_map[idx].SS == request_size) {
    // updates the process id to allocate it
    memory_map[idx].PID = process_id;
    returned_block = memory_map[idx];

    // free block larger than the requested size,
  } else if (~idx && memory_map[idx].SS > request_size) {
    // split into two pieces
    int left = memory_map[idx].SS - request_size;
    // first piece allocated
    returned_block = (struct MB){memory_map[idx].SADDR,
                                 memory_map[idx].SADDR + request_size - 1,
                                 request_size, process_id};
    // second piece becoming a free block
    free_block =
        (struct MB){memory_map[idx].SADDR + request_size,
                    memory_map[idx].SADDR + request_size + left - 1, left, 0};
    memory_map[idx] = returned_block;
    memory_map[idx + 1] = free_block;
    int tot = (*map_cnt) - idx + 1;

    for (int i = 0; i < tot; i++) {
      memory_map[idx + 2 + i] = temp_mmap[i + idx + 1];
    }
    ++(*map_cnt);
    //  no free block of memory
  } else {
    // returns the NULLBLOCK
    returned_block = NULLBLOCK;
  }

  // returns this memory block
  return returned_block;
}

struct MEMORY_BLOCK first_fit_allocate(int request_size,
                                       struct MEMORY_BLOCK memory_map[MAPMAX],
                                       int* map_cnt, int process_id) {
  // // finds the candidate memory blocks that can be allocated
  int idx = -1;
  for (int i = 0; i < (*map_cnt); i++) {
    if (!memory_map[i].PID && memory_map[i].SS >= request_size) {
      idx = i;
    }
    if (~idx)
      break;
  }
  struct MB temp_mmap[MAPMAX];
  memcpy(temp_mmap, memory_map, sizeof(struct MB) * MAPMAX);

  struct MB returned_block, free_block;

  //  free block found is exactly of the same size as the requested size
  if (~idx && memory_map[idx].SS == request_size) {
    // updates the process id to allocate it
    memory_map[idx].PID = process_id;
    returned_block = memory_map[idx];
    // free block larger than the requested size,
  } else if (~idx && memory_map[idx].SS > request_size) {
    // split into two pieces
    int left = memory_map[idx].SS - request_size;
    // first piece allocated
    returned_block = (struct MB){memory_map[idx].SADDR,
                                 memory_map[idx].SADDR + request_size - 1,
                                 request_size, process_id};

    // second piece becoming a free block
    free_block =
        (struct MB){memory_map[idx].SADDR + request_size,
                    memory_map[idx].SADDR + request_size + left - 1, left, 0};
    memory_map[idx] = returned_block;
    memory_map[idx + 1] = free_block;
    int tot = (*map_cnt) - idx + 1;

    for (int i = 0; i < tot; i++)
      memory_map[idx + 2 + i] = temp_mmap[i + idx + 1];

    ++(*map_cnt);
    //  no free block of memory
  } else {
    // returns the NULLBLOCK
    returned_block = NULLBLOCK;
  }
  // returns this memory block
  return returned_block;
}

struct MEMORY_BLOCK worst_fit_allocate(int request_size,
                                       struct MEMORY_BLOCK memory_map[MAPMAX],
                                       int* map_cnt, int process_id) {

  // finds memory blocks that can be allocated
  // and chooses the largest among these blocks
  int idx = -1, free_size = INT_MAX, max_free_size = 0;
  for (int i = 0; i < (*map_cnt); i++)
    if (!memory_map[i].PID && memory_map[i].SS >= request_size) {
      if (max_free_size < memory_map[i].SS) {
        idx = i;
        max_free_size = memory_map[i].SS;
      }
    }
  struct MB temp_mmap[MAPMAX];
  memcpy(temp_mmap, memory_map, sizeof(struct MB) * MAPMAX);

  struct MB returned_block, free_block;

  // free block found is exactly of the same size as the requested size
  if (~idx && memory_map[idx].SS == request_size) {
    // updates the process id to allocate it
    memory_map[idx].PID = process_id;
    returned_block = memory_map[idx];

    // free block larger than the requested size,
  } else if (~idx && memory_map[idx].SS > request_size) {
    // split into two pieces
    int left = memory_map[idx].SS - request_size;
    // first piece allocated
    returned_block = (struct MB){memory_map[idx].SADDR,
                                 memory_map[idx].SADDR + request_size - 1,
                                 request_size, process_id};

    // second piece becoming a free block
    free_block =
        (struct MB){memory_map[idx].SADDR + request_size,
                    memory_map[idx].SADDR + request_size + left - 1, left, 0};
    memory_map[idx] = returned_block;
    memory_map[idx + 1] = free_block;
    int tot = (*map_cnt) - idx + 1;

    for (int i = 0; i < tot; i++) {
      memory_map[idx + 2 + i] = temp_mmap[i + idx + 1];
    }
    ++(*map_cnt);
    //  no free block of memory
  } else {
    // returns the NULLBLOCK
    returned_block = NULLBLOCK;
  }
  // returns this memory block
  return returned_block;
}

struct MEMORY_BLOCK next_fit_allocate(int request_size,
                                      struct MEMORY_BLOCK memory_map[MAPMAX],
                                      int* map_cnt, int process_id,
                                      int last_address) {

  //  finds the first (lowest starting address) free memory block,
  // greater than or equal to the previously allocated block address,
  //whose size is at least as the requested size
  int idx = -1;
  if (last_address > (*map_cnt))
    return NULLBLOCK;
  for (int i = last_address; i < (*map_cnt); i++) {
    if (!memory_map[i].PID && memory_map[i].SS >= request_size) {
      idx = i;
    }
    if (~idx)
      break;
  }
  struct MB temp_mmap[MAPMAX];
  memcpy(temp_mmap, memory_map, sizeof(struct MB) * MAPMAX);

  struct MB returned_block, free_block;
  // free block found is exactly of the same size as the requested size
  if (~idx && memory_map[idx].SS == request_size) {
    // updates the process id to allocate it
    memory_map[idx].PID = process_id;
    returned_block = memory_map[idx];
    // free block larger than the requested size,
  } else if (~idx && memory_map[idx].SS > request_size) {
    // split into two pieces
    int left = memory_map[idx].SS - request_size;
    // first piece allocated
    returned_block = (struct MB){memory_map[idx].SADDR,
                                 memory_map[idx].SADDR + request_size - 1,
                                 request_size, process_id};
    // second piece becoming a free block
    free_block =
        (struct MB){memory_map[idx].SADDR + request_size,
                    memory_map[idx].SADDR + request_size + left - 1, left, 0};
    memory_map[idx] = returned_block;
    memory_map[idx + 1] = free_block;
    int tot = (*map_cnt) - idx + 1;

    for (int i = 0; i < tot; i++)
      memory_map[idx + 2 + i] = temp_mmap[i + idx + 1];

    ++(*map_cnt);
    //  no free block of memory
  } else {
    // returns the NULLBLOCK
    returned_block = NULLBLOCK;
  }
  // returns this memory block
  return returned_block;
}
// check is to block is same
int is_same_block(struct MB block, struct MB free_block) {
  if (block.SADDR == free_block.SADDR && block.EADDR == free_block.EADDR &&
      block.SS == free_block.SS && block.PID == free_block.PID)
    return 1;
  return 0;
}

void release_memory(struct MEMORY_BLOCK freed_block,
                    struct MEMORY_BLOCK memory_map[MAPMAX], int* map_cnt) {
  // marks the released block of memory as free
  for (int i = 0; i < (*map_cnt); i++)
    if (is_same_block(memory_map[i], freed_block))
      memory_map[i].PID = 0;

  struct MB temp_mmap[MAPMAX];

  int k = 0;
  // merges that block with adjacent free blocks
  for (int i = 0; i < (*map_cnt); i++) {
    if (memory_map[i].PID)
      temp_mmap[k++] = memory_map[i];
    else {
      int j = i + 1, l = memory_map[i].SADDR, r = memory_map[i].EADDR,
          ss = memory_map[i].SS;
      while (j < (*map_cnt) && !memory_map[j].PID) {
        r = memory_map[j].EADDR;
        ss += memory_map[j++].SS;
      }
      temp_mmap[k++] = (struct MB){l, r, ss, 0};
      i = j - 1;
    }
  }

  memcpy(memory_map, temp_mmap, sizeof(struct MB) * k);
  (*map_cnt) = k;
}