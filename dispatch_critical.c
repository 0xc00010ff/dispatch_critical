//
//  dispatch_critical.c
//

#include "dispatch_critical.h"
#include <stdio.h>

void dispatch_critical(double delayInSeconds, dispatch_block_t executionBlock)
{
    if (!executionBlock) { return; }
    
    int leeway = 0; // prevent GCD from scheduling blocks when convenient
    dispatch_queue_t queue = dispatch_queue_create("_dispatch_critical_q_", 0);
    dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
    if (timer)
    {
        dispatch_source_set_timer(timer,
                                  dispatch_walltime(DISPATCH_TIME_NOW,
                                                    NSEC_PER_SEC * delayInSeconds),
                                  DISPATCH_TIME_FOREVER, leeway);
        dispatch_source_set_event_handler(timer, ^{
            dispatch_async(dispatch_get_main_queue(), ^{
                executionBlock();
                dispatch_source_cancel(timer);
            });
        });
        dispatch_resume(timer);
    }
}