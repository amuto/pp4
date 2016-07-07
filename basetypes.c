#include <stdlib.h>
#include <stdio.h>
#include "basetypes.h"

int na;
int q;

/* 目的: start に始まり, required　時間の実行をする,  新しいプロセスの PCB を作り, それを返す */
PCB *pcb_new (int start, int required)
{
  PCB *p = (PCB *)malloc(sizeof(PCB));
  p->next = NULL;
  p->pid = 0;			/* 1 */
  p->state = READY;
  p->waiting_time = 0;
  p->executed_time = 0;
  p->start_time = start;	 /* 2 */
  p->required_time = required; /* 3 */
  return p;
}

/* 目的:  q の最後に pcb を追加する. void を返す*/
void pcb_enqueue(PCB *p, PCB **q)
{
  if (*q == p) {
    printf("hen!!!\n");
    exit(0);
  }
  p->next = NULL;
  if (! *q)
    *q = p;
  else {
    PCB *p = *q;
    while (p->next != NULL) {
      p = p->next;
    }
    if (p->next == p) {
      printf("hen!!!\n");
      exit(0);
    }
    p->next = p;
  }
}

/* 目的:  q の先頭の PCB を return して, q は先頭の一個を取った残りになる */
PCB *pcb_dequeue(PCB **q)
{

  int p;
  PCB *q;
  PCB *pcb;
  if (! q)
    return NULL;
  pcb = *q;
  *q = pcb->next;
  return p;
}

/* 目的: q の中から start_time が t のものを全て削除する*/
void pcb_removeAllStartAt(int t, PCB **q)
{
  PCB *n, *b;
  if (*q == NULL){
      return;
  }
  b = *q;
  n = b->next;
  while (n != NULL) {
    if(n->start_time == t) {
      b->next = n->next->next;
      n->next = NULL;
      n = n->next;
      continue;
    } else {
      b = n;
      n = n->next;
    }
  }
}

/* 目的: q の中から p を探して削除する */
void pcb_remove(PCB *p, PCB **q)
{
  PCB *n, *b;
  if (*q == NULL){		/* 特別な場合 1 */
      return;
  }
  if (*q == p) {		/* 特別な場合 2 */
      *q = (*q)->next;
      return;
  }
  b = *q;
  n = b->next;
  while (n != NULL) {
    if(p == n) {
      b->next = n->next->next;
      n->next = NULL;
      break;
    } else {
      b = n;
      n = n->next;
    }
  }
}

/* 目的: PCB の queue の先頭 top が与えられたら queue の順に PCB を表示する */
void pcb_print_list(PCB *top)
{
  if (top == NULL) {
    printf("[]");
  }
  else {
    while(top != NULL){
      printf("[pid%d,%d,%d]", top->pid, top->start_time, top->required_time);
      top=top->next;
      if (top)
	printf(", ");
    }
  }
  printf("\n");
}
