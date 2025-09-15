# CPU Scheduling Lab

This lab project focuses on implementing **CPU scheduling algorithms** in an operating system.

---

## Overview

Each process in an operating system is represented by a **Process Control Block (PCB)**.\
The PCB contains information used by the scheduler to decide which process to run next.

### Process Control Block

```c
struct PCB {
    int process_id;
    int arrival_timestamp;
    int total_bursttime;
    int execution_starttime;
    int execution_endtime;
    int remaining_bursttime;
    int process_priority;
};
```

- `process_id` – Unique process ID
- `arrival_timestamp` – Time the process enters the ready queue
- `total_bursttime` – Total CPU time required
- `execution_starttime` – Time when execution starts
- `execution_endtime` – Time when execution ends
- `remaining_bursttime` – Remaining CPU time
- `process_priority` – Lower number indicates higher priority

The **Ready Queue** is an array of PCBs for processes waiting to execute.\
The **NULLPCB** is defined as:

```c
[PID:0, AT:0, TBT:0, EST:0, EET:0, RBT:0, Priority:0]
```

### Scheduling Policies Implemented

This lab covers three scheduling policies:

1. Priority-based Preemptive Scheduling (PP)
2. Shortest-Remaining-Time-Next Preemptive Scheduling (SRTP)
3. Round-Robin Scheduling (RR)

Each policy requires functions to handle:

- Process Arrival: A new process arrives and may preempt the current process or join the ready queue.
- Process Completion: A process finishes execution, and the scheduler selects the next process to run.

All functions are implemented in `cpu.c` and use the header file `oslabs.h`.

### Functions

#### 1. Priority-based Preemptive Scheduling (PP)

**handle\_process\_arrival\_pp**

```c
struct PCB handle_process_arrival_pp(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    struct PCB current_process,
    struct PCB new_process,
    int timestamp
);
```

- If CPU is idle: new process starts immediately. Update execution\_starttime, execution\_endtime, and remaining\_bursttime.
- If CPU is busy:
  - If new process has equal/lower priority → add to ready queue.
  - If new process has higher priority → preempt current process:
    - Add current process to ready queue (adjust remaining burst time).
    - Run new process immediately.

**Example Input:**

```c
current_process: [PID:1, AT:1, TBT:4, EST:1, EET:5, RBT:4, Priority:8]
new_process:     [PID:2, AT:2, TBT:3, EST:0, EET:0, RBT:3, Priority:6]
timestamp:       2
```

**Output:**

```c
ready_queue: [PID:1, AT:1, TBT:4, EST:1, EET:0, RBT:3, Priority:8]
return PCB:  [PID:2, AT:2, TBT:3, EST:2, EET:5, RBT:3, Priority:6]
```

**handle\_process\_completion\_pp**

```c
struct PCB handle_process_completion_pp(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    int timestamp
);
```

- If ready queue is empty → return NULLPCB.
- Otherwise, select the process with highest priority (smallest priority value) and update execution\_starttime and execution\_endtime before returning.

#### 2. Shortest-Remaining-Time-Next Preemptive Scheduling (SRTP)

**handle\_process\_arrival\_srtp**

```c
struct PCB handle_process_arrival_srtp(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    struct PCB current_process,
    struct PCB new_process,
    int timestamp
);
```

- If CPU is idle: new process runs immediately.
- If CPU is busy:
  - If new process’s burst time ≥ current process’s remaining time → add to ready queue.
  - If new process’s burst time < current process’s remaining time → preempt current process.

**handle\_process\_completion\_srtp**

```c
struct PCB handle_process_completion_srtp(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    int timestamp
);
```

- If ready queue is empty → return NULLPCB.
- Otherwise, select process with smallest remaining burst time.

#### 3. Round-Robin Scheduling (RR)

**handle\_process\_arrival\_rr**

```c
struct PCB handle_process_arrival_rr(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    struct PCB current_process,
    struct PCB new_process,
    int timestamp,
    int time_quantum
);
```

- If CPU is idle: new process runs for `min(time_quantum, total_bursttime)`.
- If CPU is busy: add new process to ready queue.

**handle\_process\_completion\_rr**

```c
struct PCB handle_process_completion_rr(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    int timestamp,
    int time_quantum
);
```

- If ready queue is empty → return NULLPCB.
- Otherwise, select the earliest-arriving process and run it for `min(time_quantum, remaining_bursttime)`.

