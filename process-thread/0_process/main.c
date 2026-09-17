/**
 * @file    main.c
 * @author  Kaihsin Lin
 * @brief   驗證 Process 之間，記憶體是隔離的
 */

#include <stdio.h>
#include <unistd.h>


int global_var = 100;

int main(void)
{
    printf("\r\nBefore fork, global_var = %d, PID = %d\r\n", global_var, getpid());

    pid_t pid = fork();

    if (pid == 0)
    {
        // 子 process
        global_var = 999;
        printf("Child (PID %d): global_var = %d\n", getpid(), global_var);
    }
    else
    {
        // 父 process
        sleep(1);
        printf("Parent (PID %d): global_var = %d\n", getpid(), global_var);
    }

    return 0;
}