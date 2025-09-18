#include <limits.h>
#include <stdio.h>
#include "oslabs.h"
#define IV is_valid
#define FN frame_number
#define AT arrival_timestamp
#define LT last_access_timestamp
#define RC reference_count

// set default PTE as [is_valid: 0, FN: -1, AT: -1, LT: -1, RC: -1];
struct PTE NULLPTE = {0, -1, -1, -1, -1};

int process_page_access_fifo(struct PTE page_table[TABLEMAX], int* table_cnt,
                             int page_number, int frame_pool[POOLMAX],
                             int* frame_cnt, int current_timestamp) {
  int fn = -1, idx = -1;
  // page is already in memory
  if (page_table[page_number].IV) {
    // modifying the last_access_timestamp and the reference_count
    page_table[page_number].LT = current_timestamp;
    page_table[page_number].RC++;
    // returns the frame number
    return page_table[page_number].FN;
  }
  // if there are any free frames
  if (fn == -1 && *frame_cnt) {
    // inserted into the page-table entry corresponding to the logical page number
    fn = frame_pool[0];
    page_table[page_number] =
        (struct PTE){1, fn, current_timestamp, current_timestamp, 1};

    // frame is removed from the process frame pool
    for (int i = 0; i + 1 < (*frame_cnt); i++)
      frame_pool[i] = frame_pool[i + 1];
    --(*frame_cnt);
  }
  // not in memory and there are no free frames for the process
  if (!(*frame_cnt) && fn == -1) {
    int min_arr_time = INT_MAX;
    // find the page that has the smallest arrival_timestamp.
    for (int i = 0; i < (*table_cnt); i++)
      if (page_table[i].IV && page_table[i].AT < min_arr_time) {
        idx = i;
        min_arr_time = page_table[i].AT;
      }
    // sets the frame_number of the page-table entry of the newly-referenced page
    // sets the arrival_timestamp, the last_access_timestamp and the reference_count fields of the page-table entry
    page_table[page_number] = (struct PTE){
        1, page_table[idx].FN, current_timestamp, current_timestamp, 1};
    fn = page_table[idx].FN;
    // marks that page_table entry as NULLPTE
    page_table[idx] = NULLPTE;
  }
  // return frame number
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
    // if the page being referenced is already in memory
    if (page_table[v].IV) {
      // modifies the last_access_timestamp and _count fields of the page-table entry
      page_table[v].LT = ts;
      page_table[v].RC++;
    } else {
      // function counts this page access as a page fault
      faults++;
      // checks if there are any free frames
      if (frame_cnt) {
        // the frame number is inserted into the page-table entry
        page_table[v] = (struct PTE){1, frame_pool[0], ts, ts, 1};
        // removed from the process frame pool
        for (int j = 0; j + 1 < frame_cnt; j++)
          frame_pool[j] = frame_pool[j + 1];

        --frame_cnt;
      } else {
        int idx = -1, at = INT_MAX;
        // selects the process that are currently in memory
        // and the page that has the smallest access_timestamp
        for (int j = 0; j < table_cnt; j++)
          if (page_table[j].IV && page_table[j].AT < at) {
            idx = j;
            at = page_table[j].AT;
          }
        int freed_frame = page_table[idx].FN;
        // sets the frame_number, arrival_timestamp, last_access_timestamp and reference_count to -1
        page_table[idx] = (struct PTE)NULLPTE;
        // sets the frame_number of the page-table entry to the newly freed frame
        // sets the arrival_timestamp, the last_access_timestamp and the reference_count
        page_table[v] = (struct PTE){1, freed_frame, ts, ts, 1};
      }
    }
    // increase the timestamp;
    ++ts;
  }
  // return page faults
  return faults;
}

