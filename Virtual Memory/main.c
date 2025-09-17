#include <stdio.h>
#include <string.h>
#include "../Disk Scheduling/oslabs.h"

#define IV is_valid
#define FN frame_number
#define AT arrival_timestamp
#define LT last_access_timestamp
#define RC reference_count
struct PTE {
  int is_valid;
  int frame_number;
  int arrival_timestamp;
  int last_access_timestamp;
  int reference_count;
};
void set_pte(struct PTE* inpte, int is_valid, int frame_number,
             int arrival_timestamp, int last_access_timestamp,
             int reference_count) {
  (*inpte).IV = is_valid;
  (*inpte).FN = frame_number;
  (*inpte).AT = arrival_timestamp;
  (*inpte).LT = last_access_timestamp;
  (*inpte).RC = reference_count;
}

void print_pte(const char* label, struct PTE p) {
  printf("%s[IV: %d, FN: %d, AT: %d, LT: %d, RC: %d]\n", label, p.IV, p.FN,
         p.AT, p.LT, p.RC);
}

void print_table(const char* label, struct PTE page_table[], int table_cnt) {
  if (table_cnt == 0) {
    printf("%sEmpty Map!\n", label);
    return;
  }
  for (int i = 0; i < table_cnt; i++) {
    char entry[64];
    snprintf(entry, sizeof(entry), "%s[%d] ", label, i);
    print_pte(entry, page_table[i]);
  }
  printf("%stable_cnt: %d\n", label, table_cnt);
}

void process_page_access_fifo_test();
void count_page_faults_fifo_test();
void process_page_access_lru_test();
void count_page_faults_lru_test();
void process_page_access_lfu_test();
void count_page_faults_lfu_test();

int main(int argc, char** argv) {
  if (argc < 2) {
    printf(
        "Usage: %s [ppa_fifo | cpf_fifo | ppa_lru | "
        "cpf_lru | ppa_lfu | cpf_lfu]\n",
        argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "ppa_fifo") == 0) {
    handle_request_arrival_fcfs_test();
  } else if (strcmp(argv[1], "cpf_fifo") == 0) {
    handle_request_completion_fcfs_test();
  } else if (strcmp(argv[1], "ppa_lru") == 0) {
    handle_request_arrival_sstf_test();
  } else if (strcmp(argv[1], "cpf_lru") == 0) {
    handle_request_completion_sstf_test();
  } else if (strcmp(argv[1], "ppa_lfu") == 0) {
    handle_request_arrival_look_test();
  } else if (strcmp(argv[1], "cpf_lfu") == 0) {
    handle_request_completion_look_test();
  } else {
    printf("Unknown test: %s\n", argv[1]);
    return 1;
  }

  return 0;
}