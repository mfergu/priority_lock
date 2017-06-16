#include "plock.h"

typedef plock_t P;
typedef node_t N;

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

P *plock_create(){
	P* temp = malloc(sizeof(P));
	temp->head = malloc(sizeof(N));
	pthread_mutex_init(&temp->mlock, NULL);
	temp->value = FREE;	
	temp->head->priority = 0;
	temp->head->next = temp->head;
	return temp;
}

void plock_destroy( P *lock ){
	if(lock->head->next != lock->head){
		N* temp = lock->head->next;
		if(lock->head->next->next != lock->head){
			lock->head->next = lock->head->next->next;
			plock_destroy(lock);
		}
		free(temp);	
	} else {
		pthread_mutex_destroy(&lock->mlock);
		free(lock);
	}
}

void plock_enter( P *lock, int priority ){
	if(lock->value == BUSY) {
		N* new_node = malloc(sizeof(N));
		new_node->priority = priority;
		pthread_cond_init(&new_node->waitCV, NULL);
		
		//add to queue w/ appropriate priority, wait on cv
		N* temp = lock->head->next;
		N* temp_prev = lock->head;
		//if new node has lower priority go to the next node in the list until it reaches the head 
		while((new_node->priority <= temp->priority) && (temp != lock->head)){
			temp_prev = temp_prev->next;
			temp = temp->next;
		}
		// new node has greater priority than temp
		temp_prev->next = new_node;
		new_node->next = temp;
		pthread_cond_wait(&new_node->waitCV, &lock->mlock);
	} else {
		lock->value = BUSY;
		pthread_mutex_lock(&lock->mlock);
	}
}

void plock_exit( P *lock ){
	pthread_mutex_unlock(&lock);
	if(lock->head->next != lock->head) {
		N* temp = lock->head->next;
		lock->head->next = lock->head->next->next;
		pthread_cond_signal(&temp->waitCV);
	} else {
		lock->value = FREE;
	}

}
