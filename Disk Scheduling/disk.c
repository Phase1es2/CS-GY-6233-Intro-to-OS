#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oslabs.h"

#define RID request_id
#define AT arrival_timestamp
#define CYL cylinder
#define ADDR address
#define PID process_id

struct RCB NULLRCB = {0, 0, 0, 0, 0};

// helper to check if disk is free
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
  // returns the RCB of the newly-arriving request if the disk is free
  if (check_disk_free(current_request))
    return new_request;
  else
    request_queue[(*queue_cnt)++] = new_request;
  // returns the RCB of the currently-serviced request
  //after adding the newly-arriving request to the request queue.
  return current_request;
}
struct RCB handle_request_completion_fcfs(struct RCB request_queue[QUEUEMAX],
                                          int* queue_cnt) {
  // equest queue is empty, the method returns a NULLRCB
  if (!*queue_cnt)
    return NULLRCB;

  // the method finds the RCB in the request queue that has the earliest arrival time
  int idx = 0;
  for (int i = 1; i < *queue_cnt; i++)
    if (request_queue[i].AT < request_queue[idx].AT)
      i = idx;
  struct RCB returned_rcb = request_queue[idx];

  // then removes this RCB from the request queue and returns it.
  for (int i = idx; i < *queue_cnt; i++)
    request_queue[i] = request_queue[i + 1];

  --(*queue_cnt);
  return returned_rcb;
}

struct RCB handle_request_arrival_sstf(struct RCB request_queue[QUEUEMAX],
                                       int* queue_cnt,
                                       struct RCB current_request,
                                       struct RCB new_request, int timestamp) {
  // returns the RCB of the newly-arriving request if the disk is free
  if (check_disk_free(current_request))
    return new_request;
  else
    request_queue[(*queue_cnt)++] = new_request;
  // returns the RCB of the currently-serviced request
  //after adding the newly-arriving request to the request queue.
  return current_request;
}

struct RCB handle_request_completion_sstf(struct RCB request_queue[QUEUEMAX],
                                          int* queue_cnt,
                                          int current_cylinder) {
  // request queue is empty, the method returns NULLRCB
  if (!(*queue_cnt))
    return NULLRCB;
  // finds the RCB in the request queue whose cylinder is closest to the current cylinder.
  int idx = 0, diff_cyl = INT_MAX, temp_cyl = INT_MAX;

  for (int i = 0; i < (*queue_cnt); i++) {
    temp_cyl = abs(request_queue[i].CYL - current_cylinder);
    //  multiple requests with the closest cylinder
    // picks the request that has the earliest arrival_timestamp
    if (diff_cyl > temp_cyl ||
        (diff_cyl == temp_cyl && request_queue[i].AT < request_queue[i].AT)) {
      idx = i;
      diff_cyl = temp_cyl;
    }
  }

  struct RCB returned_rcb = request_queue[idx];

  // removes the RCB of the selected request from the request queue and returns it
  for (int i = idx; i + 1 < (*queue_cnt); i++)
    request_queue[i] = request_queue[i + 1];
  --(*queue_cnt);

  return returned_rcb;
}

struct RCB handle_request_arrival_look(struct RCB request_queue[QUEUEMAX],
                                       int* queue_cnt,
                                       struct RCB current_request,
                                       struct RCB new_request, int timestamp) {
  // returns the RCB of the newly-arriving request if the disk is free
  if (check_disk_free(current_request))
    return new_request;
  else
    request_queue[(*queue_cnt)++] = new_request;
  // returns the RCB of the currently-serviced request
  //after adding the newly-arriving request to the request queue.
  return current_request;
}

struct RCB handle_request_completion_look(struct RCB request_queue[QUEUEMAX],
                                          int* queue_cnt, int current_cylinder,
                                          int scan_direction) {
  // request queue is empty, the method returns NULLRCB
  if (*queue_cnt == 0)
    return NULLRCB;

  int idx = -1;
  int diff_cyl = INT_MAX;

  // If requests in the queue with the same cylinder as the current cylinder
  // the method picks the one with the earliest arrival time.
  for (int i = 0; i < *queue_cnt; i++)
    if (request_queue[i].CYL == current_cylinder)
      if (idx == -1 || request_queue[i].AT < request_queue[idx].AT)
        idx = i;

  if (idx == -1)
    for (int i = 0; i < *queue_cnt; i++) {
      int temp_cyl = request_queue[i].CYL - current_cylinder;
      // if the scan direction is 1 and there are requests with cylinders larger than the current cylinder
      // or f the scan direction is 0 and there are requests with cylinders smaller than the current cylinder
      if ((scan_direction && temp_cyl > 0) ||
          (!scan_direction && temp_cyl < 0)) {
        temp_cyl = abs(temp_cyl);
        if (temp_cyl < diff_cyl) {
          diff_cyl = temp_cyl;
          idx = i;
        }
      }
    }
  // no match
  // the method picks the request whose cylinder is closest to the current cylinder.
  if (idx == -1)
    for (int i = 0; i < *queue_cnt; i++) {
      int temp_cyl = abs(request_queue[i].CYL - current_cylinder);
      if (temp_cyl < diff_cyl) {
        diff_cyl = temp_cyl;
        idx = i;
      }
    }

  struct RCB returned_rcb = request_queue[idx];

  // removes the RCB from the queue and returns it.

  for (int i = idx; i < *queue_cnt - 1; i++)
    request_queue[i] = request_queue[i + 1];

  --(*queue_cnt);

  return returned_rcb;
}
