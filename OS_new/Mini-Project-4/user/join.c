#include "assert.h"
// Test 6 - clone and join syscall
//

int global = 1;
void worker(void*arg_ptr)
{
								int arg = *(int*) arg_ptr;
								assert(arg == 42);
								assert(global == 1);
								global++;
}

int main()
{
								void *stack = malloc(PGSIZE*2);
								assert(stack != NULL);
								if((uint)stack %PGSIZE)
																stack = stack + (4096 - (uint)stack% PGSIZE);

								int arg = 42;

								int clone_pid = clone(worker, &arg, stack);
								assert(clone_pid > 0);
								assert(clone_pid > 3);

								void *join_stack;
								int join_pid = join(&join_stack);
								assert(join_pid == clone_pid);
								assert(stack == join_stack);
								assert(global == 2);

								test_passed();
								exit();
}
