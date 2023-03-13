/* Include-file defining global defines and constants  	 		*/
/* used by the operating system */

// GRUPPENARBEIT

#ifndef __GLOBALS__
#define __GLOBALS__

#define	_CRT_SECURE_NO_WARNINGS		// suppress legacy warnings 

#include "bs_types.h"
#include "core.h"
#include "log.h"
#include "scheduler.h"
#include "simruntime.h"

// if this directive is enabled, the simulation supports multiprogramming. 
// Must be activated for any scheduler but the initial batch system.
#define SIM_MULTIPROGAMMING

// if this directive is enabled, the random number generator is seeded with zero
#define NO_RANDOM_SEED

// Number of possible concurrent processes 
#define NUM_PROCESSES 20

// PID of zero is used to indicate that no matching process exists
#define NO_PROCESS 0

// Maximum duration one process gets the CPU, zero indicates no preemption
#define QUANTUM 50

// name of the file with process definitions
#define PROCESS_FILENAME "processes.txt"

/* ----------------------------------------------------------------	*/
/* Define global variables that will be visible in all sourcefiles	*/
extern PCB_t processTable[NUM_PROCESSES+1]; 	// the process table
extern unsigned systemTime; 	// the current system time (up time)
extern readyList_t readyList;	// pointer to list of runnable processes
extern blockedList_t blockedList;	// pointer to blocked process


#endif  /* __GLOBALS__ */ 