/* Functions for control and administration of processes including  */
/* creation, destruction, blocked-control...						*/
/* for comments on the functions see the associated .h-file 		*/

/* ----------------------------------------------------------------	*/
/* Include required external definitions */
#include <math.h>
#include "bs_types.h"
#include "globals.h"
#include "dispatcher.h"
#include "processcontrol.h"
#include "log.h"
#include "simruntime.h"

/* ----------------------------------------------------------------	*/
/* Declare global variables according to definition in globals.h	*/
PCB_t processTable[NUM_PROCESSES+1]; 	// the process table
readyList_t readyList;	// list of runnable processes
blockedList_t blockedList;	// pointer to blocked process

/* ----------------------------------------------------------------	*/
/* Declarations of global variables visible only in this file 		*/
blockedListElement_t blockedOne; // the only process that can be blocked 
/*this must be extended to a suitable data structure for multiprogramming */

readyListElement_t readyOne;	// the only process ready in the batch system 
/*this must be extended to a suitable data structure for multiprogramming */


/* ---------------------------------------------------------------- */
/* Functions for administration of processes in general 			*/
/* ---------------------------------------------------------------- */

pid_t getNextPid()
/* Typically the PID is the index into the process table, thus the pool  	*/
/* for PIDs is limited by the size of the process table. If the end of the	*/
/* process table is reached, new PIDs are assigned by re-using unused 		*/
/* entries in the process table. 											*/
/* If no new PID can be returned (i.e. the process table is full, zero is 	*/
/* returned, which is not a valid PID. 										*/

{
	static unsigned pidCounter = 0;
	// determine next available pid. 
	for (int i = 0; i < NUM_PROCESSES; i++) {
		pidCounter++; 
		if (pidCounter > NUM_PROCESSES) pidCounter = 1; 
		if (!processTable[pidCounter].valid) return pidCounter;
	}
	/* If the loop is completed there was no free entry in the process table */
	return 0;	/* not a valid PID indicating an error  */
}

Boolean deleteProcess(pid_t pid)
/* Voids the PCB of the process with the given pid, this includes setting 	*/
/* the valid-flag to invalid and setting other values to invalid values.	*/
/* retuns FALSE on error and TRUE on success								*/
{
	if (pid == NO_PROCESS)
		return FALSE;
	else {	/* PCB correctly passed, now delete it */
		processTable[pid].valid = FALSE;
		processTable[pid].pid = 0;
		processTable[pid].ppid = 0;
		processTable[pid].ownerID = 0;
		processTable[pid].start = 0;
		processTable[pid].duration = 0;
		processTable[pid].usedCPU = 0;
		processTable[pid].type = os;
		processTable[pid].status = ended;
		return TRUE;
	}
}

/* ---------------------------------------------------------------- */
/* Functions for administration of blocked processes 				*/
/* ---------------------------------------------------------------- */
/* CAUTION: For simulation purposes the blocked list must comply with:			*/
/*		- each entry has the information of the release time (IOready)			*/
/*		  included for each process												*/
/*		- The blocked list is sorted by not decreasing release times (IOready)	*/
/*			(i.e. first process to become unblocked is always head of the list	*/


Boolean initBlockedList(void)
/* Initialise the blocked process control data structure					*/
/* (no blocked processes exist at initialisation time of the os)			*/
/* CAUTION: For simulation purposes the blocked list must comply with:			*/
/*		- each entry has the information of the release time (IOready)			*/
/*		  included for each process												*/
/*		- The blocked list is sorted by not decreasing release times (IOready)	*/
/*			(i.e. first process to become unblocked is always head of the list	*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store blocked process in batch    xxxx */
/* xxxx processing. A blocked list needs to be implemented 		       xxxx */
{

    blockedList = NULL;
    return TRUE;

}

