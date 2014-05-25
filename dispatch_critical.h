//
//  dispatch_critical.h
//


#ifndef dispatch_critical_h
#define dispatch_critical_h

#include <dispatch/dispatch.h>

/**
 * Functionally equivalent to dispatch_after, but with a 
 * guarantee for no latency caused by opportunistic scheduling
 */
void dispatch_critical(double delay, dispatch_block_t executionBlock);

#endif
