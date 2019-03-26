// Simple test to check if stack set up correctly
#include "assert.h"
void worker(void *arg_ptr);

int global = 1;
int
main()
{
								void *stack =
																malloc(PGSIZE*2);
								assert(stack != NULL);

								if((uint)stack%PGSIZE)
																stack +=
																								(4096-(uint)stack
																									%PGSIZE);
								int clone_pid =
																clone(worker, stack, stack);

								assert(clone_pid > 0);
								while(global != 5) ;
								test_passed();
								exit();
}

void
worker(void *arg_ptr){
								assert(*((uint*)
																	(arg_ptr +
																		PGSIZE - 8)) ==
															0xffffffff);
								assert((uint)&arg_ptr ==
															((uint)arg_ptr+
																PGSIZE-4));
								global = 5;
								exit();
}
