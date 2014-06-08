dispatch_critical
=================
#### GCD asyncronous scheduling with no coalescing

The standard implementation for Apple's Grand Central Dispatch function `dispatch_after()` executes its given block at an opportune time close to the specified delay in order to minimize CPU cycles for routine operations. This becomes a problem when exact timing matters, such as for scheduled animations. __dispatch_critical__ is a simple function that hides away the overhead of creating your own dispatch timer with zero time margin for CPU coalesing. 

I have monitored the use of this technique in multiple applications and devices, and have seen no negative performace results when performing 10+ UIView animation operations per second. That said, the creators of GCD decided the system was better using timer coalescing by default, so I suggest that you only use this API sparingly and when it is actually needed. 


##### Usage

``` c
dispatch_critical(2.0, ^{ NSLog(@"Hello from the past"); });
```
