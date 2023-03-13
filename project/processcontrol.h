/* header-file defining the interface of the dispatcher 					*/
/* the dispatcher contains all functions required to run the 				*/
/* simulated processes 														*/
/* The dispatcher is called in the central scheduling loop. The scheduler	*/
/* must be called to determine, which process to run						*/


// GRUPPENARBEIT


#ifndef __PROCESSCONTROL__
#define __PROCESSCONTROL__

#include "bs_types.h"
#include "globals.h"

/* The interface for handling blocked and ready processes is not suited for	*/
/* multiprogramming and more than one blocked process.						*/
/* Functions like removeBlocked(pProcess) */


pid_t getNextPid();
/* returns the next available pid.											*/
/* Typically the PID is the index into the process table, thus the pool  	*/
/* for PIDs is limited by the size of the process table. If the end of the	*/
/* process table is reached, new PIDs are assigned by re-using unused 		*/
/* entries in the process table. 											*/
/* If no new PID can be returned (i.e. the process table is full, zero is 	*/
/* returned, which is not a valid PID.

/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */

Boolean deleteProcess(pid_t pid);
/* Voids the PCB of the process with the given pid, this includes setting 	*/
/* the valid-flag to invalid and setting other values to invalid values.	*/
/* retuns FALSE on error and TRUE on success								*/


/* ---------------------------------------------------------------- */
/* Functions for administration of blocked processes 				*/
/* ---------------------------------------------------------------- */


Boolean initBlockedList(void);
/* Initialise the blocked process control data structure					*/ 
/* (no blocked processes exist at initialisation time of the os)			*/
/* retuns FALSE on error and TRUE on success								*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store blocked process in batch    xxxx */
/* xxxx processing. A blocked list needs to be implemented 		       xxxx */

Boolean addBlocked(pid_t pid, unsigned releaseTime);
/* Adds the given PID to the blocked-list									*/		
/* retuns FALSE on error and TRUE on success								*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store blocked process in batch    xxxx */
/* xxxx processing. A blocked list needs to be implemented 		       xxxx */
/* remembers exaclty one blocked process, changes process state to "blocked"*/

Boolean removeBlocked(pid_t pid);
/* Removes the given PID from the blocked-list								*/		
/* retuns FALSE on error and TRUE on success								*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store blocked process in batch    xxxx */
/* xxxx processing. A blocked list needs to be implemented 		       xxxx */
/* remembers that no process is blocked										*/

Boolean isBlockedListEmpty(void); 
/* predicate returning TRUE if any blocked process exists, FALSE if no		*/	
/* blocked processes exist													*/

blockedListElement_t *headOfBlockedList();
/* returns a pointer to the first element of the blocked list				*/
/* MUST be implemented for simulation purposes								*/
Boolean unblockProcess(void );

/* ---------------------------------------------------------------- */
/* Functions for administration of ready processes 				*/
/* ---------------------------------------------------------------- */
/* CAUTION: For simulation purposes the ready list must comply with:*/
/*		- interface as given in the .h-file							*/
/*      															*/


Boolean initReadyList(void);
/* Initialise the ready process control data structure						*/
/* (no ready processes exist at initialisation time of the os)				*/
/* retuns FALSE on error and TRUE on success								*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store the ready process in        xxxx */
/* xxxx batch processing. A ready list needs to be implemented 		   xxxx */


Boolean addReady(pid_t pid);
/* Adds the given PID to the ready-list										*/
/* retuns FALSE on error and TRUE on success								*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store the only ready process in   xxxx */
/* xxxx batch processing. A blocked list needs to be implemented 	   xxxx */


Boolean removeReady(pid_t pid);
/* Removes the given PID from the ready-list								*/
/* retuns FALSE on error and TRUE on success								*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store ready process in batch    xxxx */
/* xxxx processing. A ready list needs to be implemented 		       xxxx */

Boolean isReadyListEmpty(void);
/* predicate returning TRUE if any ready process exists, FALSE if no		*/
/* ready processes exist													*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store ready process in batch    xxxx */
/* xxxx processing. A ready list needs to be implemented 		       xxxx */




void printList(void) ;
void printListready(void);


readyListElement_t* headOfReadyList();
/* returns a pointer to the first element of the ready list				*/
/* MUST be implemented for simulation purposes								*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store ready process in batch    xxxx */
/* xxxx processing. A ready list needs to be implemented 		       xxxx */


#endif /* __PROCESSCONTROL__ */
