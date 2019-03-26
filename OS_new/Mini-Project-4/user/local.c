#include "assert.h"
// Custom test

int global = 1;
void worker(void*arg_ptr)
{
	int arg = *(int*) arg_ptr;
	assert(arg == 42);
	assert(global == 1);
	global = 5;
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

	while(global != 5);
	test_passed();
	exit();
}
