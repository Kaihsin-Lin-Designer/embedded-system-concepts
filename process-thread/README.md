# Process & Thread

Process and Thread is one of the fundamental concepts in Linux. 

## Process

In Linux, process is a resources-isolated unit. Every process has its own virtual memory space, such as stack, heap, .bss, etc. This isolation is enforced by the MMU (Memory Management Unit) — each process has its own page table, so one process cannot directly read or write another process's memory. This design ensures that a process would not overwrite other processes' data.

## Thread

A process can have multiple threads. Threads in the same process share almost all resources except for stack, register status, and program counter. These features enable threads to talk to each other easily and promptly.

## Concepts

### Race Condition

Since threads within a same process share resources, they might read and write same data at the same time; therefore, they might overwrite each other's updates. This is called **race condition**.


**Example:**
```
int global_var = 100

(At the same time)
[Alpha Thread]  global_var += 200
[Beta Thread]   global_var += 300
```

In this example, we expect `global_var` to be `600`. However, due to the race condition, we cannot assure whether the operations in these threads are overwritten by each other or not. In this case, `global_var` might be `600`, `300`, or `400`.

This is something that we want to avoid in our programs, because well written programs are predictable.


### Mutex Lock

If you've already learned SQL, you may find that race condition also happen in transactions. If multiple requests perform CRUD to the same data at a time, some of those updates are likely to be lost. Programers came up with transaction lock in SQL, and we also have **Mutex Lock** in C, which blocks other threads from entering the critical section while one 
thread is holding the lock.

```c
#include <pthread.h>

...

int global_var = 100;
pthread_mutex_t lock;

...

void* thread_func(void* arg)
{
    ...

    pthread_mutex_lock(&lock);

    /**
     * update global_var
    */

    pthread_mutex_unlock(&lock);

    ...
}

int main(void) {
    pthread_mutex_init(&lock, NULL);
    // ...
    pthread_mutex_destroy(&lock);
}

...
```

By leveraging `pthread_mutex_lock()` and `pthread_mutex_unlock`, we can make sure that only a single thread is updating the data at a time.