//Written by William Khan
//CS201 Assignment 1
//The scanner.h, scanner.c, integer.c, and integer.h file was written by John Lusth
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "strings.h"
#include "real.h"
#include "sll.h"
#include "read.h"
#include "stack.h"
#include "queue.h"
#include "integer.h"
#include "comparator.h"

typedef void (*Printer)(FILE*,void*);
static void showQueue(queue *);
// static void showStack(stack *s);
queue *sort(queue *q, Comparator c, Printer p, int *pushcount);

int main(int argc, char *argv[]){
	
	Printer print;
	Comparator comp;
	Reader reader;

		switch(argv[1][1])
		{
			case 'd':
				print = displayInteger;
				comp = intComparator;
				reader = readInts;
				break;

			case 'r':
				print = displayReal; 
				comp = realComparator;
				reader = readReals;
				break;

			case 's':
				print = displayString;
				comp = stringComparator; 
				reader = readStrings;
				break;
			case 'v':
				printf("William N. Khan\n");
				return 0;
			default:
				printf("unknown flag 'q', valid flags are -d, -r, -s, and -v\n");
				return 0;
		}

	queue *items = newQueue(print);
	FILE *fp; 
	//Standard Input
	if(argc == 2)
	{
		reader(items,stdin);
		showQueue(items);
	}
	//Input from text file
	else if(argc == 3)
	{
	
	fp = fopen(argv[2],"r");
	reader(items,fp);
	fclose(fp);
	showQueue(items);
	
	}
	int stack_push_count=1;
	int count = 0;

	while(stack_push_count!=0)
	{
		stack_push_count = 0;
		items = sort(items,comp,print, &stack_push_count);
		if (stack_push_count != 0)
		{
			showQueue(items);
		}
		else if (count == 0)
		{
			showQueue(items);
		}
		count++;
	}

		
	return 0;
}

static void showQueue(queue *s)
{ 
    displayQueue(stdout,s);
    printf("\n");
}

// static void showStack(stack *s)
// { 
//    displayStack(stdout,s);
//    printf("\n");
// }

queue *sort(queue *q, Comparator c, Printer p, int *pushcount)
{
	queue *q1 = newQueue(p);
	stack *s = newStack(p);
	void *lastin;
	void *qhead;
	
	while(sizeQueue(q)>0)
	{
		//printf("Running Sort\n");
		
		if(sizeStack(s)!=0 && sizeQueue(q1)!=0 && c(peekStack(s),peekQueue(q))>0 && c(peekStack(s),lastin) <0)
		{
			lastin = pop(s);
			enqueue(q1,lastin);
			//printf("Stack to output q\n");
		}
		else if (sizeStack(s)!=0 && sizeQueue(q1)!=0 && c(peekStack(s),peekQueue(q)) == 0)
		{
			lastin = pop(s);
			enqueue(q1,lastin);
			//printf("Stack to output q\n");
		}
		else if(sizeQueue(q)==1)
		{
			enqueue(q1,dequeue(q));
			//printf("Last input to output q\n");
		}

		else if(sizeQueue(q)>1)
		{
			qhead = dequeue(q);
			if (c(qhead,peekQueue(q))<0)
			{
				lastin = qhead;
				push(s,lastin);
				*pushcount = *pushcount + 1;
				//printf("Input q to stack\n");
			}
			else if(c(qhead,peekQueue(q))>0||c(qhead,peekQueue(q))==0)
			{
				lastin = qhead;
				enqueue(q1,qhead);
				//printf("Input q to output q\n");
			}
		}
	}
	while(sizeStack(s)!=0)
	{
		enqueue(q1,pop(s));
	}
	// printf("Input Queue");showQueue(q);
	// printf("Input Stack");showStack(s);
	// printf("Output Queue");showQueue(q1);
	// printf("\n");
	return q1;
}