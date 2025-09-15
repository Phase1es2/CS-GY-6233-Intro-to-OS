#include <stdio.h>
#include <string.h>
#include "../Disk Scheduling/oslabs.h"

#define PID process_id
#define AT arrival_timestamp
#define TBT total_bursttime
#define EST execution_starttime
#define EET execution_endtime
#define RBT remaining_bursttime
#define PP process_priority

void set_pcb(struct PCB* inpcb, int pid, int at, int tbt, int est, int eet,
             int rbt, int pp) {
  (*inpcb).PID = pid;
  (*inpcb).AT = at;
  (*inpcb).TBT = tbt;
  (*inpcb).EST = est;
  (*inpcb).EET = eet;
  (*inpcb).RBT = rbt;
  (*inpcb).PP = pp;
}
void print_pcb(const char* label, struct PCB r) {
  printf("%s[PID: %d, AT: %d, TBT: %d, EST: %d, EET: %d, RBT: %d, PP: %d]\n",
         label, r.PID, r.AT, r.TBT, r.EST, r.EET, r.RBT, r.PP);
}

void print_queue(const char* label, struct PCB queue[], int queue_cnt) {
  if (queue_cnt == 0) {
    printf("%sEmpty queue!\n", label);
    return;
  }
  for (int i = 0; i < queue_cnt; i++) {
    char entry[64];
    snprintf(entry, sizeof(entry), "%s[%d] ", label, i);
    print_pcb(entry, queue[i]);
  }
  printf("%squeue_cnt: %d\n", label, queue_cnt);
}

void handle_process_arrival_pp_test() {
  struct PCB ready_queue[QUEUEMAX];
  struct PCB b1, current_process, new_process, returned_pcb;
  int queue_cnt = 0, timestamp = 2;
  set_pcb(&current_process, 1, 1, 4, 1, 5, 4, 8);
  set_pcb(&new_process, 2, 2, 3, 0, 0, 3, 6);

  returned_pcb = handle_process_arrival_pp(
      ready_queue, &queue_cnt, current_process, new_process, timestamp);

  print_queue("Q1 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");

  memset(ready_queue, 0, sizeof ready_queue);
  queue_cnt = 0;
  timestamp = 2;
  set_pcb(&current_process, 0, 0, 0, 0, 0, 0, 0);
  set_pcb(&new_process, 5, 2, 5, 0, 0, 5, 4);

  returned_pcb = handle_process_arrival_pp(
      ready_queue, &queue_cnt, current_process, new_process, timestamp);

  print_queue("Q2 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");

  memset(ready_queue, 0, sizeof ready_queue);
  queue_cnt = 0;
  timestamp = 4;

  set_pcb(&b1, 6, 3, 4, 0, 0, 4, 5);
  ready_queue[queue_cnt++] = b1;
  set_pcb(&current_process, 5, 2, 5, 2, 7, 3, 4);
  set_pcb(&new_process, 7, 4, 5, 0, 0, 5, 7);

  returned_pcb = handle_process_arrival_pp(
      ready_queue, &queue_cnt, current_process, new_process, timestamp);

  print_queue("Q3 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");
}

void handle_process_completion_pp_test() {
  struct PCB ready_queue[QUEUEMAX];
  struct PCB b1, b2, b3, b4, returned_pcb;

  int queue_cnt = 0;
  int timestamp = 2;

  set_pcb(&b1, 1, 1, 4, 0, 0, 4, 23);
  set_pcb(&b2, 2, 1, 4, 0, 0, 4, 22);
  set_pcb(&b3, 3, 1, 4, 0, 0, 4, 24);

  ready_queue[queue_cnt++] = b1;
  ready_queue[queue_cnt++] = b2;
  ready_queue[queue_cnt++] = b3;

  returned_pcb =
      handle_process_completion_pp(ready_queue, &queue_cnt, timestamp);

  print_queue("Q1 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");

  memset(ready_queue, 0, sizeof ready_queue);
  queue_cnt = 0;
  timestamp = 3;
  returned_pcb =
      handle_process_completion_pp(ready_queue, &queue_cnt, timestamp);

  print_queue("Q2 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");

  memset(ready_queue, 0, sizeof ready_queue);
  queue_cnt = 0;
  timestamp = 8;

  set_pcb(&b1, 6, 3, 4, 0, 0, 4, 5);
  set_pcb(&b2, 7, 4, 5, 0, 0, 5, 7);
  set_pcb(&b3, 8, 5, 6, 0, 0, 6, 3);
  set_pcb(&b4, 9, 7, 5, 0, 0, 5, 9);

  ready_queue[queue_cnt++] = b1;
  ready_queue[queue_cnt++] = b2;
  ready_queue[queue_cnt++] = b3;
  ready_queue[queue_cnt++] = b4;

  returned_pcb =
      handle_process_completion_pp(ready_queue, &queue_cnt, timestamp);

  print_queue("Q3 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");
}

