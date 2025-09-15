#include <stdio.h>
#include "../Disk Scheduling/oslabs.h"
#define IV is_valid
#define FN frame_number
#define ATT arrival_timestamp
#define LATT last_access_timestamp
#define RC reference_count

int process_page_access_fifo(struct PTE page_table[TABLEMAX], int* table_cnt,
                             int page_number, int frame_pool[POOLMAX],
                             int* frame_cnt, int current_timestamp);
int count_page_faults_fifo(struct PTE page_table[TABLEMAX], int table_cnt,
                           int refrence_string[REFERENCEMAX], int reference_cnt,
                           int frame_pool[POOLMAX], int frame_cnt);
int process_page_access_lru(struct PTE page_table[TABLEMAX], int* table_cnt,
                            int page_number, int frame_pool[POOLMAX],
                            int* frame_cnt, int current_timestamp);
int count_page_faults_lru(struct PTE page_table[TABLEMAX], int table_cnt,
                          int refrence_string[REFERENCEMAX], int reference_cnt,
                          int frame_pool[POOLMAX], int frame_cnt);
int process_page_access_lfu(struct PTE page_table[TABLEMAX], int* table_cnt,
                            int page_number, int frame_pool[POOLMAX],
                            int* frame_cnt, int current_timestamp);
int count_page_faults_lfu(struct PTE page_table[TABLEMAX], int table_cnt,
                          int refrence_string[REFERENCEMAX], int reference_cnt,
                          int frame_pool[POOLMAX], int frame_cnt);