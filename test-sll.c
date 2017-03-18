#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "sll.h"
#include "integer.h"

	void Fatal(char *,...);

   static void showItems(sll *items)
       {
       printf("The items are ");
       displaySLL(stdout,items);
       printf(".\n");
       }

   int main()
      {
		       sll *a = newSLL(displayInteger);
    insertSLL(a,0,newInteger(71));
    removeSLL(a,0);
    insertSLL(a,0,newInteger(0));
    insertSLL(a,1,newInteger(21));
    removeSLL(a,1);
    removeSLL(a,0);
    insertSLL(a,0,newInteger(70));
    insertSLL(a,0,newInteger(63));
    insertSLL(a,1,newInteger(49));
    insertSLL(a,1,newInteger(92));
    insertSLL(a,4,newInteger(13));
    removeSLL(a,2);
    removeSLL(a,3);
    removeSLL(a,0);
    insertSLL(a,1,newInteger(8));
    insertSLL(a,0,newInteger(29));
    insertSLL(a,0,newInteger(47));
    insertSLL(a,0,newInteger(45));
    insertSLL(a,0,newInteger(1));
    insertSLL(a,7,newInteger(5));
    removeSLL(a,2);
    removeSLL(a,0);
    insertSLL(a,6,newInteger(93));
    insertSLL(a,3,newInteger(58));
    removeSLL(a,1);
    insertSLL(a,5,newInteger(91));
    insertSLL(a,7,newInteger(63));
    insertSLL(a,6,newInteger(61));
    displaySLL(stdout,a);

    return 0;
      }

       
void Fatal(char *fmt, ...)
    {
    va_list ap;

    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
    }