void handle_process_arrival_srtp_test() {
  struct PCB ready_queue[QUEUEMAX];
  struct PCB b1, current_process, new_process, returned_pcb;
  int queue_cnt = 0, timestamp = 2;
  set_pcb(&current_process, 1, 1, 8, 1, 9, 8, 0);
  set_pcb(&new_process, 2, 2, 6, 0, 0, 6, 0);

  returned_pcb = handle_process_arrival_srtp(
      ready_queue, &queue_cnt, current_process, new_process, timestamp);

  print_queue("Q1 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");

  memset(ready_queue, 0, sizeof ready_queue);
  queue_cnt = 0;
  timestamp = 2;

  set_pcb(&current_process, 0, 0, 0, 0, 0, 0, 0);
  set_pcb(&new_process, 5, 2, 5, 0, 0, 5, 4);

  returned_pcb = handle_process_arrival_srtp(
      ready_queue, &queue_cnt, current_process, new_process, timestamp);

  print_queue("Q2 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");

  memset(ready_queue, 0, sizeof ready_queue);
  queue_cnt = 0;
  timestamp = 4;

  set_pcb(&current_process, 5, 2, 5, 2, 7, 3, 4);
  set_pcb(&new_process, 6, 4, 7, 0, 0, 7, 2);

  returned_pcb = handle_process_arrival_srtp(
      ready_queue, &queue_cnt, current_process, new_process, timestamp);

  print_queue("Q3 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");
}

void handle_process_completion_srtp_test() {
  struct PCB ready_queue[QUEUEMAX];
  struct PCB b1, b2, b3, b4, returned_pcb;

  int queue_cnt = 0;
  int timestamp = 2;

  set_pcb(&b1, 1, 1, 23, 0, 0, 23, 0);
  set_pcb(&b2, 2, 1, 22, 0, 0, 22, 0);
  set_pcb(&b3, 3, 1, 24, 0, 0, 24, 0);

  ready_queue[queue_cnt++] = b1;
  ready_queue[queue_cnt++] = b2;
  ready_queue[queue_cnt++] = b3;

  returned_pcb =
      handle_process_completion_srtp(ready_queue, &queue_cnt, timestamp);

  print_queue("Q1 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");

  memset(ready_queue, 0, sizeof ready_queue);
  queue_cnt = 0;
  timestamp = 3;

  returned_pcb =
      handle_process_completion_srtp(ready_queue, &queue_cnt, timestamp);

  print_queue("Q2 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");

  memset(ready_queue, 0, sizeof ready_queue);
  queue_cnt = 0;
  timestamp = 8;

  set_pcb(&b1, 6, 3, 4, 0, 0, 4, 5);
  set_pcb(&b2, 7, 4, 5, 0, 0, 5, 7);
  set_pcb(&b3, 8, 5, 6, 0, 0, 6, 3);
  set_pcb(&b4, 9, 7, 5, 0, 0, 5, 9);

  ready_queue[queue_cnt++] = b1;
  ready_queue[queue_cnt++] = b2;
  ready_queue[queue_cnt++] = b3;
  ready_queue[queue_cnt++] = b4;

  returned_pcb =
      handle_process_completion_srtp(ready_queue, &queue_cnt, timestamp);

  print_queue("Q3 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");
}

