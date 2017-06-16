#include "plock.h"                                                                                            
                                                                                                              
plock_t *priority_lock;      /* global lock shared among worker threads */                                    
                                                                                                              
void *worker( void *args ){                                                                                   
  int thread_id = *( (int *) args );                                                                          
  int priority  = *( ( (int *) args ) + 1 );                                                                  
  plock_enter( priority_lock, priority );                                                                     
  printf( "thread %d starts with priority %d\n", thread_id, priority );                                       
  sleep( 1 );                                                                                                 
  printf( "thread %d ends\n", thread_id );                                                                    
  plock_exit( priority_lock );                                                                                
  pthread_exit( NULL );                                                                                       
}    

int main( int argc, char **argv ){                                                                            
  pthread_t threads[20];                                                                                      
  int i;                                                                                                      
  int rc;                                                                                                     
  int args[20][2] =            /* pairs of thread id and priority */                                          
    { {  0,  1 }, {  1,  2 }, {  2,  3 }, {  3,  4 }, {  4,  5 },                                             
      {  5, 6 }, {  6, 7 }, {  7, 8 }, {  8, 9 }, {  9, 10 },                                             
      { 10,  11 }, { 11,  12 }, { 12,  13 }, { 13,  14 }, { 14,  15 },                                             
      { 15, 16 }, { 16, 17 }, { 17, 18 }, { 18, 19 }, { 19, 20 }  };                                          
                                                                                                              
  priority_lock = plock_create();                                                                             
                                                                                                              
  for( i = 0; i < 20 ; i++ ){                                                                                 
    rc = pthread_create( &threads[i], NULL, &worker, (void *)( args[i] ) );                                   
    if( rc ){ printf( "** could not create thread %d\n", i ); exit( -1 ); }                                   
    if( ( i & 3 ) == 0 ) sleep( 1 );                                                                          
  }                                                                                                           
                                                                                                              
  for( i = 0; i < 20; i++ ){                                                                                  
    rc = pthread_join( threads[i], NULL );                                                                    
    if( rc ){ printf( "** could not join thread %d\n", i ); exit( -1 ); }                                     
  }                                                                                                           
                                                                                                              
  plock_destroy( priority_lock );                                                                             
                                                                                                              
  return 0;                                                                                                   
}    
