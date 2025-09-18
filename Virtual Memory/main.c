#include <stdio.h>
#include <string.h>
#include "../Disk Scheduling/oslabs.h"

#define IV is_valid
#define FN frame_number
#define AT arrival_timestamp
#define LT last_access_timestamp
#define RC reference_count

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

void print_frame(const char* label, int frame_pool[], int frame_cnt) {
  if (frame_cnt == 0) {
    printf("%sEmpty Frame Pool!\n", label);
    return;
  }
  printf("%sFrame Pool (count=%d): ", label, frame_cnt);
  for (int i = 0; i < frame_cnt; i++) {
    printf("%d ", frame_pool[i]);
  }
  putchar('\n');
}

void process_page_access_fifo_test() {
  struct PTE p1, p2, p3, p4, p5, p6, p7, p8;
  struct PTE page_table[TABLEMAX];
  int frame_pool[POOLMAX];
  int f1, f2, f3, f4, f5, f6, f7, f8;
  int table_cnt, page_num, frame_cnt, current_timestamp, res;

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 1, 10, 3, 3, 1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 2, 4, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 1, 1, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  page_num = 0;
  frame_cnt = 0;
  current_timestamp = 12;

  res = process_page_access_fifo(page_table, &table_cnt, page_num, frame_pool,
                                 &frame_cnt, current_timestamp);

  print_table("Q1 ", page_table, table_cnt);
  if (frame_cnt) {
    print_frame("Q1 ", frame_pool, frame_cnt);
  } else {
    printf("Q1 Frame Pool is empty.\n");
  }
  printf("Q1 frame number %d\n", res);
  puts("----------------------------------------------------------");

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 1, 10, 3, 3, 1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 2, 4, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 1, 1, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  page_num = 2;
  frame_cnt = 0;
  current_timestamp = 14;

  res = process_page_access_fifo(page_table, &table_cnt, page_num, frame_pool,
                                 &frame_cnt, current_timestamp);

  print_table("Q2 ", page_table, table_cnt);
  if (frame_cnt) {
    print_frame("Q2 ", frame_pool, frame_cnt);
  } else {
    printf("Q2 Frame Pool is empty.\n");
  }
  printf("Q2 frame number %d\n", res);
  puts("----------------------------------------------------------");

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 0, -1, -1, -1, -1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 2, 4, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 1, 1, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  page_num = 3;

  frame_cnt = 0;
  f1 = 10;
  frame_pool[frame_cnt++] = f1;

  current_timestamp = 15;

  res = process_page_access_fifo(page_table, &table_cnt, page_num, frame_pool,
                                 &frame_cnt, current_timestamp);

  print_table("Q3 ", page_table, table_cnt);
  if (frame_cnt) {
    print_frame("Q3 ", frame_pool, frame_cnt);
  } else {
    printf("Q3 Frame Pool is empty.\n");
  }
  printf("Q3 frame number %d\n", res);
  puts("----------------------------------------------------------");

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 0, -1, -1, -1, -1);
  set_pte(&p4, 1, 10, 15, 15, 1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 12, 16, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 14, 14, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  page_num = 2;

  frame_cnt = 0;

  current_timestamp = 17;

  res = process_page_access_fifo(page_table, &table_cnt, page_num, frame_pool,
                                 &frame_cnt, current_timestamp);

  print_table("Q4 ", page_table, table_cnt);
  if (frame_cnt) {
    print_frame("Q4 ", frame_pool, frame_cnt);
  } else {
    printf("Q4 Frame Pool is empty.\n");
  }
  printf("Q4 frame number %d\n", res);
  puts("----------------------------------------------------------");
}

