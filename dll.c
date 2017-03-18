#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dll.h"

dll *newDLL(void (*d)(FILE *,void *)) //d is the display function
{
    dll *items = malloc(sizeof(dll));
    if (items == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    items->head = 0;
    items->tail = 0;
    items->size = 0;
    items->display = d;
    return items;
}

void insertDLL(dll *items,int index,void *value)
{
    dllnode *p = malloc(sizeof(dllnode));  //New node created

    if (p == 0)
    {
        fprintf(stderr,"out of memory");
        exit(-1);
    }

    p->value = value;     //New node value assigned

    //Inserting at head
    if(index == 0 && items->head == NULL)
    {
        p->next = items->head;
        p->prev = NULL;
        items->head = p;
        items->tail = p;
    }
    else if(index == 0 && items->head != NULL)
    {
        p->next = items->head;
        items->head->prev = p;
        p->prev = NULL;
        items->head = p;
    }
    //Done inserting at head

    //Inserting at tail
    else if(index == items->size)
    {
        p->next = NULL;
        p->prev = items->tail;
        items->tail->next = p;
        items->tail = p;
    }
    //End inserting at tail

    //Inserting between head and tail
    else
    {
        if(index > items->size/2)
        {
            int i;
            dllnode *pre, *post;
            post = items->tail;
            for (i = 0; i < (items->size - index)-1; ++i)
            {
                post = post->prev;
            }
            pre = post->prev;
            post->prev = p;
            pre->next = p;
            p->prev = pre;
            p->next = post;
        }

        else
        {
            int i;
            dllnode *pre, *post;
            pre = items->head;
            for (i = 0; i < index-1; ++i)
            {
                pre = pre->next;
            }
            post = pre->next;
            pre->next = p;
            post->prev = p;
            p->next = post;
            p->prev = pre;
        }

    }
    //End inserting between head and tail
    items->size++;
}

void *removeDLL(dll *items,int index)
{
    if(index == 0  && items->size > 1)  //Removes head with more than one node
    {
        dllnode *temp = items->head;
        items->head = items->head->next;
        temp->next = NULL;
        items->head->prev = NULL;
        items->size--;
        return temp->value;
    }
    else if(index == 0 && items->size ==1)  //Removes head with one node in list
    {
        dllnode *temp = items->head;
        items->head = NULL;
        items->tail = NULL;
        items->size = 0;
        return temp->value;
    }

    else if(index == items->size -1)  //Removes Tail
    {
        dllnode *temp = items->tail;
        items->tail = items->tail->prev;
        items->tail->next = NULL;
        temp->prev = NULL;
        items->size--;
        return temp->value;
    }

    else if(index > items->size/2)  //Removes from upper middle
    {
        dllnode *pre,*post, *temp = items->tail;
        int i;
        for (i = 0; i < (items->size - index)-1; ++i)
        {
            temp = temp->prev;
        }
        post = temp-> next;
        pre = temp->prev;
        post->prev = pre;
        pre->next = post;
        temp->next = NULL;
        temp->prev = NULL;
        items->size--;
        return temp->value;
    }

    else if(index <= items->size/2)  //Removes from lower middle
    {
        dllnode *pre,*post, *temp = items->head;
        int i;
        for (i = 0; i < index; ++i)
        {
            temp = temp->next;   
        }
        post = temp-> next;
        pre = temp->prev;
        post->prev = pre;
        pre->next = post;
        temp->next = NULL;
        temp->prev = NULL;
        items->size--;
        return temp->value;
    }
    return 0;
}
void unionDLL(dll *recipient, dll *donor)
{
    //Merge Lists
    if(recipient->size != 0 && donor->size != 0)
    {
        recipient->tail->next = donor->head;
        donor->head->prev = recipient->tail;
        recipient->tail = donor->tail;
        recipient->size = recipient->size + donor->size;
    }
    else if(recipient->size ==0)
    {
        recipient->head = donor->head;
        recipient->tail = donor-> tail;
    }
    //Empty Donor
    donor->head = NULL;
    donor->tail = NULL;
    donor->size = 0;

}

void *getDLL(dll *items,int index)
{  
    if(index > items->size/2)
    {
        dllnode *temp=items->tail;
        int i;
        for (i = 0; i < (items->size-index)-1; ++i)
        {
            temp = temp->prev;
        }
        return temp->value;
    }
    else
    {
        dllnode *temp=items->head;
        int i;
        for (i = 0; i < index; ++i)
        {
            temp = temp->next;
        }
        return temp->value;
    }
}

int sizeDLL(dll *items)
{
    return items->size;
}

void displayDLL(FILE *fp, dll *items)
{
    dllnode *temp;
    temp = items->head;

    fprintf(fp,"[");
    while(temp != NULL)
    {
        items -> display(fp,temp->value);
        if(temp->next != NULL)
        {
            fprintf(fp,",");
        }
        temp = temp -> next;
    }
    fprintf(fp,"]");
}