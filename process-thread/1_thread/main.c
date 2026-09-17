/**
 * @file    main.c
 * @author  Kaihsin Lin
 * @brief   驗證 Thread 之間，記憶體是共享的
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


int global_var = 100;

void* thread_func(void* arg)
{
    global_var = 999;
    printf("Thread: global_var = %d\n", global_var);
    return NULL;
}

int main(void)
{
    pthread_t tid;
    printf("Before thread, global_var = %d\n", global_var);

    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_join(tid, NULL);

    return 0;
}