#ifndef _RANDOM_H
#define _RANDOM_H
#include "types.h"
/**
 * Returns an int based on an array of the 4096 numbers generated from an intial seed fed to srand
 * See http://school.anhb.uwa.edu.au/personalpages/kwessen/shared/Marsaglia03.html
*/

#define PHI 0x9e3779b9 // the golden ratio
#define SEED_SIZE 0x00001000 // sets seed array size to 4096

static uint Q[SEED_SIZE];
static uint c = 710004734; // initial random number (from random.org)

// Creates seed array
static void srand(uint x)
{
	int i;

	Q[0] = x;
	Q[1] = x + PHI;
	Q[2] = x + PHI * 2;

	for (i = 3; i < SEED_SIZE; i++) {
			Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
    }
}

static uint rand(void)
{
	unsigned long long t, a = 809430660LL;
	static uint i = SEED_SIZE - 1;
	uint x, r = 0xfffffffe;
	i = (i + 1) & (SEED_SIZE - 1);
	t = a * Q[i] + c;
	c = (t >> 32);
	x = t + c;
	if (x < c) {
	    x++;
	    c++;
	}
	return (Q[i] = r - x);
}
#endif