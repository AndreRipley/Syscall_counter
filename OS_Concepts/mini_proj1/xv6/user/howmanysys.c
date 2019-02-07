#include "types.h"
#include "user.h"

int main(void) {
    printf(1, "There have been %d system calls made.\n", howmanysys());
    exit();
}
