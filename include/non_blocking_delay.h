#ifndef NON_BLOCKING_DELAY_H
#define NON_BLOCKING_DELAY_H

typedef struct
{
    unsigned long duration;
    unsigned long startTime;
} nonBlockingDelay_t;

void nonBlockingDelayInit(nonBlockingDelay_t *p, unsigned long duration);
bool nonBlockingDelayUpdate(nonBlockingDelay_t *p);

#endif /* NON_BLOCKING_DELAY_H */