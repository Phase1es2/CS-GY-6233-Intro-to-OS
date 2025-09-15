#include <stdio.h>
#include "../Disk Scheduling/oslabs.h"
#define PID process_id
#define AT arrival_timestamp
#define TBT total_bursttime
#define EST execution_starttime
#define EET execution_endtime
#define RBT remaining_bursttime
#define PP process_priority

// NULLPCB is defined as [PID:0, AT:0, TBT:0, EST:0, EET:0, RBT:0, Priority:0]
struct PCB NULLPCB = {0, 0, 0, 0, 0, 0, 0};

// helper to compare if an inpcb is NULLPCB
int check_exited_process(struct PCB inpcb) {
  if (inpcb.PID == NULLPCB.PID && inpcb.AT == NULLPCB.AT &&
      inpcb.TBT == NULLPCB.TBT && inpcb.EST == NULLPCB.EST &&
      inpcb.EET == NULLPCB.EET && inpcb.RBT == NULLPCB.RBT &&
      inpcb.PP == NULLPCB.PP)
    return 1;

  return 0;
}

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX],
                                     int* queue_cnt, struct PCB current_process,
                                     struct PCB new_process, int timestamp) {
  if (check_exited_process(current_process)) {
    // the new process is modified so that the execution start time is set to the current timestamp
    new_process.EST = timestamp;
    // execution end time is set to the sum of the current timestamp and total burst time
    new_process.EET = timestamp + new_process.TBT;
    // the remaining burst time is set to the total burst time
    new_process.RBT = new_process.TBT;
    return new_process;
  } else if (current_process.PP <= new_process.PP) {
    // its execution start time and execution end time are set to 0
    new_process.EST = 0;
    new_process.EET = 0;
    // the remaining burst time is the same as its total burst time.
    new_process.RBT = new_process.TBT;
    // added to the ready queue
    ready_queue[(*queue_cnt)++] = new_process;
    // return value is the PCB of the currently-running process
    return current_process;
  } else {
    // new process is modified so that the execution start time is set to the current timestamp
    new_process.EST = timestamp;
    // execution end time is set to the sum of the current timestamp and the total burst time
    new_process.EET = timestamp + new_process.TBT;
    // remaining burst time is set to the total burst time
    new_process.RBT = new_process.TBT;
    // currently-running process is added to the ready queue

    // the PCB of the currently-running process is added to the ready queue
    // after marking its execution end time as 0, and adjusting its remaining burst time.
    current_process.EET = 0;
    current_process.RBT -= timestamp - current_process.EST;
    ready_queue[(*queue_cnt)++] = current_process;
    // return value is the PCB of the new process
    return new_process;
  }
}

struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX],
                                        int* queue_cnt, int timestamp) {
  // queue is empty, the method returns the NULLPCB
  if (!(*queue_cnt))
    return NULLPCB;

  // idx for returned_pcb
  int idx = 0;
  // finds the PCB of the process in the ready queue with the highest priority
  for (int i = 0; i < (*queue_cnt); i++)
    if (ready_queue[i].PP < ready_queue[idx].PP)
      idx = i;

  struct PCB returned_pcb = ready_queue[idx];
  // removes this PCB from the ready queue
  for (int i = idx; i + 1 < (*queue_cnt); i++)
    ready_queue[i] = ready_queue[i + 1];
  --(*queue_cnt);

  // execution start time as the current timestamp and the execution end time
  // as the sum of the current timestamp and the remaining burst time
  returned_pcb.EST = timestamp;
  returned_pcb.EET = timestamp + returned_pcb.RBT;

  return returned_pcb;
}
struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX],
                                       int* queue_cnt,
                                       struct PCB current_process,
                                       struct PCB new_process, int time_stamp) {
  // If there is no currently-running process
  if (check_exited_process(current_process)) {
    // execution start time is set to the current timestamp
    new_process.EST = time_stamp;
    // execution end time is set to the sum of the current timestamp
    new_process.EET = time_stamp + new_process.TBT;
    // the remaining burst time is set to the total burst time
    new_process.RBT = new_process.TBT;
    // returns the PCB of the newly-arriving process
    return new_process;
    // If tcurrently-running process
    // compares the remaining burst time of the currently-running process
    // and the total burst time of the newly-arriving process
  } else if (current_process.RBT <= new_process.TBT) {
    // then its PCB is simply added to the ready queue
    new_process.EST = 0;
    new_process.EET = 0;
    new_process.RBT = new_process.TBT;
    ready_queue[(*queue_cnt)++] = new_process;
    // return value is the PCB of the currently running process
    return current_process;
  } else {  // If the new process has a shorter burst time
    // the new process: the execution start time is set to the current timestamp
    new_process.EST = time_stamp;
    // execution end time is set to the sum of the current timestamp and the total burst time
    new_process.EET = time_stamp + new_process.TBT;
    // the remaining burst time is set to the total burst time
    new_process.RBT = new_process.TBT;
    // PCB of the currently-running process is added to the ready queue
    current_process.RBT -= time_stamp - current_process.EST;
    current_process.EST = 0;
    current_process.EET = 0;
    ready_queue[(*queue_cnt)++] = current_process;

    // return value is the PCB of the new process
    return new_process;
  }
}
struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX],
                                          int* queue_cnt, int timestamp) {
  // queue is empty, the method returns the NULLPCB
  if (!(*queue_cnt))
    return NULLPCB;

  int idx = 0;
  // finds the process with the smallest remaining burst time
  for (int i = 0; i < (*queue_cnt); i++)
    if (ready_queue[i].RBT < ready_queue[idx].RBT)
      idx = i;
  // return pcb
  struct PCB returned_pcb = ready_queue[idx];

  // removes this PCB
  for (int i = idx; i + 1 < (*queue_cnt); i++)
    ready_queue[i] = ready_queue[i + 1];
  --(*queue_cnt);

  // the execution start time as the current timestamp
  returned_pcb.EST = timestamp;
  // the execution end time as the sum of the current timestamp and the remaining burst time.
  returned_pcb.EET = timestamp + returned_pcb.RBT;

  // return pcb with smallest reaming burst time
  return returned_pcb;
}
struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX],
                                     int* queue_cnt, struct PCB current_process,
                                     struct PCB new_process, int timestamp,
                                     int time_quantum) {
  // If there is no currently-running process
  if (check_exited_process(current_process)) {
    // returns the PCB of the newly-arriving process

    // execution start time is set to the current timestamp
    new_process.EST = timestamp;
    // execution end time is set to the sum of the current timestamp
    // and the smaller of the time quantum and the total burst time
    new_process.EET = timestamp + MIN(time_quantum, new_process.TBT);
    // remaining burst time is set to the total burst time.
    new_process.RBT = new_process.TBT;
    // returns the PCB of the newly-arriving process
    return new_process;
  } else {  // If there is a currently-running process
    // execution start time and execution end time are set to 0
    new_process.EST = 0;
    new_process.EET = 0;
    // the remaining burst time is set to the total burst time
    new_process.RBT = new_process.TBT;
    // adds the PCB of the newly-arriving process to the ready queue
    ready_queue[(*queue_cnt)++] = new_process;

    // return value is the PCB of the currently running process
    return current_process;
  }
}
struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX],
                                        int* queue_cnt, int timestamp,
                                        int time_quantum) {
  // the ready queue is empty, the method returns the NULLPCB
  if (!(*queue_cnt))
    return NULLPCB;
  int idx = 0;
  // finds the process with the earliest arrival time
  for (int i = 0; i < (*queue_cnt); i++)
    if (ready_queue[i].AT < ready_queue[idx].AT)
      idx = i;

  struct PCB returned_pcb = ready_queue[idx];

  // removes this PCB from the ready queue
  for (int i = idx; i + 1 < (*queue_cnt); i++)
    ready_queue[i] = ready_queue[i + 1];
  --(*queue_cnt);

  // execution start time as the current timestamp
  returned_pcb.EST = timestamp;
  // execution end time as the sum of the current timestamp
  // and the smaller of the time quantum and the remaining burst time
  returned_pcb.EET = timestamp + MIN(returned_pcb.RBT, time_quantum);
  // return PCB
  return returned_pcb;
}