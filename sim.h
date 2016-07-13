#define SIM_H
#ifndef SCHED_H
#include "sched.h"
#endif

#define MAX_PROCESS 1000

typedef enum { S0=0, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11 } ScenarioType;

extern int timechart[MAX_PROCESS+1][MAX_CLOCK];

void sim_initialize (SchedulerType, ScenarioType);
void sim_start (void);
void sim_print_result(void);
int sim_set_process (int s, int t);

int sim_get_number_of_processes ();
int sim_get_process_info (int p, int k);
