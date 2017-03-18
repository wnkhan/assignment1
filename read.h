#include <stdio.h>
#include "queue.h"

#ifndef __READ_INCLUDED__
#define __READ_INCLUDED__

typedef void (*Reader)(queue*,FILE*);

extern void readInts(queue *q, FILE *fp);
extern void readReals(queue *q, FILE *fp);
extern void readStrings(queue *q, FILE *fp);

#endif