void count_page_faults_fifo_test() {
  struct PTE p1, p2, p3, p4, p5, p6, p7, p8;
  struct PTE page_table[TABLEMAX];
  int refrence_string[REFERENCEMAX];
  int r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12;
  int frame_pool[POOLMAX];
  int f1, f2, f3, f4, f5, f6, f7, f8;

  int table_cnt, page_num, frame_cnt, current_timestamp, res, refer_cnt, faults;

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);
  memset(refrence_string, 0, sizeof refrence_string);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 0, -1, -1, -1, -1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 0, -1, -1, -1, -1);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 0, -1, -1, -1, -1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  refer_cnt = 0;
  r1 = 0, r2 = 3, r3 = 2, r4 = 6, r5 = 3, r6 = 4, r7 = 5, r8 = 2, r9 = 4,
  r10 = 5, r11 = 7;
  refrence_string[refer_cnt++] = r1;
  refrence_string[refer_cnt++] = r2;
  refrence_string[refer_cnt++] = r3;
  refrence_string[refer_cnt++] = r4;
  refrence_string[refer_cnt++] = r5;
  refrence_string[refer_cnt++] = r6;
  refrence_string[refer_cnt++] = r7;
  refrence_string[refer_cnt++] = r8;
  refrence_string[refer_cnt++] = r9;
  refrence_string[refer_cnt++] = r10;
  refrence_string[refer_cnt++] = r11;

  // page_num = 0;
  frame_cnt = 0;
  f1 = 0, f2 = 1, f3 = 2;
  frame_pool[frame_cnt++] = f1;
  frame_pool[frame_cnt++] = f2;
  frame_pool[frame_cnt++] = f3;

  // current_timestamp = 12;

  faults = count_page_faults_fifo(page_table, table_cnt, refrence_string,
                                  refer_cnt, frame_pool, frame_cnt);
  printf("Q1 page faults: %d\n", faults);
  puts("----------------------------------------------------------");

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);
  memset(refrence_string, 0, sizeof refrence_string);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 1, 10, 3, 3, 1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 2, 4, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 1, 1, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  refer_cnt = 0;
  r1 = 2, r2 = 5, r3 = 0, r4 = 7, r5 = 4, r6 = 2, r7 = 3, r8 = 5, r9 = 1,
  r10 = 2, r11 = 6, r12 = 0;
  refrence_string[refer_cnt++] = r1;
  refrence_string[refer_cnt++] = r2;
  refrence_string[refer_cnt++] = r3;
  refrence_string[refer_cnt++] = r4;
  refrence_string[refer_cnt++] = r5;
  refrence_string[refer_cnt++] = r6;
  refrence_string[refer_cnt++] = r7;
  refrence_string[refer_cnt++] = r8;
  refrence_string[refer_cnt++] = r9;
  refrence_string[refer_cnt++] = r10;
  refrence_string[refer_cnt++] = r11;
  refrence_string[refer_cnt++] = r12;

  // page_num = 0;
  frame_cnt = 0;

  // current_timestamp = 12;

  faults = count_page_faults_fifo(page_table, table_cnt, refrence_string,
                                  refer_cnt, frame_pool, frame_cnt);
  printf("Q2 page faults: %d\n", faults);
  puts("----------------------------------------------------------");
}

