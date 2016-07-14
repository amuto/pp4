#include "sim.h"

int
main (void)
{
  sim_initialize(FCFS,S1);
  sim_start();
  sim_print_result();
  return 0;
}
