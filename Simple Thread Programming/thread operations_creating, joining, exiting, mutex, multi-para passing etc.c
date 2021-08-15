#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // to support sin() and cos()
#include <time.h> // to set random seed
#include <unistd.h> //to support sleep()

//use gcc ./source.c -lm -lpthread -o ./exefilename to compile!

#define N_THREADS 100
#define CHECK_ERROR_OCCUR(RET, FUNC, ACTION) if(RET) \
{\
    fprintf(stderr, "ERROR! "FUNC" returns %d when "ACTION".\n", RET);\
    exit(EXIT_FAILURE);\
}

//Struct pack_t defines the parameter package, which is used in passing
//multiple parameters:
struct pack_t{
    int n_threads;
    pthread_t * thread_list;
};

//Global mutex variable (mutex) is used to protect shared data when multiple
//writes occur.
pthread_mutex_t mutex;

/*  Concurrency_routine accept the address of the index counter (shared data).
It uses mutex to lock the counter when copying the value to the thread's own local
variable, which is stored in its own stack. It will print messages and do a simple
calculation. Then the thread will exit.
*/
void * concurrency_routine(void * in) {
    pthread_mutex_lock(&mutex);
    int index = (*(int *)in)++;
    pthread_mutex_unlock(&mutex);
    double res = 0.0;
    printf("Concurrency routine %d is running.\n", index);

    for(int i = 0; i < 100000; ++i)
        res += sin((double)i) + cos((double)i);
    printf("Concurrency routine %d has finished. The result is %lf .\n", index, res);
    pthread_exit(NULL);
}

/*  Stopwatch_routine accept the address of the multi-para package, which includes
the number of threads to create and the pthread_t array address. It will calculate
for how long the stopwatch_routine thread runs, using clock(). Then the thread will
exit.
*/
void * stopwatch_routine(void * pack) {
    int n = ( (struct pack_t *)pack )->n_threads;
    pthread_t * list = ( (struct pack_t *)pack )->thread_list;
    int rv_create, thread_index = 0;
    static clock_t clocks;
    clocks = clock(); //Initialisation of local variables is excluded.
    for(int i = 0; i < n; ++i) {
        rv_create = pthread_create(list + i, NULL, concurrency_routine, &thread_index);
        CHECK_ERROR_OCCUR(rv_create, "pthread_create()", "creating concurrency threads")
    }
    clocks = clock() - clocks;
    pthread_exit(&clocks);
}

int main(int argc, char *argv[]) {
    //initialisation of pthread_t, pthread_attr_t and mutex vars :
    pthread_t stopwatch_thread, thread[N_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&mutex, NULL);

    struct pack_t pack;
    void * clocks;
    int rv_create, rv_join;

    pack.n_threads = N_THREADS;
    pack.thread_list = thread;
    printf("Creating stopwatch_thread...\n");
    rv_create = pthread_create(&stopwatch_thread, &attr, stopwatch_routine, &pack);
    CHECK_ERROR_OCCUR(rv_create, "pthread_create()", "creating stopwatch_thread")

    printf("Joining stopwatch_thread to main...\n");
    //pthread_join, start a new thread and block the calling thread - main,
    //until the new thread exits.
    //YOU CAN SEE HOW RETURN VALUE IS TRANSMITTED:
    rv_join = pthread_join(stopwatch_thread, &clocks);
    CHECK_ERROR_OCCUR(rv_join, "pthread_join", "joining stopwatch_thread to main")

    getchar(); // protect mutex variable from being destroyed while still in use
    printf("The stopwatch_thread takes %lf second(s) to finish.\n", *(clock_t *)clocks / (double)CLOCKS_PER_SEC);
    pthread_mutex_destroy(&mutex);
    pthread_attr_destroy(&attr);

    //use pthread_exit() in main to support running unfinished subthreads when all else in main is done.
    pthread_exit(NULL);
}
