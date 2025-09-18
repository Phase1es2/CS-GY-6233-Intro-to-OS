#include <limits.h>
#include <stdio.h>
#include "oslabs.h"
#define IV is_valid
#define FN frame_number
#define AT arrival_timestamp
#define LT last_access_timestamp
#define RC reference_count

struct PTE NULLPTE = {0, -1, -1, -1, -1};

int process_page_access_fifo(struct PTE page_table[TABLEMAX], int* table_cnt,
                             int page_number, int frame_pool[POOLMAX],
                             int* frame_cnt, int current_timestamp) {
  int fn = -1, idx = -1;
  // page is already in memory
  if (page_table[page_number].IV) {
    page_table[page_number].LT = current_timestamp;
    page_table[page_number].RC++;
    return page_table[page_number].FN;
  }

  if (fn == -1 && *frame_cnt) {
    fn = frame_pool[0];
    page_table[page_number] =
        (struct PTE){1, fn, current_timestamp, current_timestamp, 1};
    for (int i = 0; i + 1 < (*frame_cnt); i++)
      frame_pool[i] = frame_pool[i + 1];
    --(*frame_cnt);
  }

  if (!(*frame_cnt) && fn == -1) {
    int min_arr_time = INT_MAX;
    for (int i = 0; i < (*table_cnt); i++)
      if (page_table[i].IV && page_table[i].AT < min_arr_time) {
        idx = i;
        min_arr_time = page_table[i].AT;
      }
    page_table[page_number] = (struct PTE){
        1, page_table[idx].FN, current_timestamp, current_timestamp, 1};
    fn = page_table[idx].FN;
    page_table[idx] = NULLPTE;
  }

  return fn;
}

int count_page_faults_fifo(struct PTE page_table[TABLEMAX], int table_cnt,
                           int refrence_string[REFERENCEMAX], int reference_cnt,
                           int frame_pool[POOLMAX], int frame_cnt) {

  int ts = 1, faults = 0;

  for (int i = 0; i < table_cnt; i++)
    if (page_table[i].IV && page_table[i].AT >= ts)
      ts = page_table[i].AT + 1;

  for (int i = 0; i < reference_cnt; i++) {
    int v = refrence_string[i];

    if (page_table[v].IV) {
      page_table[v].LT = ts;
      page_table[v].RC++;
    } else {
      faults++;
      if (frame_cnt) {
        page_table[v] = (struct PTE){1, frame_pool[0], ts, ts, 1};
        for (int j = 0; j + 1 < frame_cnt; j++)
          frame_pool[j] = frame_pool[j + 1];

        --frame_cnt;
      } else {
        int idx = -1, at = INT_MAX;
        for (int j = 0; j < table_cnt; j++)
          if (page_table[j].IV && page_table[j].AT < at) {
            idx = j;
            at = page_table[j].AT;
          }
        int freed_frame = page_table[idx].FN;
        page_table[idx] = (struct PTE)NULLPTE;
        page_table[v] = (struct PTE){1, freed_frame, ts, ts, 1};
      }
    }
    ++ts;
  }
  return faults;
}

