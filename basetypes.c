#include <stdlib.h>
#include <stdio.h>
#include "basetypes.h"

int na;
int q;

/* ��Ū: start �˻Ϥޤ�, required�����֤μ¹Ԥ򤹤�,  �������ץ����� PCB ����, ������֤� */
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

/* ��Ū:  q �κǸ�� pcb ���ɲä���. void ���֤�*/
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

/* ��Ū:  q ����Ƭ�� PCB �� return ����, q ����Ƭ�ΰ�Ĥ��ä��Ĥ�ˤʤ� */
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

/* ��Ū: q ���椫�� start_time �� t �Τ�Τ����ƺ������*/
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

/* ��Ū: q ���椫�� p ��õ���ƺ������ */
void pcb_remove(PCB *p, PCB **q)
{
  PCB *n, *b;
  if (*q == NULL){		/* ���̤ʾ�� 1 */
      return;
  }
  if (*q == p) {		/* ���̤ʾ�� 2 */
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

/* ��Ū: PCB �� queue ����Ƭ top ��Ϳ����줿�� queue �ν�� PCB ��ɽ������ */
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
