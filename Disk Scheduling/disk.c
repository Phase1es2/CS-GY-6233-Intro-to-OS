#include <stdio.h>
#include <string.h>
#include "oslabs.h"

struct RCB NULLRCB = {0, 0, 0, 0, 0};

void setup_rcb(struct RCB* intrcb, int request_id, int arrival_timestamp,
               int cylinder, int address, int process_id) {
  (*intrcb).request_id = request_id;
  (*intrcb).arrival_timestamp = arrival_timestamp;
  (*intrcb).cylinder = cylinder;
  (*intrcb).address = address;
  (*intrcb).process_id = process_id;
}

int check_disk_free(struct RCB current_request) {
  if (current_request.request_id == NULLRCB.request_id &&
      current_request.arrival_timestamp == NULLRCB.arrival_timestamp &&
      current_request.cylinder == NULLRCB.cylinder &&
      current_request.address == NULLRCB.address &&
      current_request.address == NULLRCB.address)
    return 1;
  return 0;
}

struct RCB handle_request_arrival_fcfs(struct RCB request_queue[QUEUEMAX],
                                       int* queue_cnt,
                                       struct RCB current_request,
                                       struct RCB new_request, int timestamp) {
  if (check_disk_free(current_request))
    return new_request;
  else
    request_queue[(*queue_cnt)++] = new_request;
  return current_request;
}
struct RCB handle_request_completion_fcfs(struct RCB request_queue[QUEUEMAX],
                                          int* queue_cnt) {
  if (!*queue_cnt)
    return NULLRCB;
  int idx = 0;
  for (int i = 1; i < *queue_cnt; i++)
    if (request_queue[i].arrival_timestamp <
        request_queue[idx].arrival_timestamp)
      i = idx;
  struct RCB returned_rcb = request_queue[idx];

  for (int i = idx; i < *queue_cnt; i++)
    request_queue[i] = request_queue[i + 1];

  --(*queue_cnt);
  return returned_rcb;
}

struct RCB handle_request_arrival_sstf(struct RCB request_queue[QUEUEMAX],
                                       int* queue_cnt,
                                       struct RCB current_request,
                                       struct RCB new_request, int timestamp) {}
struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX],
                                          int* queue_cnt,
                                          int current_cylinder) {}
struct RCB handle_request_arrival_look(struct RCB request_queue[QUEUEMAX],
                                       int* queue_cnt,
                                       struct RCB current_request,
                                       struct RCB new_request, int timestamp) {}
struct RCB handle_request_completion_look(struct RCB request_queue[QUEUEMAX],
                                          int* queue_cnt, int current_cylinder,
                                          int scan_direction) {}
