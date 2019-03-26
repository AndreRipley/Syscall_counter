#ifndef __ASSERT_HEADER__
#define __ASSERT_HEADER__
#include "types.h"
#include "user.h"
#define assert(x)\
	if(!(x))\
	printf(2, "Assertion failed on line %d in file %s\n", __LINE__, __FILE__), exit();

#define test_failed()\
	printf(1, "TEST FAILED\n"), exit();

#define test_passed()\
	printf(1, "TEST PASSED\n"), exit();
#endif
