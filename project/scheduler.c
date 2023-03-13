/* Implementation of the scheduler */
/* for comments on the functions see the associated .h-file */

/* ----------------------------------------------------------------- */
/* Include required external definitions */
#include <math.h>
#include "bs_types.h"
#include "globals.h"
#include "processcontrol.h"
#include "scheduler.h"


/* ----------------------------------------------------------------- */
/*                Declarations of local helper functions             */



/* ----------------------------------------------------------------- */
/*                Externally available functions                     */
/* ----------------------------------------------------------------- */

pid_t schedule(readyList_t readyListParam)
{

    pid_t nextToRun;


    if (readyListParam == NULL) return NO_PROCESS;

    nextToRun = readyListParam->pid;
    // Prozess wird aus der Ready Priority Queue gelöscht bevor es ausgeführt wird
    removeReady(nextToRun);

    return nextToRun;

}


/* ----------------------------------------------------------------- */
/*                       Local helper functions                      */
/* ----------------------------------------------------------------- */