// Speichern in einer Instanz der Funktion den Speicher den der Prozess benötigt
// Kriegt PID und die Remaining Time die der Prozess noch braucht bis seine Ausführung vorbei ist
// Berechnet durch die derzeitige Systemzeit + die Zeit wie lange der Prozess blockiert wird
struct blockedListElement_struct* newBlockedListElement(pid_t pid, unsigned blockDuration) {
    struct blockedListElement_struct* temp = (struct blockedListElement_struct*)malloc(sizeof(struct blockedListElement_struct));
    temp->pid = pid;
    temp->IOready = systemTime + blockDuration;
    temp->next = NULL;
    return temp;
}
Boolean addBlocked(pid_t pid, unsigned blockDuration)
/* CAUTION: For simulation purposes the blocked list must comply with:			*/
/*		- each entry has the information of the release time (IOready)			*/
/*		  included for each process	(handled by the simulation)					*/
/*        calculated as the systemTime + blockDuration						*/
/*		- The blocked list is sorted by not decreasing release times (IOready)	*/
/*			(i.e. first process to become unblocked is always head of the list	*/

/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store blocked process in batch    xxxx */
/* xxxx processing. A blocked list needs to be implemented 		       xxxx */
/* retuns FALSE on error and TRUE on success								*/
{
    processTable[pid].status = blocked;
    struct blockedListElement_struct* head = blockedList;
    struct blockedListElement_struct* temp = newBlockedListElement(pid,blockDuration);
    // Sollte die blockedList leer sein oder IOready Zeit vom Head größer als die vom neu
    // Erzeugten sein, wird das neue Element zum Head und das vorherige nach hinten verschoben
    if (blockedList == NULL || blockedList->IOready > temp->IOready) {
        temp->next = blockedList;
        blockedList = temp;
    }

    else{
        // Solange nächstes Element nicht > IOready Zeit als neues hat
        // Suchen wir weiter. Sobald gefunden wird, wird Element vor dem nächsten Element hinzugefügt
        while (head->next != NULL &&
               head->next->IOready <= temp->IOready) {
            head = head->next;
        }
        temp->next = head->next;
        head->next = temp;
    }
    logAdd(pid,"added the process to the blockedList","and will blocked until:",(blockDuration + systemTime));

    return TRUE;
}


Boolean unblockProcess(void ) {
    
    struct blockedListElement_struct *ptr = blockedList;

    // Wenn BlockList nicht leer ist und die IOready Zeit vom Head <= systemZeit ist
    // Wird der Prozess aus der Blocked Priority Queue gelöscht
    // PID des Prozesses wurde zwischengespeichert um dann in die Ready Queue hinzugefügt zu werden
    if (ptr != NULL && ptr->IOready <= systemTime) {
        pid_t  currentPid = ptr->pid;
        logIOreadyDone(ptr->pid,ptr->IOready);
        removeBlocked(ptr->pid);
        addReady(currentPid);
        return TRUE;
    }


    return FALSE;
}

Boolean removeBlocked(pid_t pid)
/* Removes the given PID from the blocked-list								*/		
/* retuns FALSE on error and TRUE on success								*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store blocked process in batch    xxxx */
/* xxxx processing. A blocked list needs to be implemented 		       xxxx */
{
    // Pointer auf den derzeitigen Head der Queue
    // ersetzen derzeitiges Element mit dem nächsten Element innerhalb der Blocked Priority Queue
    // Geben Speicher wieder frei
    if(blockedList == NULL) return FALSE;
    struct blockedListElement_struct* temp = blockedList;
    blockedList = blockedList->next;
    free(temp);
    logPid(pid,"removed the process out of blockedList");


    return TRUE;
}

Boolean isBlockedListEmpty(void)
/* predicate returning TRUE if any blocked process exists, FALSE if no		*/
/* blocked processes exist													*/
{

    return  blockedList == NULL;;
}

blockedListElement_t *headOfBlockedList()
/* returns a pointer to the first element of the blocked list				*/
/* MUST be implemented for simulation purposes								*/			
{
	if (!isBlockedListEmpty()) {
		return blockedList;	// return pointer to the only blocked element remembered
	} 
	else return NULL;		// empty blocked list has no first element
}


/* ---------------------------------------------------------------- */
/* Functions for administration of ready processes 				*/
/* ---------------------------------------------------------------- */
/* CAUTION: For simulation purposes the ready list must comply with:*/
/*		- interface as given in the .h-file							*/
/*		- The ready list is sorted by not decreasing start-times			*/
/*			(i.e. first process to become ready is always head of the list	*/
/*      															*/

