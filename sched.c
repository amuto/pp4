#include <stdlib.h>
#include <stdio.h>
#include "sched.h"
/* #include "monitor.h" */

/*
 * Schedule module
 */

/* Monitor submodule */
void monitor_initialize ();
void monitor_allocation();

void monitor_process_allocate(PCB *);
void monitor_process_terminate(PCB *);
double monitor_average_turnaround_time (void);

/*
 * prototype declarations
 */

/* scheduling algorithms */
pcb_compare_function sched_FCFS;
pcb_compare_function sched_SRTF;
pcb_compare_function sched_RR;
void sched_initialize_by_func (pcb_compare_function);
pcb_compare_function *sched_algorithm_by_number (SchedulerType);

/*
 * global variables
 */

SchedulerType current_scheduler;
PCB *sched_current_process;
PCB *sched_ready_queue = NULL;
PCB *sched_start_list = NULL;
PCB *sched_finished_list = NULL;
/* last used pid */
int sched_last_pid;
/* pointer to the algorithm */
pcb_compare_function *sched_algorithm; 
PCB *monitor_activation_history[MAX_CLOCK]; /* for simulater */
int mon_current_clock = 0;

/*
 * function definitions
 */

pcb_compare_function *sched_algorithm_by_number (SchedulerType s)
{
  switch (s) {
  case FCFS:
    return *sched_FCFS;
    break;
  case SRTF:
    return *sched_SRTF;
    break;
  case RR:
    return *sched_RR;
    break;
  default:
    return *sched_FCFS;
    break;
  }
}

/* Mokuteki: */
void sched_set_scheduler (SchedulerType s)
{
  sched_algorithm = sched_algorithm_by_number(s);
  current_scheduler = s;
}

/* Mokuteki: */
SchedulerType sched_get_scheduler ()
{
  return current_scheduler;
}

/* Mokuteki: */
void sched_initialize (SchedulerType s)
{
  sched_set_scheduler(s);
  sched_last_pid = MIN_PID;
  sched_ready_queue = NULL;
  sched_current_process = NULL;
  sched_start_list = NULL;
  monitor_initialize ();
}

/* Mokuteki: make schedule */
void sched_scheduler ()
{
  /* A */
  {
    PCB *q = sched_ready_queue;
    while (q != NULL) {
      q->waiting_time++;
      q = q->next;
    }
  }
  /* B */
  if (sched_current_process) {
    sched_current_process->executed_time++;
    if (sched_current_process->executed_time == sched_current_process->required_time) {
      sched_terminate_current_process();
    }
  }
 /* C */
  {
    int flag = False;
    PCB *q = sched_start_list;
    while (q) {
      if (current_clock >= q->start_time) {
	printf(" * clock = %2d: pid%d starts now\n", current_clock, q->pid);
	PCB *target = q;
	q = q->next;
	pcb_remove(target, &sched_start_list);
	pcb_enqueue(target, &sched_ready_queue);
	flag = True;
	continue;
      }
      q = q->next;
    }
    if (sched_current_process && flag == False && sched_algorithm == sched_SRTF)
      return sched_dispatcher(sched_current_process);
  }
  /* D */
  if (sched_current_process) {
    if (sched_algorithm == sched_FCFS) {
      return sched_dispatcher(sched_current_process);
    }
    else {
      sched_current_process->state = READY;
      pcb_enqueue(sched_current_process, &sched_ready_queue);
      sched_current_process = NULL;
    }
  }
  /* E */
   if (sched_ready_queue) {
    PCB *selected = sched_ready_queue; /* current winner */
    PCB *tmp = sched_ready_queue;
    while(tmp) {
      selected = sched_algorithm(selected, tmp);
      tmp=tmp->next;
    }
    /* F */
    /* printf(" * clock = %2d: pid %d is selected\n", current_clock, selected->pid); */
    sched_dispatcher(selected);
  }
}

/* Mokuteki: disaptch to process 'to' (subfunction of sched_scheduler) */
void sched_dispatcher (PCB *to)
{
  to->state = RUNNING;
  to->waiting_time = 0;
  sched_current_process = to;
  monitor_process_allocate(to);
  pcb_remove(to, &sched_ready_queue);
  /* */
}

/* Mokuteki: */
int sched_create_process(int s, int r)
{
  PCB *new = pcb_new(s, r);
  new->pid = sched_last_pid++;
  pcb_enqueue(new, &sched_start_list);
  return 0;
}

/* Mokuteki: */
int sched_terminate_current_process()
{
  PCB *pcb = sched_current_process;
  if (! pcb)
    return -1;
  pcb_remove(pcb, &sched_ready_queue);
  /* */
  printf(" * clock = %2d: pid%d is terminated\n", current_clock, pcb->pid);
  monitor_process_terminate(pcb);
  sched_current_process = NULL;
  return 0;
}

/* Mokuteki: */
void sched_print()
{
  printf("Current time: %d:\t", current_clock); 
  printf(" * running process: ");
  pcb_print_list(sched_current_process);
  // printf(" * ready process queue: ");
  // pcb_print_list(sched_ready_queue);
  // printf(" * processes created already: ");
  // pcb_print_list(sched_start_list);
}

/* Mokuteki: select the candidate by FCFS */
PCB *sched_FCFS(PCB *i, PCB *j)
{
  if (i->start_time <= j->start_time) /* FIXME */
    return i;
  else
    return j;
}

/* Mokuteki: select the candidate by SRTF */
PCB *sched_SRTF(PCB *i, PCB *j)
{
  if (i->required_time - i->executed_time < j->required_time - j->executed_time)
    return i;
  else
    return j;
}

/* Mokuteki: select the candidate by Round Robin */
PCB *sched_RR(PCB *i, PCB *j __attribute__ ((unused)))
{
  return i; /* FIXME */
}

/*
 ** MONITOR BLOCK
*/

void monitor_initialize ()
{
  int i;
  mon_current_clock = -1;
  for (i = 0; i < MAX_CLOCK; i++)
    monitor_activation_history[i] = NULL;
}

void monitor_process_allocate(PCB *pcb)
{
  int i;
  for(i=mon_current_clock+1; i <= current_clock; i++)
    monitor_activation_history[i] = pcb;
  mon_current_clock = current_clock;
}

void monitor_process_terminate(PCB *pcb)
{
  pcb->executed_time=current_clock;
  pcb_enqueue(pcb, &sched_finished_list);
}

PCB **monitor_allocation_history(void)
{
  return (PCB **)monitor_activation_history;
}

double monitor_average_turnaround_time (void)
{
  int num_processes = 0;
  int turn_around = 0;
 PCB *p = sched_finished_list;
  while (p) {
    num_processes++;
    turn_around += p->executed_time - p->start_time;
    p = p->next;
  }
  if (num_processes==0)
    return 1000000;
  return (double)turn_around/(double)num_processes;
}