void handle_process_arrival_rr_test() {
  struct PCB ready_queue[QUEUEMAX];
  struct PCB b1, current_process, new_process, returned_pcb;
  int queue_cnt = 0, timestamp = 2, time_quantum = 6;

  set_pcb(&current_process, 1, 1, 8, 1, 9, 8, 0);
  set_pcb(&new_process, 2, 2, 8, 0, 0, 8, 0);

  returned_pcb =
      handle_process_arrival_rr(ready_queue, &queue_cnt, current_process,
                                new_process, timestamp, time_quantum);

  print_queue("Q1 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");

  memset(ready_queue, 0, sizeof ready_queue);
  queue_cnt = 0;
  timestamp = 2;
  time_quantum = 6;

  set_pcb(&current_process, 0, 0, 0, 0, 0, 0, 0);
  set_pcb(&new_process, 5, 2, 5, 0, 0, 5, 4);

  returned_pcb =
      handle_process_arrival_rr(ready_queue, &queue_cnt, current_process,
                                new_process, timestamp, time_quantum);

  print_queue("Q2 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");

  memset(ready_queue, 0, sizeof ready_queue);
  queue_cnt = 0;
  timestamp = 4;
  time_quantum = 6;

  set_pcb(&current_process, 5, 2, 5, 2, 7, 3, 4);
  set_pcb(&new_process, 6, 4, 7, 0, 0, 7, 2);

  returned_pcb =
      handle_process_arrival_rr(ready_queue, &queue_cnt, current_process,
                                new_process, timestamp, time_quantum);

  print_queue("Q3 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");
}

void handle_process_completion_rr_test() {
  struct PCB ready_queue[QUEUEMAX];
  struct PCB b1, b2, b3, b4, returned_pcb;

  int queue_cnt = 0;
  int timestamp = 24;
  int time_quantum = 10;

  set_pcb(&b1, 1, 22, 8, 0, 0, 8, 0);
  set_pcb(&b2, 2, 21, 8, 0, 0, 8, 0);
  set_pcb(&b3, 3, 23, 8, 0, 0, 8, 0);

  ready_queue[queue_cnt++] = b1;
  ready_queue[queue_cnt++] = b2;
  ready_queue[queue_cnt++] = b3;

  returned_pcb = handle_process_completion_rr(ready_queue, &queue_cnt,
                                              timestamp, time_quantum);

  print_queue("Q1 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");

  memset(ready_queue, 0, sizeof ready_queue);
  queue_cnt = 0;
  timestamp = 2;
  time_quantum = 6;

  returned_pcb = handle_process_completion_rr(ready_queue, &queue_cnt,
                                              timestamp, time_quantum);

  print_queue("Q2 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");

  memset(ready_queue, 0, sizeof ready_queue);
  queue_cnt = 0;
  timestamp = 12;
  time_quantum = 6;

  set_pcb(&b1, 6, 3, 4, 0, 0, 4, 5);
  set_pcb(&b2, 7, 4, 5, 0, 0, 5, 7);
  set_pcb(&b3, 8, 5, 6, 0, 0, 6, 3);
  set_pcb(&b4, 9, 7, 5, 0, 0, 5, 9);

  ready_queue[queue_cnt++] = b1;
  ready_queue[queue_cnt++] = b2;
  ready_queue[queue_cnt++] = b3;
  ready_queue[queue_cnt++] = b4;

  returned_pcb = handle_process_completion_rr(ready_queue, &queue_cnt,
                                              timestamp, time_quantum);

  print_queue("Q3 ", ready_queue, queue_cnt);
  print_pcb("Returned ", returned_pcb);
  puts("----------------------------------------------------------");
}
int main(int argc, char** argv) {

  if (argc < 2) {
    printf(
        "Usage: %s [arrival_pp | completion_pp | arrival_srtp | "
        "completion_srtp | arrival_rr | completion_rr]\n",
        argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "arrival_pp") == 0) {
    handle_process_arrival_pp_test();
  } else if (strcmp(argv[1], "completion_pp") == 0) {
    handle_process_completion_pp_test();
  } else if (strcmp(argv[1], "arrival_srtp") == 0) {
    handle_process_arrival_srtp_test();
  } else if (strcmp(argv[1], "completion_srtp") == 0) {
    handle_process_completion_srtp_test();
  } else if (strcmp(argv[1], "arrival_rr") == 0) {
    handle_process_arrival_rr_test();
  } else if (strcmp(argv[1], "completion_rr") == 0) {
    handle_process_completion_rr_test();
  } else {
    printf("Unknown test: %s\n", argv[1]);
    return 1;
  }

  return 0;
}
