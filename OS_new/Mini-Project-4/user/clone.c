#include "assert.h"
int global = 0;
void worker(void *arg_ptr);
// Clone and verify that address space is shared
int main()
{
								global = 13;
								void *stack = malloc(PGSIZE*2);
								if((uint)stack%PGSIZE)
																stack+=4096 - (uint)stack%PGSIZE;
								int clone_pid = clone(worker, 0, stack);
								assert(clone_pid > 0);
								while(global != 5) ;
								test_passed();
								exit();
}

void worker(void *arg_ptr){
								assert(global == 13);
								assert(arg_ptr == 0);
								global = 5;
								assert(global == 5);
								exit();
}
