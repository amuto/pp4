#include <stdlib.h>
#include <stdio.h>
#include "basetypes.h"

int na;

/* Mokuteki: start ni hajimari, required jikan no jikkou wo suru, atarashi process no PCB wo tukuri, sore wo kaesu */
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

/* Mokuteki:  q no saigo ni pcb wo tuika suru. return void */
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

/* Mokuteki:  q no sentou no PCB wo return site, q ha sentou no ikko wo totta nokori ni naru */
PCB *pcb_dequeue(PCB **q)
{
  PCB *pcb;
  if (! q)
    return NULL;
  pcb = *q;
  *q = pcb->next;
  return p;
}

/* Mokuteki: q no nakakara start_time ga t no monowo subete sakujo suru */
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

/* Mokuteki: q no nakakara p wo sagashite sakujo suru */
void pcb_remove(PCB *p, PCB **q)
{
  PCB *n, *b;
  if (*q == NULL){		/* tokubetu na baai 1 */
      return;
  }
  if (*q == p) {		/* tokubetu na baai 2 */
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

/* Mokuteki: PCB no queue no sentou top ga ataeraretara queue no juni PCB wo hyouji suru */
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

int
main (void)
{
  PCB *q1 = NULL;
  printf("OK\n");

  return 0;
}
