#include <stdio.h>
#include "oslabs.h"
#define PID process_id
#define AT arrival_timestamp
#define TB total_bursttime
#define ES execution_starttime
#define EE execution_endtime
#define RB remaining_bursttime
#define PP process_priority

//NULLPCB is defined as [PID:0, AT:0, TBT:0, EST:0, EET:0, RBT:0, Priority:0]
struct PCB NULLPCB = {[0, 0, 0, 0, 0, 0, 0]};

int check_exited_process(struct PCB inpcb) {
  if (inpcb.PID == NULLPCB.PID && inpcb.AT == NULLPCB.AT &&
      inpcb.TB == NULLPCB.TB && inpcb.ES == NULLPCB.ES &&
      inpcb.EE == NULLPCB.EE && inpcb.RB == NULLPCB.RB &&
      inpcb.PP == NULLPCB.PP)
    return 1;

  return 0;
}

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX],
                                     int* queue_cnt, struct PCB current_process,
                                     struct PCB new_process, int timestamp) {}
struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX],
                                        int* queue_cnt, int timestamp) {}
struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX],
                                       int* queue_cnt,
                                       struct PCB current_process,
                                       struct PCB new_process, int time_stamp) {
}
struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX],
                                          int* queue_cnt, int timestamp);
struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX],
                                     int* queue_cnt, struct PCB current_process,
                                     struct PCB new_process, int timestamp,
                                     int time_quantum) {}
struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX],
                                        int* queue_cnt, int timestamp,
                                        int time_quantum) {}