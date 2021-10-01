#ifndef __UTILITY_H
#define __UTILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SIZE_T
 #define _SIZE_T
 typedef unsigned int size_t;
#endif

#ifndef NULL
 #define NULL ((void *)0)
#endif

#define ARRAYSIZE(a)    (sizeof(a) / sizeof((a)[0]))
 
void uMemSet(void *s, char val, size_t n);


#ifdef __cplusplus
}
#endif

#endif
