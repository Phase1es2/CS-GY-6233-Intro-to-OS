# Memory Management Lab

This lab project focuses on implementing **memory–management schemes** in an operating system.

---

## Overview

The operating system manages main memory as a list of **memory blocks**.  
Each block is represented by a data structure:

```c
struct MEMORY_BLOCK {
    int start_address;
    int end_address;
    int segment_size;
    int process_id;   // 0 indicates a free block
};
```

- `start_address` – Starting address of the memory segment  
- `end_address` – Ending address of the memory segment  
- `segment_size` – Size of the memory segment in bytes  
- `process_id` – ID of the process that owns this block (0 means free)

The **Memory Map** is an array of `MEMORY_BLOCK` structures that represents the current state of memory.  
The **NULLBLOCK** is defined as:

```c
[start_address:0, end_address:0, segment_size:0, process_id:0]
```

As processes request and release memory, the memory map is updated by splitting, merging, and reassigning blocks.

---

## Allocation Schemes Implemented

This lab covers four allocation schemes and one release function:

1. **Best Fit Allocation**
2. **First Fit Allocation**
3. **Worst (Largest) Fit Allocation**
4. **Next Fit Allocation**
5. **Release Memory**

Each function is implemented in `memory.c` and uses the header file `oslabs.h`.

---

### 1. Best Fit Allocation

**best_fit_allocate**

```c
struct MEMORY_BLOCK best_fit_allocate(
    int request_size,
    struct MEMORY_BLOCK memory_map[MAPMAX],
    int *map_cnt,
    int process_id
);
```

- Scans all free blocks and selects the **smallest** block that is at least as large as the request.
- If the block size matches the request exactly:
  - Update `process_id` and return the allocated block.
- If the block is larger:
  - Split it into an allocated block and a smaller free block.
  - Update the memory map and `map_cnt`.
- If no block can satisfy the request:
  - Return `NULLBLOCK`.

**Example Input**

```
memory_map: [start:0, end:1023, size:1024, pid:0]
map_cnt:    1
request_size: 10
process_id: 32
```

**Example Output**

```
memory_map:
  [start:0, end:9,   size:10,  pid:32],
  [start:10,end:1023,size:1014,pid:0]
map_cnt:    2
return:     [start:0, end:9, size:10, pid:32]
```

---

### 2. First Fit Allocation

**first_fit_allocate**

```c
struct MEMORY_BLOCK first_fit_allocate(
    int request_size,
    struct MEMORY_BLOCK memory_map[MAPMAX],
    int *map_cnt,
    int process_id
);
```

- Scans from the **beginning of memory** and selects the first free block large enough to satisfy the request.
- Splitting and return behavior are the same as in Best Fit.

---

### 3. Worst Fit Allocation

**worst_fit_allocate**

```c
struct MEMORY_BLOCK worst_fit_allocate(
    int request_size,
    struct MEMORY_BLOCK memory_map[MAPMAX],
    int *map_cnt,
    int process_id
);
```

- Scans all free blocks and selects the **largest** block that can satisfy the request.
- Splitting and return behavior are the same as in Best Fit.

---

### 4. Next Fit Allocation

**next_fit_allocate**

```c
struct MEMORY_BLOCK next_fit_allocate(
    int request_size,
    struct MEMORY_BLOCK memory_map[MAPMAX],
    int *map_cnt,
    int process_id,
    int last_address
);
```

- Scans memory starting **from the last allocated address** (wrapping to the beginning if necessary).
- Selects the first free block large enough to satisfy the request.
- Splitting and return behavior are the same as in Best Fit.

---

### 5. Release Memory

**release_memory**

```c
void release_memory(
    struct MEMORY_BLOCK freed_block,
    struct MEMORY_BLOCK memory_map[MAPMAX],
    int *map_cnt
);
```

- Marks the specified block as free (`process_id = 0`).
- **Merges** adjacent free blocks into a single larger block when possible.
- Updates `map_cnt` to reflect the new memory map.

**Example Input**

```
memory_map:
  [start:0, end:7,  size:8,  pid:12],
  [start:8, end:15, size:8,  pid:0 ],
  [start:16,end:23, size:8,  pid:13],
  [start:24,end:27, size:4,  pid:0 ],
  [start:28,end:29, size:2,  pid:11]
map_cnt:    5
freed_block:[start:16,end:23,size:8,pid:13]
```

**Example Output**

```
memory_map:
  [start:0, end:7,  size:8,  pid:12],
  [start:8, end:27, size:20, pid:0 ],
  [start:28,end:29, size:2,  pid:11]
map_cnt:    3
```

---

## References

- Modern Operating Systems (Andrew S. Tanenbaum), Section 3.2 – *Memory Allocation Algorithms*
