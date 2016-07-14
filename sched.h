#define SCHED_H
#ifndef BASETYPES_H
#include "basetypes.h"
#endif

#define True 1
#define False 0

#define MIN_PID 1		/* PID starts from 1 */
#define MAX_CLOCK 1000	/* upper limit time of simulation */

/* kind of scheduling algorithm */
typedef enum { FCFS, SRTF, RR } SchedulerType;

extern PCB *sched_current_process;
extern PCB *sched_ready_queue;
extern PCB *sched_start_list;
extern PCB *sched_finished_list;
extern int sched_last_pid;		/* the last used pid */

void sched_set_scheduler (SchedulerType);
SchedulerType sched_get_scheduler (void);
void sched_initialize(SchedulerType);
void sched_scheduler ();
void sched_dispatcher (PCB *);
int sched_create_process(int, int);
int sched_terminate_current_process(void);
void sched_print(void);

/* monitor block */
void monitor_initialize ();
void monitor_allocation();
extern PCB** monitor_allocation_history(void);
void monitor_process_allocate(PCB *);
void monitor_process_terminate(PCB *);
double monitor_average_turnaround_time (void);
