/* header-file defining the interface of the logger							*/	 
/* please extent if needed to suit the needs of logging added functionality */


// GRUPPENARBEIT

#ifndef __LOG__
#define __LOG__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bs_types.h"
#include "globals.h"
#include "dispatcher.h"


void logGeneric(char* message);
/* print the given general string to stdout and/or a log file 				*/
/* The time stamp (systemTime) will be prepended automatically				*/
/* the linefeed is automatically appended									*/
void logAdd(unsigned pid, char* message1,char* message2,unsigned done);
void logPid(unsigned pid, char* message);
/* print the given  string to stdout and/or a log file 						*/
/* The time stamp (systemTime) and the  PID are prepended automatically		*/
/* the linefeed is automatically appended									*/
void logIOreadyDone(unsigned pid, unsigned done);
/// hier fehlt kommentar

void logPidEvent(unsigned pid, schedulingEvent_t reason, char * message);
/* print the given  string to stdout and/or a log file 						*/
/* The time stamp (systemTime) and the  PID are prepended automatically		*/
/* the last scheduling event is also prepended								*/
/* the linefeed is automatically appended									*/

void logPidCompleteness(unsigned pid, unsigned done, unsigned length, 
						char * message);
/* print the given  string to stdout and/or a log file 						*/
/* The time stamp (systemTime) and the  PID are prepended automatically		*/
/* the fraction of used CPU over process duratiuon is also prepended		*/
/* the linefeed is automatically appended									*/


#endif /* __LOG__ */