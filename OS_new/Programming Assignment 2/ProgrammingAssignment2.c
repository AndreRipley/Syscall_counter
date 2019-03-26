// Cody Carroll
// Programming Assignment 2
// Fall 2018

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *fib;
int cIndex;

// Start of the child function
void *findFib() {
    if (cIndex == 0)
        fib[cIndex] = 0;
    else if (cIndex == 1)
        fib[cIndex] = 1;
    else
        fib[cIndex] = fib[cIndex - 2]
                     + fib[cIndex - 1];
    pthread_exit(0);

}

// Start of the parent function
int main(int argc, char *argv[]) { // Argc the number of arguments argv

    int z;

    // Error if you don't input a number between 1-47
    if ((z = atoi(argv[1])) < 0 || (z > 47)) {
        printf("There is an error, please enter a number between 1-47 \n"); // Output if you don't input a number between 1-47
        return -1;
    }

    // Allocating of memory for the fib sequence
    fib = malloc(z * sizeof(int)); // Size of the memory
    pthread_t *p = malloc(z * sizeof(pthread_t));

    // Creation of the thread of numbers and joining the thread to proc
    for (cIndex = 0; cIndex < z; cIndex++) {
        pthread_create(&p[cIndex], NULL, findFib, NULL);
        pthread_join(p[cIndex], NULL);
    }

    for (cIndex = 0; cIndex < z; cIndex++)
        printf("%d ", fib[cIndex]);

    // Exit
    printf("\n");
    return 0;

}
