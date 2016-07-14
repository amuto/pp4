#include <stdio.h>
#include "sim.h"

int sim_upper_limit = 0;
int timechart[MAX_PROCESS+1][MAX_CLOCK];
int process_info[MAX_PROCESS+1][2];

/* FUNCTION DEFINITIONS */
void sim_initialize (SchedulerType i, ScenarioType s)
{
  current_clock = 0;
  sched_initialize(i);
  switch (s) {
  case S0:
    sim_set_process(0, 1);
    sim_set_process(0, 2);
    break;
  case S1:
    sim_set_process(0, 14);
    sim_set_process(9, 18);
    sim_set_process(20, 12);
    break;
  case S2:
    sim_set_process(0, 16);
    sim_set_process(9, 18);
    sim_set_process(19, 12);
    break;
  case S3:
    sim_set_process(0, 14);
    sim_set_process(9, 18);
    sim_set_process(20, 12);
    break;
  case S4:
    sim_set_process(0,8);
    sim_set_process(1,7);
    sim_set_process(2,20);
    sim_set_process(4,8);
    sim_set_process(7,13);
    sim_set_process(20,10);
    break;
  case S5:
    sim_set_process(0,7);
    sim_set_process(4,17);
    sim_set_process(2,9);
    sim_set_process(5,8);
    sim_set_process(10,8);
    sim_set_process(13,10);
    break;
  case S6:
    sim_set_process(0,8);
    sim_set_process(0,7);
    sim_set_process(5,20);
    sim_set_process(9,8);
    sim_set_process(9,13);
    sim_set_process(9,10);
    break;
  case S7:
    sim_set_process(0,20);
    sim_set_process(1,4);
    sim_set_process(4,4);
    sim_set_process(5,6);
    sim_set_process(7,4);
    sim_set_process(9,10);
    break;
  case S8:
    sim_set_process(0,9);
    sim_set_process(1,8);
    sim_set_process(2,19);
    sim_set_process(3,5);
    sim_set_process(4,8);
    sim_set_process(10,10);
    break;
  case S9:
    sim_set_process(0,3);
    sim_set_process(1,9);
    sim_set_process(2,4);
    sim_set_process(4,2);
    break;
  case S10:
  sched_create_process(0, 41);
  sched_create_process(3, 12);
  sched_create_process(1, 5);
  sched_create_process(5, 2);
  sched_create_process(17, 10);
  sched_create_process(3, 20);
  sched_create_process(8, 13);
  sched_create_process(23, 23);
  sched_create_process(40, 2);
  sched_create_process(38, 13);
  sched_create_process(3, 12);
  sched_create_process(9, 8);
  sched_create_process(22, 19);
  sched_create_process(13, 8);
  sched_create_process(8, 9);
  sched_create_process(19, 18);
  sched_create_process(51, 3);
  sched_create_process(28, 18);
  sched_create_process(31, 2);
  sched_create_process(26, 6);
  sched_create_process(17, 12);
    break;
  default:
    break;
  }
}

int sim_set_process (int s, int t)
{
  int pid = sched_create_process(s, t);
  process_info[pid][0] = s;
  process_info[pid][1] = t;
  return 0;
}

void sim_start ()
{
  printf("Start the simlutation from %d to %d\n", current_clock, MAX_CLOCK);
  while(current_clock < MAX_CLOCK) {
    sched_scheduler();
    current_clock++;
  }
}


void set_timechart ()
{
  int pid;
  int t;

  for (pid = 1; pid < MAX_PROCESS;  pid++)
    for (t = 0; t < MAX_CLOCK; t++) {
      if (monitor_allocation_history()[t]== NULL)
	timechart[pid][t] = 0;
      else if (monitor_allocation_history()[t]->pid == pid)
	timechart[pid][t] = 1;
      else
	timechart[pid][t] = 0;
    }
}

/* Mokuteki: print the result of the simulation */
void sim_print_result ()
{
  int pid;
  int t;
  PCB **table __attribute__ ((unused));
  switch (sched_get_scheduler()) {
  case FCFS:
    printf("FCFS\n");
    break;
  case SRTF:
    printf("SRTF\n");
    break;
  case  RR:
    printf("RR\n");
    break;
  default:
    printf("hen\n");
    break;
  }
  printf ("Elapsed time: %d\n", current_clock);
  printf ("Ave. Turn-arround time : %.1lf\n", monitor_average_turnaround_time ());
  /* FIXME (use after set_timechart implementation */
  {
    int max_process = 0;
    int end_time;
    PCB *l = sched_finished_list;

    set_timechart();
    printf(" Time Chart\n");

    while (l) {
      max_process++;
      l = l->next;
    }
    for (end_time = MAX_CLOCK-1; 0 < end_time; end_time--) {
      int flag = 0;
      int p = 1;
      for (p = 1; p <= max_process; p++)
	if (timechart[p][end_time] == 1) {
	  flag = 1;
	  break;
	}
      if (flag) break;
    }
    for (pid = 1; pid <= max_process;  pid++) {
      printf("P%d: ", pid);
      for (t = 0; t < end_time; t++) {
	if (timechart[pid][t] == 1)
	  printf("X");
	else
	  printf(" ");
      }
      printf("\n");
    }
  }
  /* */
}

int sim_get_number_of_processes()
{
  return sched_last_pid;
}

int sim_get_process_info (int pid, int k)
{
  if (sched_last_pid < pid) return -1;
  switch (k) {
  case 1:
    return process_info[pid][0];
  case 2:
    return process_info[pid][1];
  default:
    return -1;
  }
}
