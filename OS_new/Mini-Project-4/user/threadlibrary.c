#include "user.h"
#include "x86.h"

int thread_create(void (*start_routine)(void*), void*arg)
{
    void *stack = malloc(PGSIZE*2);
    if(stack == NULL)
    return -1;
    if((uint)stack %PGSIZE)
    stack = stack + (4096 - (uint)stack% PGSIZE);

    return clone(start_routine, arg, stack);
}

int thread_join()
{
    void *stack = NULL;
    int rv = join(&stack);
    if(stack == NULL)
        return -1;
    free(stack);
    return rv;
}

void lock_acquire(lock_t * lk)
{
while(xchg(&lk->locked, 1) != 0) ;
}

void lock_release(lock_t * lk)
{
xchg(&lk->locked, 0);
}

void lock_init(lock_t* lk)
{
lk->locked = 0;
}
