#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

void merge_sort(list_ele_t **head);

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
    list_ele_t *tmp;
    while (q->head) {
        tmp = q->head->next;
        free(q->head->value);
        free(q->head);
        q->head = tmp;
    }
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
    if (!q || q->size < 1)
        return false;
    if (sp) {
        size_t size = (bufsize > strlen(q->head->value))
                          ? strlen(q->head->value)
                          : (bufsize - 1);

        memcpy(sp, q->head->value, size);
        sp[size] = '\0';
    }

    list_ele_t *tmp = q->head->next;
    free(q->head->value);
    free(q->head);
    q->head = tmp;
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q ? q->size : 0;
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
    if (!q || q->size <= 1)
        return;
    merge_sort(&q->head);
    while (q->tail->next) {
        q->tail = q->tail->next;
    }
}

/*
 * Divide queue from mid
 * Original ELE will be cut
 * Return mid ELE
 */
list_ele_t *divide_mid_ele(list_ele_t **head)
{
    list_ele_t *one = *head;
    list_ele_t *jump = (*head)->next;
    while (jump && jump->next) {
        jump = jump->next->next;
        one = one->next;
    }
    list_ele_t *mid = one->next;
    one->next = NULL;
    return mid;
}

list_ele_t *merge(list_ele_t *list1, list_ele_t *list2)
{
    if (!list1)
        return list2;
    if (!list2)
        return list1;
    size_t len_l1 = strlen(list1->value), len_l2 = strlen(list1->value);
    if (len_l1 < len_l2)
        len_l1 = len_l2;
    if (strncmp(list1->value, list2->value, len_l1) < 0) {
        list1->next = merge(list1->next, list2);
        return list1;
    } else {
        list2->next = merge(list2->next, list1);
        return list2;
    }
}

void merge_sort(list_ele_t **head)
{
    if (!(*head) || !(*head)->next)
        return;
    list_ele_t *mid = divide_mid_ele(head);
    merge_sort(head);
    merge_sort(&mid);
    *head = merge(*head, mid);
}