void process_page_access_lru_test() {
  struct PTE p1, p2, p3, p4, p5, p6, p7, p8;
  struct PTE page_table[TABLEMAX];
  int frame_pool[POOLMAX];
  int f1, f2, f3, f4, f5, f6, f7, f8;
  int table_cnt, page_num, frame_cnt, current_timestamp, res;

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 1, 10, 3, 3, 1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 2, 4, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 1, 1, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  page_num = 0;
  frame_cnt = 0;
  current_timestamp = 12;

  res = process_page_access_lru(page_table, &table_cnt, page_num, frame_pool,
                                &frame_cnt, current_timestamp);

  print_table("Q1 ", page_table, table_cnt);
  if (frame_cnt) {
    print_frame("Q1 ", frame_pool, frame_cnt);
  } else {
    printf("Q1 Frame Pool is empty.\n");
  }
  printf("Q1 frame number %d\n", res);
  puts("----------------------------------------------------------");

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 1, 10, 3, 3, 1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 2, 4, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 1, 1, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  page_num = 2;
  frame_cnt = 0;
  current_timestamp = 14;

  res = process_page_access_lru(page_table, &table_cnt, page_num, frame_pool,
                                &frame_cnt, current_timestamp);

  print_table("Q2 ", page_table, table_cnt);
  if (frame_cnt) {
    print_frame("Q2 ", frame_pool, frame_cnt);
  } else {
    printf("Q2 Frame Pool is empty.\n");
  }
  printf("Q2 frame number %d\n", res);
  puts("----------------------------------------------------------");

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 0, -1, -1, -1, -1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 2, 4, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 1, 1, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  page_num = 3;

  frame_cnt = 0;
  f1 = 10;
  frame_pool[frame_cnt++] = f1;

  current_timestamp = 15;

  res = process_page_access_lru(page_table, &table_cnt, page_num, frame_pool,
                                &frame_cnt, current_timestamp);

  print_table("Q3 ", page_table, table_cnt);
  if (frame_cnt) {
    print_frame("Q3 ", frame_pool, frame_cnt);
  } else {
    printf("Q3 Frame Pool is empty.\n");
  }
  printf("Q3 frame number %d\n", res);
  puts("----------------------------------------------------------");

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 0, -1, -1, -1, -1);
  set_pte(&p4, 1, 10, 15, 15, 1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 12, 16, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 14, 14, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  page_num = 2;

  frame_cnt = 0;

  current_timestamp = 17;

  res = process_page_access_lru(page_table, &table_cnt, page_num, frame_pool,
                                &frame_cnt, current_timestamp);

  print_table("Q4 ", page_table, table_cnt);
  if (frame_cnt) {
    print_frame("Q4 ", frame_pool, frame_cnt);
  } else {
    printf("Q4 Frame Pool is empty.\n");
  }
  printf("Q4 frame number %d\n", res);
  puts("----------------------------------------------------------");
}

void count_page_faults_lru_test() {
  struct PTE p1, p2, p3, p4, p5, p6, p7, p8;
  struct PTE page_table[TABLEMAX];
  int refrence_string[REFERENCEMAX];
  int r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12;
  int frame_pool[POOLMAX];
  int f1, f2, f3, f4, f5, f6, f7, f8;

  int table_cnt, page_num, frame_cnt, current_timestamp, res, refer_cnt, faults;

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);
  memset(refrence_string, 0, sizeof refrence_string);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 0, -1, -1, -1, -1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 0, -1, -1, -1, -1);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 0, -1, -1, -1, -1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  refer_cnt = 0;
  r1 = 0, r2 = 3, r3 = 2, r4 = 6, r5 = 3, r6 = 4, r7 = 5, r8 = 2, r9 = 4,
  r10 = 6, r11 = 5;
  refrence_string[refer_cnt++] = r1;
  refrence_string[refer_cnt++] = r2;
  refrence_string[refer_cnt++] = r3;
  refrence_string[refer_cnt++] = r4;
  refrence_string[refer_cnt++] = r5;
  refrence_string[refer_cnt++] = r6;
  refrence_string[refer_cnt++] = r7;
  refrence_string[refer_cnt++] = r8;
  refrence_string[refer_cnt++] = r9;
  refrence_string[refer_cnt++] = r10;
  refrence_string[refer_cnt++] = r11;

  // page_num = 0;
  frame_cnt = 0;
  f1 = 0, f2 = 1, f3 = 2;
  frame_pool[frame_cnt++] = f1;
  frame_pool[frame_cnt++] = f2;
  frame_pool[frame_cnt++] = f3;

  // current_timestamp = 12;

  faults = count_page_faults_lru(page_table, table_cnt, refrence_string,
                                 refer_cnt, frame_pool, frame_cnt);
  printf("Q1 page faults: %d\n", faults);
  puts("----------------------------------------------------------");

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);
  memset(refrence_string, 0, sizeof refrence_string);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 1, 10, 3, 3, 1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 2, 4, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 1, 1, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  refer_cnt = 0;
  r1 = 2, r2 = 5, r3 = 0, r4 = 2, r5 = 5, r6 = 2, r7 = 3, r8 = 5, r9 = 1,
  r10 = 2, r11 = 6, r12 = 0;
  refrence_string[refer_cnt++] = r1;
  refrence_string[refer_cnt++] = r2;
  refrence_string[refer_cnt++] = r3;
  refrence_string[refer_cnt++] = r4;
  refrence_string[refer_cnt++] = r5;
  refrence_string[refer_cnt++] = r6;
  refrence_string[refer_cnt++] = r7;
  refrence_string[refer_cnt++] = r8;
  refrence_string[refer_cnt++] = r9;
  refrence_string[refer_cnt++] = r10;
  refrence_string[refer_cnt++] = r11;
  refrence_string[refer_cnt++] = r12;

  // page_num = 0;
  frame_cnt = 0;

  // current_timestamp = 12;

  faults = count_page_faults_lru(page_table, table_cnt, refrence_string,
                                 refer_cnt, frame_pool, frame_cnt);
  printf("Q2 page faults: %d\n", faults);
  puts("----------------------------------------------------------");
}

