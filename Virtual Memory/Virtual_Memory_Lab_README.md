# Virtual Memory Lab

This lab project focuses on implementing **page-replacement algorithms**
in a demand-paging system.

## Overview

Each process in a demand-paging system maintains a **page table**, which
tracks logical-to-physical page mappings and metadata. The page table is
an array of page-table entries (PTEs):

``` c
struct PTE {
    int is_valid;
    int frame_number;
    int arrival_timestamp;
    int last_access_timestamp;
    int reference_count;
};
```

-   `is_valid` -- Indicates if the page is currently in memory\
-   `frame_number` -- Frame number where the page resides\
-   `arrival_timestamp` -- Time when the page was brought into memory\
-   `last_access_timestamp` -- Time when the page was last referenced\
-   `reference_count` -- Number of references since arrival

Each process also has a **frame pool** (array of integers) representing
free memory frames available for allocation.

## Page Replacement Policies Implemented

This lab implements three page-replacement algorithms:

1.  **First-In-First-Out (FIFO)**
2.  **Least-Recently-Used (LRU)**
3.  **Least-Frequently-Used (LFU)**

For each policy, two main functions are implemented:

-   **process_page_access\_`<policy>`{=html}** -- Handles a single page
    access, updating the page table and returning the frame number.
-   **count_page_faults\_`<policy>`{=html}** -- Simulates a sequence of
    page references and returns the total number of page faults.

## Function Specifications

Below are summaries of the key functions. Full details and sample
inputs/outputs are in the project documentation.

### 1. FIFO

``` c
int process_page_access_fifo(struct PTE page_table[TABLEMAX], int *table_cnt,
    int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp);
```

``` c
int count_page_faults_fifo(struct PTE page_table[TABLEMAX], int table_cnt,
    int reference_string[REFERENCEMAX], int reference_cnt,
    int frame_pool[POOLMAX], int frame_cnt);
```

Implements First-In-First-Out replacement, evicting the page with the
smallest arrival_timestamp when no free frames are available.

### 2. LRU

``` c
int process_page_access_lru(struct PTE page_table[TABLEMAX], int *table_cnt,
    int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp);
```

``` c
int count_page_faults_lru(struct PTE page_table[TABLEMAX], int table_cnt,
    int reference_string[REFERENCEMAX], int reference_cnt,
    int frame_pool[POOLMAX], int frame_cnt);
```

Implements Least-Recently-Used replacement, evicting the page with the
smallest last_access_timestamp.

### 3. LFU

``` c
int process_page_access_lfu(struct PTE page_table[TABLEMAX], int *table_cnt,
    int page_number, int frame_pool[POOLMAX], int *frame_cnt, int current_timestamp);
```

``` c
int count_page_faults_lfu(struct PTE page_table[TABLEMAX], int table_cnt,
    int reference_string[REFERENCEMAX], int reference_cnt,
    int frame_pool[POOLMAX], int frame_cnt);
```

Implements Least-Frequently-Used replacement, evicting the page with the
smallest reference_count (breaking ties with arrival_timestamp).

## References

For a detailed discussion of these algorithms, refer to **Section 3.4 of
the Modern Operating Systems** textbook.
