#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
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
    /* Free queue structure */
    if (!q)
        return;
    while (q->head) {
        list_ele_t *tmp = q->head->next;
        free(q->head);
        q->head = tmp;
    }
    free(q->tail);
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    size_t length = strlen(s) + 1;
    if (!newh)
        return false;
    newh->value = malloc(length * sizeof(char));
    if (!newh->value) {
        free(newh);
        return false;
    }
    memcpy(newh->value, s, length);
    newh->next = q->head;
    if (!q->head)
        q->tail = newh;
    q->head = newh;
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    size_t length = strlen(s) + 1;
    if (!newh)
        return false;
    newh->value = malloc(length * sizeof(char));
    if (!newh->value) {
        free(newh);
        return false;
    }
    memcpy(newh->value, s, length);
    newh->next = NULL;
    if (!q->head || !q->tail) {
        q->head = newh;
        q->tail = newh;
        return true;
    }
    q->tail->next = newh;
    q->tail = q->tail->next;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    if (!q || q->size < 1)
        return false;
    q->head = q->head->next;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return (q == NULL) ? 0 : q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || q->size <= 1)
        return;
    list_ele_t *pre = NULL;
    while (q->head) {
        list_ele_t *next = q->head->next;
        q->head->next = pre;
        if (!pre)
            q->tail = q->head;
        pre = q->head;
        q->head = next;
    }
    q->head = pre;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