Boolean initReadyList(void)
/* Initialise the ready process control data structure						*/
/* (no ready processes exist at initialisation time of the os)				*/
/* retuns FALSE on error and TRUE on success								*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store the ready process in        xxxx */
/* xxxx batch processing. A ready list needs to be implemented 		   xxxx */
{
    readyList = NULL;
    return TRUE;
}
    // Speichern in einer Instanz der Funktion den Speicher den der Prozess benötigt
    // Kriegt PID und die Remaining Time die der Prozess noch braucht bis seine Ausführung vorbei ist
    // Berechnet durch den ProcessTable, wo wir die PID von diesem Prozess kriegen, dessen
    // Duration - die genutzte cpuzeit subtrahiert wird
struct readyListElement_struct* newReadyListElement(pid_t pid) {
    struct readyListElement_struct* temp = (struct readyListElement_struct*)malloc(sizeof(struct readyListElement_struct));
    temp->pid = pid;
    temp->remainingTime = processTable[pid].duration - processTable[pid].usedCPU;
    temp->next = NULL;
    return temp;
}

Boolean addReady(pid_t pid)	// add this process to the ready list
/* retuns FALSE on error and TRUE on success								*/
/* CAUTION: For simulation purposes the ready list must comply with:*/
/*		- interface as given in the .h-file							*/
/*		- no process is added as "ready" before its start time has elapsed	*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store the only ready process in   xxxx */
/* xxxx batch processing. A blocked list needs to be implemented 	   xxxx */
{
    // Erzeugen neues Element mittels newReadyListElement Funktion
    processTable[pid].status = ready;
    struct readyListElement_struct* head = readyList;
    struct readyListElement_struct* temp = newReadyListElement(pid);
    unsigned timeremaining = processTable[pid].duration - processTable[pid].usedCPU;
    // Sollte die ReadyList leer sein oder die remaining Time vom Head größer als die vom neu
    // Erzeugten sein, wird das neue Element zum Head und das vorherige nach hinten verschoben
    if (readyList == NULL || readyList->remainingTime > timeremaining) {
        temp->next = readyList;
        readyList = temp;
    }
    else{
        // Sollte das nicht der Fall sein dann wird in der Queue weitergesucht bis wir die richtige
        // Position finden und sortieren das Element ein
        while (head->next != NULL &&
               head->next->remainingTime <= timeremaining) {
            head = head->next;
        }
        temp->next = head->next;
        head->next = temp;
    }
    logAdd(pid,"added the process to the readyList","with the remaining time:",timeremaining);
    return TRUE;

}


Boolean removeReady(pid_t pid)
/* retuns FALSE on error and TRUE on success								*/
/* CAUTION: For simulation purposes the ready list must comply with:*/
/*		- interface as given in the .h-file							*/
/*		- no process is added as "ready" before its start time has elapsed	*/
/* xxxx This function is a stub with reduced functionality, it must be xxxx */
/* xxxx extended to enable full functionality of the operating system  xxxx */
/* xxxx A global variable is used to store ready process in batch    xxxx */
/* xxxx processing. A ready list needs to be implemented 		       xxxx */
{

    // Pointer auf den derzeitigen Head der Queue
    // ersetzen derzeitiges Element mit dem nächsten Element innerhalb der Ready Priority Queue
    // Geben Speicher wieder frei
    if(readyList == NULL) return FALSE;
    struct readyListElement_struct* temp = readyList;
    readyList = readyList->next;
    free(temp);
    logPid(pid,"removed the process out of readyList");

    return TRUE;

}



Boolean isReadyListEmpty(void)
/* predicate returning TRUE if any ready process exists, FALSE if no		*/
/* ready processes exist													*/
{

    return readyList == NULL;
}

readyListElement_t* headOfReadyList()
/* returns a pointer to the first element of the ready list				*/
/* MUST be implemented for simulation purposes								*/
/* CAUTION: For simulation purposes the ready list must comply with:*/
/*		- interface as given in the .h-file							*/
/*		- no process is added as "ready" before its start time has elapsed	*/
{

    if (!isReadyListEmpty()) {
        return readyList;	// return pointer to the only ready element remembered
    }

    else return NULL;		// empty ready list has no first element
}


