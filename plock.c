#include "plock.h"

typedef struct plock_t T;
typedef struct node_t N;

/*
typedef struct{
  int value;          // FREE or BUSY                            
  pthread_mutex_t mlock;  // mutex protecting the plock structure    
  node_t *head;       // linked list of waiting threads          
} plock_t;

typedef struct node_def{
  int priority;       // priority of the waiting thread          
  pthread_cond_t waitCV;  // thread waits on this condition variable 
  struct node_def *next;  // node is part of a singly-linked list    
} node_t;


*/

T *plock_create(){
	T* temp = malloc(T);
	temp->value = FREE;	
	temp->mlock = PTHREAD_MUTEX_INITIALIZER;
	return temp;
}

void plock_destroy( T *lock ){

}

void plock_enter( T *lock, int priority ){

}

void plock_exit( T *lock ){

}
