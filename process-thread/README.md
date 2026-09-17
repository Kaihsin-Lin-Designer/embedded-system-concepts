# Process & Thread

Process and Thread are one of the fundamental concepts in Linux. 

## Process

In Linux, a process is a resource-isolated unit. Every process has its own virtual memory space, such as stack, heap, .bss, etc. This isolation is enforced by the MMU (Memory Management Unit) — each process has its own page table, so one process cannot directly read or write another process's memory. This design ensures that a process cannot overwrite another process's data.

## Thread

A process can have multiple threads. Threads in the same process share almost all resources except for the stack, register state, and program counter. This shared memory model enables threads to communicate with each other easily and efficiently.

## Concepts

### Race Condition

Since threads within the same process share resources, they might read and write the same data at the same time; therefore, they might overwrite each other's updates. This is called **race condition**.


**Example:**
```
int global_var = 100;

(At the same time)
[Alpha Thread]  global_var += 200;
[Beta Thread]   global_var += 300;
```

In this example, we expect `global_var` to be `600`. However, due to the race condition, we cannot assure whether the operations in these threads are overwritten by each other or not. In this case, `global_var` might be `600`, `300`, or `400`.

This is something that we want to avoid in our programs, because well-written programs are predictable.


### Mutex Lock

If you've already learned SQL, you may find that the same kind of race condition also happens in transactions. If multiple requests perform CRUD operations on the same data at the same time, some of those updates are likely to be lost. Programmers came up with transaction locks in SQL to solve this, and in C we have a similar mechanism called **Mutex Lock**, which blocks other threads from entering the critical section while one thread is holding the lock.

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

By leveraging `pthread_mutex_lock()` and `pthread_mutex_unlock()`, we can make sure that only a single thread is updating the data at a time.