int process_page_access_lru(struct PTE page_table[TABLEMAX], int* table_cnt,
                            int page_number, int frame_pool[POOLMAX],
                            int* frame_cnt, int current_timestamp) {
  int idx = -1, fn = -1;
  // page is already in memory
  if (page_table[page_number].IV) {
    // modifying the last_access_timestamp and the reference_count
    page_table[page_number].LT = current_timestamp;
    page_table[page_number].RC++;
    // returns the frame number
    return page_table[page_number].FN;
  }
  // if there are any free frames
  if (fn == -1 && (*frame_cnt)) {
    // inserted into the page-table entry corresponding to the logical page number
    fn = frame_pool[0];
    page_table[page_number] =
        (struct PTE){1, fn, current_timestamp, current_timestamp, 1};
    // frame is removed from the process frame pool
    for (int i = 0; i + 1 < (*frame_cnt); i++)
      frame_pool[i] = frame_pool[i + 1];
    --(*frame_cnt);
  }
  // not in memory and there are no free frames for the process
  if (!(*frame_cnt) && fn == -1) {
    int min_rc = INT_MAX;
    int min_lt = INT_MAX;
    // find the page that has the smallest last_access_timestamp
    for (int i = 0; i < (*table_cnt); i++)
      if (page_table[i].IV && min_lt > page_table[i].LT) {
        idx = i;
        min_lt = page_table[i].LT;
      }
    // sets the frame_number of the page-table entry of the newly-referenced page
    // sets the arrival_timestamp, the last_access_timestamp and the reference_count fields of the page-table entry
    page_table[page_number] = (struct PTE){
        1, page_table[idx].FN, current_timestamp, current_timestamp, 1};
    fn = page_table[idx].FN;
    // marks that page_table entry as NULLPTE
    page_table[idx] = NULLPTE;
  }
  // returns the frame number
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
    // if the page being referenced is already in memory
    if (page_table[v].IV) {
      // modifies the last_access_timestamp and _count fields of the page-table entry
      page_table[v].LT = ts;
      page_table[v].RC++;
    } else {
      // function counts this page access as a page fault
      faults++;
      // checks if there are any free frames
      if (frame_cnt) {
        // the frame number is inserted into the page-table entry
        page_table[v] = (struct PTE){1, frame_pool[0], ts, ts, 1};
        // removed from the process frame pool
        for (int j = 0; j + 1 < frame_cnt; j++)
          frame_pool[j] = frame_pool[j + 1];

        --frame_cnt;
      } else {
        int idx = -1, min_lt = INT_MAX;
        // selects the process that are currently in memory
        // and the page that has the smallest last_access_timestamp
        for (int j = 0; j < table_cnt; j++)
          if (page_table[j].IV && page_table[j].LT < min_lt) {
            idx = j;
            min_lt = page_table[j].LT;
          }
        int freed_frame = page_table[idx].FN;
        // sets the frame_number, arrival_timestamp, last_access_timestamp and reference_count to -1
        page_table[idx] = (struct PTE)NULLPTE;
        // sets the frame_number of the page-table entry to the newly freed frame
        // sets the arrival_timestamp, the last_access_timestamp and the reference_count
        page_table[v] = (struct PTE){1, freed_frame, ts, ts, 1};
      }
    }
    // increase the timestamp;
    ++ts;
  }
  // return page faults
  return faults;
}
int process_page_access_lfu(struct PTE page_table[TABLEMAX], int* table_cnt,
                            int page_number, int frame_pool[POOLMAX],
                            int* frame_cnt, int current_timestamp) {
  int idx = -1, fn = -1;
  // page is already in memory
  if (page_table[page_number].IV) {
    // modifying the last_access_timestamp and the reference_count
    page_table[page_number].LT = current_timestamp;
    page_table[page_number].RC++;
    // returns the frame number
    return page_table[page_number].FN;
  }
  // if there are any free frames
  if (fn == -1 && (*frame_cnt)) {
    // inserted into the page-table entry corresponding to the logical page number
    fn = frame_pool[0];
    page_table[page_number] =
        (struct PTE){1, fn, current_timestamp, current_timestamp, 1};
    // find the page that has the smallest last_access_timestamp
    for (int i = 0; i + 1 < (*frame_cnt); i++)
      frame_pool[i] = frame_pool[i + 1];
    --(*frame_cnt);
  }
  // not in memory and there are no free frames for the process
  if (!(*frame_cnt) && fn == -1) {
    int min_rc = INT_MAX, min_at = INT_MAX;
    // find the page that has the smallest reference_count
    // If multiple pages have the smallest reference_count
    // the one with the smallest arrival_timestamp
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
    // sets the frame_number of the page-table entry of the newly-referenced page
    // sets the arrival_timestamp, the last_access_timestamp and the reference_count fields of the page-table entry
    page_table[page_number] = (struct PTE){
        1, page_table[idx].FN, current_timestamp, current_timestamp, 1};
    fn = page_table[idx].FN;
    // marks that page_table entry as NULLPTE
    page_table[idx] = NULLPTE;
  }
  // returns the frame number
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
    // if the page being referenced is already in memory
    if (page_table[v].IV) {
      // modifies the last_access_timestamp and _count fields of the page-table entry
      page_table[v].LT = ts;
      page_table[v].RC++;
    } else {
      // function counts this page access as a page fault
      faults++;
      // checks if there are any free frames
      if (frame_cnt) {
        // the frame number is inserted into the page-table entry
        page_table[v] = (struct PTE){1, frame_pool[0], ts, ts, 1};
        // removed from the process frame pool
        for (int j = 0; j + 1 < frame_cnt; j++)
          frame_pool[j] = frame_pool[j + 1];

        --frame_cnt;
      } else {
        int idx = -1, at = INT_MAX, rc = INT_MAX;
        // selects the process that are currently in memory
        // and the page that has the smallest reference_count
        // If multiple pages have the smallest reference_count
        // select the smallest arrival_timestamp
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
        // sets the frame_number, arrival_timestamp, last_access_timestamp and reference_count to -1
        page_table[idx] = (struct PTE)NULLPTE;
        // sets the frame_number of the page-table entry to the newly freed frame
        // sets the arrival_timestamp, the last_access_timestamp and the reference_count
        page_table[v] = (struct PTE){1, freed_frame, ts, ts, 1};
      }
    }
    // increase the timestamp;
    ++ts;
  }
  // return page faults
  return faults;
}