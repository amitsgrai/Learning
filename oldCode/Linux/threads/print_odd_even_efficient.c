#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;
void *functionCount1();
void *functionCount2();
int count = 0;
#define COUNT_DONE 10

int main()
{
 pthread_t thread1, thread2;
 pthread_create( &thread1, NULL, &functionCount1, NULL);
 pthread_create( &thread2, NULL, &functionCount2, NULL);
 pthread_join( thread1, NULL);
 pthread_join( thread2, NULL);
 return 0;
}

// Print odd numbers
void *functionCount1()
{
//  static int i;
   printf("AR: this is function1\n");
  for(;;) {
   // Lock mutex and then wait for signal to relase mutex
   printf("AR: for loop 1\n");
   pthread_mutex_lock( &count_mutex );
   if ( count % 2 != 0 ) { //odd value
   printf("Counter value functionCount1 ODD: %d\n",count);
     pthread_cond_wait( &condition_var, &count_mutex );
   printf("AR: after cond wait in FunctCount1\n");
   }

   printf("AR: after if condition in FunctCount1\n");
   count++;
   pthread_cond_signal( &condition_var );
  // i++;
   if ( count >= COUNT_DONE ) {
     pthread_mutex_unlock( &count_mutex );
     return(NULL);
   }
//	printf("the value of lock is odd lock:%d\n",i);
   pthread_mutex_unlock( &count_mutex );
 }
}

// print even numbers
void *functionCount2()
{
//	static int i;
   printf("AR: this is function2\n");
  for(;;) {
   printf("AR: for loop 2\n");
  // Lock mutex and then wait for signal to relase mutex
  pthread_mutex_lock( &count_mutex );
//	i++;
  if ( count % 2 == 0 ) { //Even value
  printf("Counter value functionCount2 EVEN: %d\n",count);
    pthread_cond_wait( &condition_var, &count_mutex );
   printf("AR: after cond wait in FunctCount2\n");
  } 
   printf("AR: after if condition in FunctCount2\n");
  count++;
  pthread_cond_signal( &condition_var );
  if( count >= COUNT_DONE ) {
    pthread_mutex_unlock( &count_mutex );
    return(NULL);
  }
//	printf("the value of lock even lock:%d\n",i);
  pthread_mutex_unlock( &count_mutex );
 }
}
