/**
 * @file    main.c
 * @author  Kaihsin Lin
 * @brief   多 threads 與彼此的競爭關係
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>


int global_var = 0;

typedef struct {
    char thread_name[128];
    int increase_num;
    int interval;
    int rounds;
} IncreaseStruct;


void* increase_func(void* arg)
{
    IncreaseStruct *increase_args = (IncreaseStruct *) arg;
    for (int i = 0; i < increase_args->rounds; i++)
    {
        // sleep(increase_args->interval);
        global_var += increase_args->increase_num;
        // printf("Thread [%s]: +%d, global_var = %d\n", increase_args->thread_name, increase_args->increase_num, global_var);
    }
    return NULL;
}

int main(void)
{
    
    pthread_t tid_alpha;

    IncreaseStruct *a_arg = malloc(sizeof(IncreaseStruct));
    strcpy(a_arg->thread_name, "Alpha");
    a_arg->increase_num = 2;
    a_arg->interval = 1;
    a_arg->rounds = 1000000;

    pthread_t tid_beta;

    IncreaseStruct *b_arg = malloc(sizeof(IncreaseStruct));
    strcpy(b_arg->thread_name, "Beta");
    b_arg->increase_num = 5;
    b_arg->interval = 3;
    b_arg->rounds = 1000000;

    printf("Before thread, global_var = %d\n", global_var);

    pthread_create(&tid_alpha, NULL, increase_func, a_arg);
    pthread_create(&tid_beta, NULL, increase_func, b_arg);
    pthread_join(tid_alpha, NULL);
    pthread_join(tid_beta, NULL);

    free(a_arg);
    free(b_arg);

    printf("Final global_var = %d", global_var);
    printf(", while global_var should be \"%d\"\n", 
        a_arg->increase_num * a_arg->rounds 
        + b_arg->increase_num * b_arg->rounds
    );

    return 0;
}