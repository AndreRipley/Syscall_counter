#include "assert.h"

int ppid;
int global = 1;

void
worker(void *arg_ptr) {
        int arg = *(int*)arg_ptr;
        assert(arg == 35);
        assert(global == 1);
        global++;
        exit();
}

int
main(int argc, char *argv[])
{
        ppid = getpid();

        int arg = 35;
        int thread_pid = thread_create(worker, &arg);
        assert(thread_pid > 0);

        int join_pid = thread_join();
        assert(join_pid == thread_pid);
        assert(global == 2);

        test_passed();
        exit();
}
