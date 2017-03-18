#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"
#include "stack.h"
#include "queue.h"
#include "integer.h"
#include "real.h"
#include "strings.h"
#include "read.h"

void readInts(queue *q, FILE *fp)
{
	int x = readInt(fp);
	while(!feof(fp))
	{
		enqueue(q,newInteger(x));
		x = readInt(fp);
	}
}

void readReals(queue *q, FILE *fp)
{
	double x = readReal(fp);
	while(!feof(fp))
	{
		enqueue(q,newReal(x));
		x = readReal(fp);
	}
}

void readStrings(queue *q, FILE *fp)
{
	char *x = readString(fp);
	while(!feof(fp))
	{
		enqueue(q,newString(x));
		x = readString(fp);
	}
}