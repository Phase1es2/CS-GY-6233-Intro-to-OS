#include <stdio.h>
#include <string.h>
#include "oslabs.h"

void setup_rcb(struct RCB* intrcb, int request_id, int arrival_timestamp,
               int cylinder, int address, int process_id) {
  (*intrcb).request_id = request_id;
  (*intrcb).arrival_timestamp = arrival_timestamp;
  (*intrcb).cylinder = cylinder;
  (*intrcb).address = address;
  (*intrcb).process_id = process_id;
}

void print_rcb(const char* label, struct RCB r) {
  printf("%s[RID: %d, AT: %d, CYL: %d, ADDR: %d, PID: %d]\n", label,
         r.request_id, r.arrival_timestamp, r.cylinder, r.address,
         r.process_id);
}

void print_queue(const char* label, struct RCB queue[], int queue_cnt) {
  if (queue_cnt == 0) {
    printf("%sEmpty queue!\n", label);
    return;
  }
  for (int i = 0; i < queue_cnt; i++) {
    char entry[64];
    snprintf(entry, sizeof(entry), "%s[%d] ", label, i);
    print_rcb(entry, queue[i]);
  }
  printf("%squeue_cnt: %d\n", label, queue_cnt);
}

void handle_request_arrival_fcfs_test() {
  struct RCB request_queue[QUEUEMAX];
  struct RCB current_request, new_request, returned_rcb;
  int timestamp, queue_cnt;

  printf("=========== Test for handle_request_arrival_fcfs ===========\n");

  // ---- Test 1 ----
  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  timestamp = 2;
  setup_rcb(&current_request, 51, 1, 53, 53, 51);
  setup_rcb(&new_request, 52, 2, 54, 54, 52);

  returned_rcb = handle_request_arrival_fcfs(
      request_queue, &queue_cnt, current_request, new_request, timestamp);

  print_queue("Q1 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  // ---- Test 2 ----
  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  timestamp = 3;
  setup_rcb(&current_request, 52, 2, 54, 54, 52);
  setup_rcb(&new_request, 53, 3, 45, 60, 53);

  returned_rcb = handle_request_arrival_fcfs(
      request_queue, &queue_cnt, current_request, new_request, timestamp);

  print_queue("Q2 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  // ---- Test 3 ----
  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  timestamp = 3;
  struct RCB b1;
  setup_rcb(&b1, 51, 2, 53, 53, 51);
  request_queue[queue_cnt++] = b1;
  setup_rcb(&current_request, 50, 1, 52, 52, 50);
  setup_rcb(&new_request, 52, 3, 54, 54, 52);

  returned_rcb = handle_request_arrival_fcfs(
      request_queue, &queue_cnt, current_request, new_request, timestamp);

  print_queue("Q3 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("==========================================================");
}

void handle_request_completion_fcfs_test() {
  struct RCB request_queue[QUEUEMAX];
  struct RCB current_request, returned_rcb;
  int queue_cnt;

  printf("=========== Test for handle_request_completion_fcfs =========\n");

  // ---- Test 1 ----
  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  setup_rcb(&current_request, 1, 10, 124323, 124323, 1);
  request_queue[queue_cnt++] = current_request;

  returned_rcb = handle_request_completion_fcfs(request_queue, &queue_cnt);
  print_queue("Q1 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  // ---- Test 2 ----
  struct RCB r1, r2, r3;
  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  setup_rcb(&r1, 4, 2, 53, 53, 4);
  setup_rcb(&r2, 5, 3, 54, 54, 5);
  setup_rcb(&r3, 6, 5, 51, 59, 6);
  request_queue[queue_cnt++] = r1;
  request_queue[queue_cnt++] = r2;
  request_queue[queue_cnt++] = r3;

  returned_rcb = handle_request_completion_fcfs(request_queue, &queue_cnt);
  print_queue("Q2 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  // ---- Test 3 ----
  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  setup_rcb(&r1, 51, 2, 53, 53, 51);
  setup_rcb(&r2, 52, 3, 54, 54, 52);
  request_queue[queue_cnt++] = r1;
  request_queue[queue_cnt++] = r2;

  returned_rcb = handle_request_completion_fcfs(request_queue, &queue_cnt);
  print_queue("Q3 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("==========================================================");
}

void handle_request_arrival_sstf_test() {
  struct RCB request_queue[QUEUEMAX];
  struct RCB current_request, new_request, returned_rcb;
  int timestamp, queue_cnt;

  setup_rcb(&current_request, 51, 1, 53, 53, 51);
  setup_rcb(&new_request, 52, 2, 54, 54, 52);

  timestamp = 2;

  returned_rcb = handle_request_arrival_sstf(
      request_queue, &queue_cnt, current_request, new_request, timestamp);

  print_queue("Q1 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  memset(request_queue, 0, sizeof request_queue);

  queue_cnt = 0;
  setup_rcb(&current_request, 52, 2, 54, 54, 52);
  setup_rcb(&new_request, 53, 3, 45, 60, 53);
  timestamp = 3;

  returned_rcb = handle_request_arrival_sstf(
      request_queue, &queue_cnt, current_request, new_request, timestamp);

  print_queue("Q2 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  struct RCB r1;
  setup_rcb(&r1, 51, 2, 53, 53, 51);
  request_queue[queue_cnt++] = r1;

  setup_rcb(&current_request, 50, 1, 52, 52, 50);
  setup_rcb(&new_request, 52, 3, 54, 54, 52);
  timestamp = 3;

  returned_rcb = handle_request_arrival_sstf(
      request_queue, &queue_cnt, current_request, new_request, timestamp);

  print_queue("Q3 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");
}

void handle_request_completion_sstf_test() {
  struct RCB request_queue[QUEUEMAX];
  struct RCB r1, r2, r3, r4, returned_rcb;
  int timestamp, queue_cnt = 0, current_cylinder;

  setup_rcb(&r1, 1, 72, 45, 45, 1);
  setup_rcb(&r2, 2, 71, 47, 47, 2);
  setup_rcb(&r3, 3, 73, 43, 43, 3);
  request_queue[queue_cnt++] = r1;
  request_queue[queue_cnt++] = r2;
  request_queue[queue_cnt++] = r3;

  current_cylinder = 48;
  returned_rcb = handle_request_completion_sstf(request_queue, &queue_cnt,
                                                current_cylinder);
  print_queue("Q1 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  setup_rcb(&r1, 4, 2, 53, 53, 4);
  setup_rcb(&r2, 5, 3, 54, 54, 5);
  setup_rcb(&r3, 6, 5, 51, 59, 6);
  request_queue[queue_cnt++] = r1;
  request_queue[queue_cnt++] = r2;
  request_queue[queue_cnt++] = r3;

  current_cylinder = 57;
  returned_rcb = handle_request_completion_sstf(request_queue, &queue_cnt,
                                                current_cylinder);

  print_queue("Q2 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  setup_rcb(&r1, 51, 1, 90, 53, 51);
  setup_rcb(&r2, 52, 3, 15, 54, 52);
  setup_rcb(&r3, 53, 4, 45, 55, 53);
  setup_rcb(&r4, 54, 7, 28, 56, 54);
  request_queue[queue_cnt++] = r1;
  request_queue[queue_cnt++] = r2;
  request_queue[queue_cnt++] = r3;
  request_queue[queue_cnt++] = r4;
  current_cylinder = 25;

  returned_rcb = handle_request_completion_sstf(request_queue, &queue_cnt,
                                                current_cylinder);

  print_queue("Q3 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");
}

void handle_request_arrival_look_test() {
  struct RCB request_queue[QUEUEMAX];
  struct RCB r1, current_request, new_request, returned_rcb;
  int timestamp, queue_cnt;
  timestamp = 2;

  setup_rcb(&current_request, 51, 1, 53, 53, 51);
  setup_rcb(&new_request, 52, 2, 54, 54, 52);

  returned_rcb = handle_request_arrival_look(
      request_queue, &queue_cnt, current_request, new_request, timestamp);

  print_queue("Q1 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  setup_rcb(&current_request, 52, 2, 54, 54, 52);
  setup_rcb(&new_request, 53, 3, 45, 60, 53);
  timestamp = 3;

  returned_rcb = handle_request_arrival_look(
      request_queue, &queue_cnt, current_request, new_request, timestamp);

  print_queue("Q2 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  setup_rcb(&r1, 51, 2, 53, 53, 51);
  request_queue[queue_cnt++] = r1;

  setup_rcb(&current_request, 50, 1, 52, 52, 10);
  setup_rcb(&new_request, 52, 3, 54, 54, 52);
  timestamp = 3;

  returned_rcb = handle_request_arrival_look(
      request_queue, &queue_cnt, current_request, new_request, timestamp);

  print_queue("Q3 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");
}

void handle_request_completion_look_test() {
  struct RCB request_queue[QUEUEMAX];
  struct RCB r1, r2, r3, r4, returned_rcb;
  int timestamp, queue_cnt = 0, current_cylinder, scan_direction;

  setup_rcb(&r1, 1, 52, 58, 58, 1);
  setup_rcb(&r2, 2, 51, 58, 58, 2);
  setup_rcb(&r3, 3, 53, 58, 58, 3);
  request_queue[queue_cnt++] = r1;
  request_queue[queue_cnt++] = r2;
  request_queue[queue_cnt++] = r3;
  current_cylinder = 58;
  scan_direction = 1;

  returned_rcb = handle_request_completion_look(
      request_queue, &queue_cnt, current_cylinder, scan_direction);

  print_queue("Q1 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  setup_rcb(&r1, 51, 1, 90, 53, 51);
  setup_rcb(&r2, 52, 3, 15, 54, 52);
  setup_rcb(&r3, 53, 4, 45, 55, 53);
  setup_rcb(&r4, 54, 7, 28, 56, 54);
  request_queue[queue_cnt++] = r1;
  request_queue[queue_cnt++] = r2;
  request_queue[queue_cnt++] = r3;
  request_queue[queue_cnt++] = r4;
  current_cylinder = 27;
  scan_direction = 0;

  returned_rcb = handle_request_completion_look(
      request_queue, &queue_cnt, current_cylinder, scan_direction);

  print_queue("Q2 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  setup_rcb(&r1, 51, 1, 90, 53, 51);
  setup_rcb(&r2, 52, 3, 57, 54, 52);
  setup_rcb(&r3, 53, 4, 45, 55, 53);
  setup_rcb(&r4, 54, 7, 28, 56, 54);
  request_queue[queue_cnt++] = r1;
  request_queue[queue_cnt++] = r2;
  request_queue[queue_cnt++] = r3;
  request_queue[queue_cnt++] = r4;
  current_cylinder = 27;
  scan_direction = 0;

  returned_rcb = handle_request_completion_look(
      request_queue, &queue_cnt, current_cylinder, scan_direction);

  print_queue("Q3 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  setup_rcb(&r1, 51, 1, 90, 53, 51);
  setup_rcb(&r2, 52, 3, 57, 54, 52);
  setup_rcb(&r3, 53, 4, 45, 55, 53);
  setup_rcb(&r4, 54, 7, 28, 56, 54);
  request_queue[queue_cnt++] = r1;
  request_queue[queue_cnt++] = r2;
  request_queue[queue_cnt++] = r3;
  request_queue[queue_cnt++] = r4;
  current_cylinder = 80;
  scan_direction = 1;

  returned_rcb = handle_request_completion_look(
      request_queue, &queue_cnt, current_cylinder, scan_direction);

  print_queue("Q4 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");

  memset(request_queue, 0, sizeof request_queue);
  queue_cnt = 0;
  setup_rcb(&r1, 51, 1, 20, 53, 51);
  setup_rcb(&r2, 52, 3, 57, 54, 52);
  setup_rcb(&r3, 53, 4, 45, 55, 53);
  setup_rcb(&r4, 54, 7, 28, 56, 54);
  request_queue[queue_cnt++] = r1;
  request_queue[queue_cnt++] = r2;
  request_queue[queue_cnt++] = r3;
  request_queue[queue_cnt++] = r4;
  current_cylinder = 80;
  scan_direction = 1;

  returned_rcb = handle_request_completion_look(
      request_queue, &queue_cnt, current_cylinder, scan_direction);

  print_queue("Q5 ", request_queue, queue_cnt);
  print_rcb("Returned ", returned_rcb);
  puts("----------------------------------------------------------");
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf(
        "Usage: %s [fcfs_arrival | fcfs_completion | sstf_arrival | "
        "sstf_completion | look_arrival | look_completion]\n",
        argv[0]);
    return 1;
  }

  if (strcmp(argv[1], "fcfs_arrival") == 0) {
    handle_request_arrival_fcfs_test();
  } else if (strcmp(argv[1], "fcfs_completion") == 0) {
    handle_request_completion_fcfs_test();
  } else if (strcmp(argv[1], "sstf_arrival") == 0) {
    handle_request_arrival_sstf_test();
  } else if (strcmp(argv[1], "sstf_completion") == 0) {
    handle_request_completion_sstf_test();
  } else if (strcmp(argv[1], "look_arrival") == 0) {
    handle_request_arrival_look_test();
  } else if (strcmp(argv[1], "look_completion") == 0) {
    handle_request_completion_look_test();
  } else {
    printf("Unknown test: %s\n", argv[1]);
    return 1;
  }

  return 0;
}