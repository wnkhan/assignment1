#ifndef __DLL_INCLUDED__
#define __DLL_INCLUDED__

    typedef struct dllnode
        {
        void *value;
        struct dllnode *next;
        struct dllnode *prev;
        } dllnode;

    typedef struct dll
        {
        dllnode *head;
        dllnode *tail;
        int size;
        void (*display)(FILE *,void *);
        } dll;

extern dll *newDLL(void (*d)(FILE *,void *));            //constructor                //done
extern void insertDLL(dll *items,int index,void *value); //stores a generic value     //done
extern void *removeDLL(dll *items,int index);            //returns a generic value    //done
extern void unionDLL(dll *recipient,dll *donor);         //merge two lists into one   //done
extern void *getDLL(dll *items,int index);               //get the value at the index  //done
extern int sizeDLL(dll *items);                                                        //done
extern void displayDLL(FILE *,dll *items);                                             //done

#endif