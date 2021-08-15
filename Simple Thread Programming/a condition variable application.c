#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //support for clock() and CLOCKS_PER_SEC
#include <stdbool.h> // support for bool vars

/* In this program, we create two sorts of threads. One is the watch thread which
  monitors the value of the count variable, the other are increase threads which
  increase the value of count. When count reaches its limit, the watch thread
  immediately stops all the increase threads from increasing the value of count
  and tells them to 'die'. Time consumption of the watch thread is measured.
  Condition variable is applied in the monitoring part.
*/

#define N_THREAD 10
/* ERROR_CHECK example:
ERROR_CHECK("*** failure", "main()", rv != 0, "%d", rv)
*/
#define ERROR_CHECK(ERROR_DESCRIPT, FUNCTION_NAME, CONDITION, PRINT_RET_VAL, RET_VAL) if(CONDITION)\
{\
    fprintf(stderr, FUNCTION_NAME" : "ERROR_DESCRIPT" , return value is "\
            PRINT_RET_VAL"\n", RET_VAL);\
    exit(EXIT_FAILURE);\
}

/* global data */
int count = 0;
int cur_thread_id = 0;
bool inc_cannot_run = true;
pthread_mutex_t mutex_count;
pthread_cond_t cond_count_value;

void * watch_routine(void * in) {
    clock_t * clocks = (clock_t *)malloc(sizeof(clock_t));
    ERROR_CHECK("memory allocation error", "malloc()", clocks == NULL, "%p", clocks)

    *clocks = clock();
    int count_limit = *(int *)in, thread_id = cur_thread_id++, rv;
    printf("Created Watch Thread (ID %d).\n", thread_id);

    printf("Watch_routine starts working. Thread ID %d and count_limit is %d\n", thread_id, count_limit);
    inc_cannot_run = false; //allow inc threads to continue to run
    rv = pthread_mutex_lock(&mutex_count);
    ERROR_CHECK("mutex lock failure", "pthread_mutex_lock()", rv, "%d", rv )
    while(count < count_limit) {
        printf("Thread ID %d: Limit not reached. It is %d now. Going to wait!\n", thread_id, count);
        pthread_cond_wait(&cond_count_value, &mutex_count);
        //Wait, unlocks mutex_count and lets other threads to run and lock it.
        //Not until signal is received and mutex_count is unlocked can this watch thread continue.
        printf("Thread ID %d: Signal received and waiting quited. Now going on!\n", thread_id);
    }
    printf("Thread ID %d: Limit reached. It is %d now. Going to exit!\n", thread_id, count);
    pthread_mutex_unlock(&mutex_count);
    *clocks = clock() - *clocks;
    pthread_exit(clocks); //pointer clocks can be returned to the pointer given in pthread_join()
}

void * inc_routine(void * in) {
    while(inc_cannot_run) continue; //this way, inc threads are blocked when watch thread is not ready

    int count_limit = *(int *)in, thread_id = cur_thread_id++, rv;
    int loop_limit = count_limit / N_THREAD + 1;
    printf("Created Inc Thread (ID %d).\n", thread_id);

    for(int i = 1; i <= loop_limit; ++i) {
        pthread_mutex_lock(&mutex_count);
        if(count < count_limit) ++count;
        else {
            printf("Thread ID %d : count limit reached and it is %d now. Going to exit.\n", thread_id, count);
            pthread_mutex_unlock(&mutex_count);
            break;
        }
        printf("Thread ID %d : count increased and it is %d now.\n", thread_id, count);
        pthread_cond_signal(&cond_count_value);
        pthread_mutex_unlock(&mutex_count);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[N_THREAD], thread_watch;
    pthread_attr_t attr;

    /*initialisation of pthread_..._t vars*/
    pthread_mutex_init(&mutex_count, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_cond_init(&cond_count_value, NULL);

    /*Here comes the work~~*/
    int count_limit = 0, rv;
    clock_t * clocks_of_watch;
    printf("The count value is now %d. Several threads are going to increase it.\n", count);
    printf("Please set the limit of the value (larger than 0): ");
    scanf("%d", &count_limit);
    while(getchar() != '\n') continue;

    rv = pthread_create(&thread_watch, &attr, watch_routine, &count_limit);
    ERROR_CHECK("thread creation failure", "pthread_create()", rv, "%d", rv)
    for(int i = 0; i < N_THREAD; ++i) {
        rv = pthread_create(&threads[i], &attr, inc_routine, &count_limit);
        ERROR_CHECK("thread creation failure", "pthread_create()", rv, "%d", rv)
    }
    rv = pthread_join(thread_watch, (void **)&clocks_of_watch );

    getchar(); //prevent destruction while vars are in use
    //is getchar() necessary?
    printf("Watch_routine runs approximately for %lf seconds.\n", *clocks_of_watch / (double)CLOCKS_PER_SEC);
    /*destruction and exit*/
    free(clocks_of_watch);
    pthread_cond_destroy(&cond_count_value);
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&mutex_count);
    pthread_exit(NULL);
}