int process_page_access_lru(struct PTE page_table[TABLEMAX], int* table_cnt,
                            int page_number, int frame_pool[POOLMAX],
                            int* frame_cnt, int current_timestamp) {
  int idx = -1, fn = -1;
  if (page_table[page_number].IV) {
    page_table[page_number].LT = current_timestamp;
    page_table[page_number].RC++;
    return page_table[page_number].FN;
  }
  if (fn == -1 && (*frame_cnt)) {
    fn = frame_pool[0];
    page_table[page_number] =
        (struct PTE){1, fn, current_timestamp, current_timestamp, 1};
    for (int i = 0; i + 1 < (*frame_cnt); i++)
      frame_pool[i] = frame_pool[i + 1];
    --(*frame_cnt);
  }
  if (!(*frame_cnt) && fn == -1) {
    int min_rc = INT_MAX;

    int min_lt = INT_MAX;
    for (int i = 0; i < (*table_cnt); i++)
      if (page_table[i].IV && min_lt > page_table[i].LT) {
        idx = i;
        min_lt = page_table[i].LT;
      }

    page_table[page_number] = (struct PTE){
        1, page_table[idx].FN, current_timestamp, current_timestamp, 1};
    fn = page_table[idx].FN;
    page_table[idx] = NULLPTE;
  }
  return fn;
}
int count_page_faults_lru(struct PTE page_table[TABLEMAX], int table_cnt,
                          int refrence_string[REFERENCEMAX], int reference_cnt,
                          int frame_pool[POOLMAX], int frame_cnt) {
  int ts = 1, faults = 0;

  for (int i = 0; i < table_cnt; i++)
    if (page_table[i].IV && page_table[i].AT >= ts)
      ts = page_table[i].AT + 1;

  for (int i = 0; i < reference_cnt; i++) {
    int v = refrence_string[i];
    if (page_table[v].IV) {
      page_table[v].LT = ts;
      page_table[v].RC++;
    } else {
      faults++;
      if (frame_cnt) {
        page_table[v] = (struct PTE){1, frame_pool[0], ts, ts, 1};
        for (int j = 0; j + 1 < frame_cnt; j++)
          frame_pool[j] = frame_pool[j + 1];

        --frame_cnt;
      } else {
        int idx = -1, min_lt = INT_MAX;
        for (int j = 0; j < table_cnt; j++)
          if (page_table[j].IV && page_table[j].LT < min_lt) {
            idx = j;
            min_lt = page_table[j].LT;
          }
        int freed_frame = page_table[idx].FN;
        page_table[idx] = (struct PTE)NULLPTE;
        page_table[v] = (struct PTE){1, freed_frame, ts, ts, 1};
      }
    }
    ++ts;
  }
  return faults;
}
int process_page_access_lfu(struct PTE page_table[TABLEMAX], int* table_cnt,
                            int page_number, int frame_pool[POOLMAX],
                            int* frame_cnt, int current_timestamp) {
  int idx = -1, fn = -1;
  if (page_table[page_number].IV) {
    page_table[page_number].LT = current_timestamp;
    page_table[page_number].RC++;
    return page_table[page_number].FN;
  }
  if (fn == -1 && (*frame_cnt)) {
    fn = frame_pool[0];
    page_table[page_number] =
        (struct PTE){1, fn, current_timestamp, current_timestamp, 1};
    for (int i = 0; i + 1 < (*frame_cnt); i++)
      frame_pool[i] = frame_pool[i + 1];
    --(*frame_cnt);
  }
  if (!(*frame_cnt) && fn == -1) {
    int min_rc = INT_MAX, min_at = INT_MAX;

    for (int i = 0; i < (*table_cnt); i++) {
      if (!page_table[i].IV)
        continue;
      if (page_table[i].RC < min_rc ||
          page_table[i].RC == min_rc && page_table[i].AT < min_at) {

        idx = i;
        min_rc = page_table[i].RC;
        min_at = page_table[i].AT;
      }
    }
    page_table[page_number] = (struct PTE){
        1, page_table[idx].FN, current_timestamp, current_timestamp, 1};
    fn = page_table[idx].FN;
    page_table[idx] = NULLPTE;
  }
  return fn;
}
int count_page_faults_lfu(struct PTE page_table[TABLEMAX], int table_cnt,
                          int refrence_string[REFERENCEMAX], int reference_cnt,
                          int frame_pool[POOLMAX], int frame_cnt) {
  int ts = 1, faults = 0;

  for (int i = 0; i < table_cnt; i++)
    if (page_table[i].IV && page_table[i].AT >= ts)
      ts = page_table[i].AT + 1;

  for (int i = 0; i < reference_cnt; i++) {
    int v = refrence_string[i];

    if (page_table[v].IV) {
      page_table[v].LT = ts;
      page_table[v].RC++;
    } else {
      faults++;
      if (frame_cnt) {
        page_table[v] = (struct PTE){1, frame_pool[0], ts, ts, 1};
        for (int j = 0; j + 1 < frame_cnt; j++)
          frame_pool[j] = frame_pool[j + 1];

        --frame_cnt;
      } else {
        int idx = -1, at = INT_MAX, rc = INT_MAX;
        for (int j = 0; j < table_cnt; j++) {
          if (!page_table[j].IV)
            continue;
          if (page_table[j].RC < rc ||
              page_table[j].RC == rc && page_table[j].AT < at) {
            idx = j;
            at = page_table[j].AT;
            rc = page_table[j].RC;
          }
        }
        int freed_frame = page_table[idx].FN;
        page_table[idx] = (struct PTE)NULLPTE;
        page_table[v] = (struct PTE){1, freed_frame, ts, ts, 1};
      }
    }
    ++ts;
  }
  return faults;
}