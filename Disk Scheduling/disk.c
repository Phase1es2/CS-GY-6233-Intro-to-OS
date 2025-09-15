#include <stdio.h>
#include <string.h>
#include "oslabs.h"

#define RID request_id
#define AT arrival_timestamp
#define CYL cylinder
#define ADDR address
#define PID process_id

struct RCB NULLRCB = {0, 0, 0, 0, 0};

int check_disk_free(struct RCB current_request) {
  if (current_request.RID == NULLRCB.RID && current_request.AT == NULLRCB.AT &&
      current_request.CYL == NULLRCB.CYL &&
      current_request.ADDR == NULLRCB.ADDR &&
      current_request.PID == NULLRCB.PID)
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
    if (request_queue[i].AT < request_queue[idx].AT)
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
