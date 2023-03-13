/* Include-file defining elementary data types used by the 			*/
/* operating system */


// GRUPPENARBEIT

#ifndef __BS_TYPES__
#define __BS_TYPES__

//#include "globals.h"

typedef enum {FALSE=0, TRUE} Boolean;


/* data type for storing of process IDs		*/
typedef unsigned pid_t;

/* data type for the possible types of processes */
/* the process type determines the IO-characteristic */
typedef enum 
	{
		os, interactive, batch, background, foreground
	} ProcessType_t; 

/* data type for the process-states used for scheduling and life-	*/
/* cycle manegament of the processes 								*/
typedef enum 
	{
		init, running, ready, blocked, ended
		
	} Status_t; 

/* data type for the different events that cause the scheduler to	*/
/* become active */
typedef enum 
	{ 
		none, started, completed, io, quantumOver, unblocked
	} schedulingEvent_t; 

/* data type for the simulation environment */
/* the information contained ion this struct are not available to the os */

typedef struct sim_info_struct
	{
		unsigned IOready;	// simulation time when IO is complete, may be in the future
	} sim_info_t;

/* data type for the Process Control Block */
/* +++ this might need to be extended to support future features	*/
/* like additional schedulers */
typedef struct 
	{
		Boolean valid; 		
		pid_t pid; 
		pid_t ppid; 
		unsigned ownerID;
		unsigned start; 
		unsigned duration; 
		unsigned usedCPU; 
		ProcessType_t type; 
		Status_t status;
		sim_info_t simInfo;
	} PCB_t;




/* data type for the list of processes in ready state				*/
// Node einer Priority Queue
// Mit PID und Remaining Time und Pointer auf das nächste Node in der Queue
typedef struct readyListElement_struct
{
    pid_t pid;
    unsigned	remainingTime;
    struct readyListElement_struct *next;

} readyListElement_t;
/* +++ this needs to be changed for support of multiprogramming			*/
/* +++ for batch-OS this is only the single running process				*/
/* data type for the list of processes in blocked state					*/

typedef readyListElement_t* readyList_t;
/* +++ this needs to be changed for support of multiprogramming			*/
/* +++ for batch-OS this is only the single running process				*/

//======================================================================



//===========================================================================

/* data type for the list of processes in blocked state					*/
// Node einer Priority Queue
// Mit PID und IOready und Pointer auf das nächste Node in der Queue
typedef struct blockedListElement_struct
{
	pid_t		pid;
	unsigned	IOready;
	struct blockedListElement_struct* next;
} blockedListElement_t;

/* +++ this needs to be changed for support of multiprogramming			*/
/* +++ for batch-OS this is only the single running process				*/
/* data type for the list of processes in blocked state					*/

typedef blockedListElement_t* blockedList_t;
/* +++ this needs to be changed for support of multiprogramming			*/
/* +++ for batch-OS this is only the single running process				*/

// =============================================================================




#endif  /* __BS_TYPES__ */ 