void process_page_access_lfu_test() {
  struct PTE p1, p2, p3, p4, p5, p6, p7, p8;
  struct PTE page_table[TABLEMAX];
  int frame_pool[POOLMAX];
  int f1, f2, f3, f4, f5, f6, f7, f8;
  int table_cnt, page_num, frame_cnt, current_timestamp, res;

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 1, 10, 3, 3, 1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 2, 4, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 1, 1, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  page_num = 0;
  frame_cnt = 0;
  current_timestamp = 12;

  res = process_page_access_lfu(page_table, &table_cnt, page_num, frame_pool,
                                &frame_cnt, current_timestamp);

  print_table("Q1 ", page_table, table_cnt);
  if (frame_cnt) {
    print_frame("Q1 ", frame_pool, frame_cnt);
  } else {
    printf("Q1 Frame Pool is empty.\n");
  }
  printf("Q1 frame number %d\n", res);
  puts("----------------------------------------------------------");

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 1, 10, 3, 3, 1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 2, 4, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 1, 1, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  page_num = 2;
  frame_cnt = 0;
  current_timestamp = 14;

  res = process_page_access_lfu(page_table, &table_cnt, page_num, frame_pool,
                                &frame_cnt, current_timestamp);

  print_table("Q2 ", page_table, table_cnt);
  if (frame_cnt) {
    print_frame("Q2 ", frame_pool, frame_cnt);
  } else {
    printf("Q2 Frame Pool is empty.\n");
  }
  printf("Q2 frame number %d\n", res);
  puts("----------------------------------------------------------");

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 0, -1, -1, -1, -1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 2, 4, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 1, 1, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  page_num = 3;

  frame_cnt = 0;
  f1 = 10;
  frame_pool[frame_cnt++] = f1;

  current_timestamp = 15;

  res = process_page_access_lfu(page_table, &table_cnt, page_num, frame_pool,
                                &frame_cnt, current_timestamp);

  print_table("Q3 ", page_table, table_cnt);
  if (frame_cnt) {
    print_frame("Q3 ", frame_pool, frame_cnt);
  } else {
    printf("Q3 Frame Pool is empty.\n");
  }
  printf("Q3 frame number %d\n", res);
  puts("----------------------------------------------------------");

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 0, -1, -1, -1, -1);
  set_pte(&p4, 1, 10, 15, 15, 1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 12, 16, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 14, 17, 4);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  page_num = 2;

  frame_cnt = 0;

  current_timestamp = 17;

  res = process_page_access_lfu(page_table, &table_cnt, page_num, frame_pool,
                                &frame_cnt, current_timestamp);

  print_table("Q4 ", page_table, table_cnt);
  if (frame_cnt) {
    print_frame("Q4 ", frame_pool, frame_cnt);
  } else {
    printf("Q4 Frame Pool is empty.\n");
  }
  printf("Q4 frame number %d\n", res);
  puts("----------------------------------------------------------");
}

