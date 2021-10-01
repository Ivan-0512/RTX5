
#include "utility.h"

void
uMemSet(void *s, char val, size_t n)
{
	size_t cnt;
	
	while(n--) {
		*(char *)s++ = val;
	}
}


