/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
      return NULL;
    } else {
      q->head = NULL;
      q->tail = NULL;
      q->size = 0;
      return q;  
    }
    
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) {
      return;
    }

    list_ele_t *cur = q->head;
    list_ele_t *next;
    while (cur != NULL) {
      next = cur->next;
      cur->next = NULL;
      free(cur);
      cur = next;
    }
    
    /* How about freeing the list elements? */
    /* Free queue structure */
    q->head = NULL;
    q->tail = NULL;
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    if (q == NULL) {
      return false;
    }
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
      return false;
    }
    /* What if malloc returned NULL? */

    // 使newh成为链表的第一个节点
    newh->value = v;
    newh->next = q->head;
    q->head = newh;

    // 插入头部时更新size
    q->size++;
    // 如果是第一个节点，则尾部也指向该节点
    if (q->tail == NULL) {
      q->tail = newh;
    }
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    if (q == NULL) {
      return false;
    }
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) {
      return false;
    }
    newt->value = v;
    newt->next = NULL;

    // 如果是第一个元素，则head和tail指针都指向该元素
    if (q->tail == NULL) {
      q->tail = newt;
      q->head = newt;
    } else {
      // 如果不是第一个元素 将尾部的元素的next指向新分配的节点，tail指向新尾部
      q->tail->next = newt;
      q->tail = newt;
    }
    q->size++;
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if (q == NULL || q->head == NULL) {
      return false;
    }
    /* You need to fix up this code. */
    if (vp != NULL) {
      *vp = q->head->value;
    }
    // 将第一个元素从链表中断开
    list_ele_t *oldh = q->head;
    q->head = oldh->next;
    q->size--;
    oldh->next = NULL;
    
    // 删除head时，可能改变tail
    if (q->size == 0) {
      q->tail = NULL;
    }
    free(oldh);
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
    if (q == NULL || q->head == NULL) {
      return 0;
    } else {
      return q->size;
    }
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->head == NULL) {
      return;
    }
    // 单链表逆序
    list_ele_t* before = NULL; 
    list_ele_t* cur = q->head;
    list_ele_t* next = cur;
    while (cur != NULL) {
        next = cur->next;
        cur->next = before;
        before = cur;
        cur = next;
    }
    // 交换q->head和q->tail的指向
    list_ele_t *tmp = q->head;
    q->head = q->tail;
    q->tail = tmp;
    /* You need to write the code for this function */
}

