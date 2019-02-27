#ifndef _PSTAT_H
#define _PSTAT_H

#include "param.h"

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

// Copied directly from the assignment sheet
struct pstat {
	int inuse[NPROC]; // whether this slot of the proccess table is in use (1 or 0)
	int tickets[NPROC]; // Number of tickets
	int pid[NPROC]; // PID of each process
	int ticks[NPROC]; // Number of ticks each process has accumulated
	
	enum procstate state[NPROC]; //state

	int total_tickets;

};

#endif
