/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;
    list_ele_t *tmp;

    while (q->head != NULL) {
        tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    char *ele_val = malloc((strlen(s) + 1) * sizeof(char));
    if (!ele_val) {
        free(newh);
        return false;
    }
    memset(ele_val, '\0', strlen(s) + 1);
    strcpy(ele_val, s);
    newh->value = ele_val;
    newh->next = q->head;

    if (!q->head)
        q->tail = newh;
    q->head = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newh;
    if (!q)
        return false;

    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    char *ele_val = malloc((strlen(s) + 1) * sizeof(char));
    if (!ele_val) {
        free(newh);
        return false;
    }
    memset(ele_val, '\0', strlen(s) + 1);
    strcpy(ele_val, s);
    newh->value = ele_val;
    newh->next = NULL;

    if (!q->tail) {
        q->head = newh;
        q->tail = newh;
    }
    q->tail->next = newh;
    q->tail = newh;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q || !(q->head))
        return false;

    list_ele_t *tmp;
    tmp = q->head;
    if (sp) {
        memset(sp, '\0', bufsize);
        strncpy(sp, tmp->value, bufsize - 1);
    }
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (!q || !q->head || !q->head->next)
        return;
    list_ele_t *forward, *backward;

    backward = q->head;
    q->tail = q->head;
    q->head = q->head->next;
    forward = q->head->next;
    backward->next = NULL;

    while (forward != NULL) {
        q->head->next = backward;
        backward = q->head;
        q->head = forward;
        forward = forward->next;
    }
    q->head->next = backward;
}
