# Disk Scheduling Lab

This lab project focuses on implementing **I/O scheduling algorithms** in an operating system.

---

## Overview

Each I/O request in an operating system is represented by a **Request Control Block (RCB)**:

```c
struct RCB {
    int request_id;
    int arrival_timestamp;
    int cylinder;
    int address;
    int process_id;
};
```

- `request_id` – Unique ID of the I/O request
- `arrival_timestamp` – Time the request arrives
- `cylinder` – Disk cylinder to access
- `address` – Physical disk address of the request
- `process_id` – ID of the process issuing the request

The **I/O Request Queue** is an array of `RCB` entries representing pending requests.  
The **NULLRCB** is defined as:

```c
[RID:0, AT:0, CYL:0, ADDR:0, PID:0]
```

This lab implements three scheduling policies, each requiring functions to handle **request arrival** and **request completion**.

---

## Scheduling Policies Implemented

1. **First-Come-First-Served (FCFS)**
2. **Shortest-Seek-Time-First (SSTF)**
3. **LOOK (Elevator Algorithm)**

All functions are implemented in `disk.c` and use the header file `oslabs.h`.

---

### 1. First-Come-First-Served (FCFS)

#### handle_request_arrival_fcfs

```c
struct RCB handle_request_arrival_fcfs(
    struct RCB request_queue[QUEUEMAX],
    int *queue_cnt,
    struct RCB current_request,
    struct RCB new_request,
    int timestamp
);
```

- If the disk is **idle** (`current_request` is `NULLRCB`):
  - Service the new request immediately and return it.
- Otherwise:
  - Add the new request to the queue and return the current request.

#### handle_request_completion_fcfs

```c
struct RCB handle_request_completion_fcfs(
    struct RCB request_queue[QUEUEMAX],
    int *queue_cnt
);
```

- If the queue is **empty**, return `NULLRCB`.
- Otherwise:
  - Select the request with the **earliest arrival time**.
  - Remove it from the queue and return it.

---

### 2. Shortest-Seek-Time-First (SSTF)

#### handle_request_arrival_sstf

```c
struct RCB handle_request_arrival_sstf(
    struct RCB request_queue[QUEUEMAX],
    int *queue_cnt,
    struct RCB current_request,
    struct RCB new_request,
    int timestamp
);
```

- If the disk is **idle**, service the new request immediately.
- Otherwise:
  - Add the new request to the queue.
  - Return the current request.

#### handle_request_completion_sstf

```c
struct RCB handle_request_completion_sstf(
    struct RCB request_queue[QUEUEMAX],
    int *queue_cnt,
    int current_cylinder
);
```

- If the queue is **empty**, return `NULLRCB`.
- Otherwise:
  - Choose the request whose **cylinder is closest** to the current cylinder.
  - Break ties by **earliest arrival time**.
  - Remove it from the queue and return it.

---

### 3. LOOK (Elevator Algorithm)

#### handle_request_arrival_look

```c
struct RCB handle_request_arrival_look(
    struct RCB request_queue[QUEUEMAX],
    int *queue_cnt,
    struct RCB current_request,
    struct RCB new_request,
    int timestamp
);
```

- If the disk is **idle**, service the new request immediately.
- Otherwise:
  - Add the new request to the queue.
  - Return the current request.

#### handle_request_completion_look

```c
struct RCB handle_request_completion_look(
    struct RCB request_queue[QUEUEMAX],
    int *queue_cnt,
    int current_cylinder,
    int scan_direction
);
```

- If the queue is **empty**, return `NULLRCB`.
- Otherwise:
  - If requests exist at the **current cylinder**, choose the one with the earliest arrival.
  - Else, if `scan_direction == 1` (upwards):
    - If requests exist with **higher cylinder numbers**, choose the closest.
    - Otherwise, choose the closest lower cylinder.
  - Else, if `scan_direction == 0` (downwards):
    - If requests exist with **lower cylinder numbers**, choose the closest.
    - Otherwise, choose the closest higher cylinder.
  - Remove the selected request from the queue and return it.

---

## References

- Modern Operating Systems (Andrew S. Tanenbaum), Section 5.4.3 – *Disk Scheduling Algorithms*
