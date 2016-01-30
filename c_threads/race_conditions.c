#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>


struct job{
    struct job* next;
};

struct job* job_queue;

pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t job_queue_count;

// one time init of job queue
void init_job_queue(){
    job_queue = NULL;
    int value;

    sem_init(&job_queue_count, 0,0);
}

//process the queue untill its empty 

void* thread_function (void* args){
    while(1){
        struct job* next_job;

        sem_wait(&job_queue_count);

        pthread_mutex_lock (&job_queue_mutex);

        next_job = job_queue;

        job_queue = job_queue->next;

        pthread_mutex_unlock (&job_queue_mutex);

        printf("value %d\n", next_job->value);
    }

    return NULL;
}

void enqueue_job (int data){
    struct job* new_job;

    new_job = (struct job*) malloc (sizeof(struct job));
    new_job.value = 5;

    pthread_mutex_lock (&job_queue_mutex);

    //adding a new job to the head of the linked list
    
    new_job->next = job_queue;
    job_queue = new_job;

    // let other threads know that there are jobs in the queue 
    // one of the threads that was blocked, now has the ability to consume the job;
    sem_post(&job_queue_count);

    pthread_mutex_unlock(&job_queue_mutex);
}

int main (){

}
