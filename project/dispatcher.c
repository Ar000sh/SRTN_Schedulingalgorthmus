/* Implementation of the dispatcher 								*/
/* for comments on the functions see the associated .h-file 		*/
/* !!!!!!!!!! Do not change the functions in this file !!!!!!!!!! 	*/

/* Functions are part of the test-environment and may use 			*/
/* information that is not available in a real system. 				*/

/* ----------------------------------------------------------------	*/
/* Include required external definitions */
#include <math.h>
#include "bs_types.h"
#include "globals.h"
#include "dispatcher.h"



/* ----------------------------------------------------------------- */
/*                Declarations of local helper functions             */

/* function to retrieve the  mean value between two IO-events for    */
/* the given type of process. Used to determine the time until the   */
/* next IO-event occurs (applying exponential distribution).		 */
unsigned probabilityFromType (ProcessType_t processType);

/* ----------------------------------------------------------------- */
/*                Externally available functions                     */
/* ----------------------------------------------------------------- */

schedulingEvent_t sim_runProcess(pid_t pid, unsigned quantum)
	{
	unsigned mean, remaining, IOtime;
	double prob, expProb; 
	// calculate the remaining process time
	remaining=processTable[pid].duration-processTable[pid].usedCPU;
	// look-up mean value of intervall length between two IO events for this process
	mean = probabilityFromType(processTable[pid].type); 
	if (mean==0) 		// no IO in this process
		{
		IOtime=0; 
		}
	else 				// determine when IO will occure
		{
		// calculate probability for IO using exponential distribution
		// see [http://de.wikipedia.org/wiki/Exponentialverteilung]
		// The parameter of exponential distribution is: lambda=1/mean;
		// normally distributed random variable
		prob = ((double)(rand() % 1000))/1000.0;
		// converted into exponential distribution
		expProb=-(double)mean*log(prob); 		
		// generate IO-event based on that probability
		IOtime=(unsigned)expProb;  //		IOtime=(unsigned)(expProb*(double)quantum); 
		}
	// disctinct between non-preemptive(quantum=0) and preemptive with quantum (quantum>0)
	/* ------ NON-PREEMPTIVE used for BATCH ------ */ 
	if (quantum==0) 
		{	// batch processing, quantum not used
		if ((IOtime>=remaining) || (IOtime==0))		// no IO 
			{	// no IO --> ignore IO
			processTable[pid].usedCPU=processTable[pid].usedCPU + remaining; 
			systemTime = systemTime + remaining;	
			// return the appropriate scheduling event
			return completed; 
			} 
		else 				// IO occured
			{
			systemTime = systemTime + IOtime;	// update system time
			processTable[pid].usedCPU=processTable[pid].usedCPU+IOtime; 
			return io; 		// return IO as scheduling event 
			}

		}
	else 
	/* ------ PREEMPTIVE WITH QUANTUM  ------ */ 
		{	// scheduling when really using the quantum 
		if ((IOtime>=quantum) || (IOtime>=remaining) || (IOtime==0))		// no IO 
			{	// no IO or IO occuring too late --> ignore IO
			if (quantum>remaining)		// check for early completion
				{	// quantum not fully used 
				processTable[pid].usedCPU=processTable[pid].usedCPU + remaining; // update process property
				systemTime = systemTime + remaining;	// update system time
				return completed;		// return the appropriate scheduling event
				}
			else
				{	// quantum fully used 
				processTable[pid].usedCPU=processTable[pid].usedCPU + quantum; // update process property
				systemTime = systemTime + quantum;	// update system time
				return quantumOver;	// return the appropriate scheduling event
				}

			} 
		else 				// IO occured
			{
			systemTime = systemTime + IOtime;	// update system time
			processTable[pid].usedCPU=processTable[pid].usedCPU+IOtime; // update process property
			return io; 		// return IO as scheduling event 
			}

		}
	return quantumOver;			// default: quantum fully used
	}

/* ----------------------------------------------------------------- */
/*                       Local helper functions                      */
/* ----------------------------------------------------------------- */

unsigned probabilityFromType (ProcessType_t processType)
// returns the mean value between two IO-events for the given type of process
	{
	unsigned result=0;
	switch (processType) {
		case os:
			result=IO_MEAN_OS;
			break; 
		case interactive:
			result=IO_MEAN_INTERACTIVE;
			break; 
		case batch: 
			result=IO_MEAN_BATCH;
			break; 
		case background: 
			result=IO_MEAN_BACKGROUND;
			break; 		
		case foreground: 
			result=IO_MEAN_FOREGROUND;
			break; 		
		default: 
			result=IO_MEAN_DEFAULT;
		}
	return result; 
	}