void count_page_faults_lfu_test() {

  struct PTE p1, p2, p3, p4, p5, p6, p7, p8;
  struct PTE page_table[TABLEMAX];
  int refrence_string[REFERENCEMAX];
  int r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12;
  int frame_pool[POOLMAX];
  int f1, f2, f3, f4, f5, f6, f7, f8;

  int table_cnt, page_num, frame_cnt, current_timestamp, res, refer_cnt, faults;

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);
  memset(refrence_string, 0, sizeof refrence_string);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 0, -1, -1, -1, -1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 0, -1, -1, -1, -1);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 0, -1, -1, -1, -1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  refer_cnt = 0;
  r1 = 0, r2 = 3, r3 = 2, r4 = 6, r5 = 3, r6 = 4, r7 = 5, r8 = 2, r9 = 6,
  r10 = 4, r11 = 5;
  refrence_string[refer_cnt++] = r1;
  refrence_string[refer_cnt++] = r2;
  refrence_string[refer_cnt++] = r3;
  refrence_string[refer_cnt++] = r4;
  refrence_string[refer_cnt++] = r5;
  refrence_string[refer_cnt++] = r6;
  refrence_string[refer_cnt++] = r7;
  refrence_string[refer_cnt++] = r8;
  refrence_string[refer_cnt++] = r9;
  refrence_string[refer_cnt++] = r10;
  refrence_string[refer_cnt++] = r11;

  // page_num = 0;
  frame_cnt = 0;
  f1 = 0, f2 = 1, f3 = 2;
  frame_pool[frame_cnt++] = f1;
  frame_pool[frame_cnt++] = f2;
  frame_pool[frame_cnt++] = f3;

  // current_timestamp = 12;

  faults = count_page_faults_lfu(page_table, table_cnt, refrence_string,
                                 refer_cnt, frame_pool, frame_cnt);
  printf("Q1 page faults: %d\n", faults);
  puts("----------------------------------------------------------");

  memset(page_table, 0, sizeof page_table);
  memset(frame_pool, 0, sizeof frame_pool);
  memset(refrence_string, 0, sizeof refrence_string);

  set_pte(&p1, 0, -1, -1, -1, -1);
  set_pte(&p2, 0, -1, -1, -1, -1);
  set_pte(&p3, 1, 10, 3, 3, 1);
  set_pte(&p4, 0, -1, -1, -1, -1);
  set_pte(&p5, 0, -1, -1, -1, -1);
  set_pte(&p6, 1, 20, 2, 4, 2);
  set_pte(&p7, 0, -1, -1, -1, -1);
  set_pte(&p8, 1, 30, 1, 1, 1);
  table_cnt = 0;

  page_table[table_cnt++] = p1;
  page_table[table_cnt++] = p2;
  page_table[table_cnt++] = p3;
  page_table[table_cnt++] = p4;
  page_table[table_cnt++] = p5;
  page_table[table_cnt++] = p6;
  page_table[table_cnt++] = p7;
  page_table[table_cnt++] = p8;

  refer_cnt = 0;
  r1 = 2, r2 = 5, r3 = 0, r4 = 2, r5 = 5, r6 = 2, r7 = 3, r8 = 5, r9 = 1,
  r10 = 2, r11 = 6, r12 = 0;
  refrence_string[refer_cnt++] = r1;
  refrence_string[refer_cnt++] = r2;
  refrence_string[refer_cnt++] = r3;
  refrence_string[refer_cnt++] = r4;
  refrence_string[refer_cnt++] = r5;
  refrence_string[refer_cnt++] = r6;
  refrence_string[refer_cnt++] = r7;
  refrence_string[refer_cnt++] = r8;
  refrence_string[refer_cnt++] = r9;
  refrence_string[refer_cnt++] = r10;
  refrence_string[refer_cnt++] = r11;
  refrence_string[refer_cnt++] = r12;

  // page_num = 0;
  frame_cnt = 0;

  // current_timestamp = 12;

  faults = count_page_faults_lfu(page_table, table_cnt, refrence_string,
                                 refer_cnt, frame_pool, frame_cnt);
  printf("Q2 page faults: %d\n", faults);
  puts("----------------------------------------------------------");
}

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