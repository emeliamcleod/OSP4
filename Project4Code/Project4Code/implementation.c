#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//#include <semaphore.h>

#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

Zem_t leftFork;
Zem_t rightFork;
Zem_t mutex;

void algo1(int number) // where N is the number of philosophers provided by the command line
{
    int philosophers[number]; // creates philosophers
    for (i = 0; i < number; i++)
    {
        philosophers[i] = i; // numbers philosophers
        
    }

    int forks[number]; // creates forks
    for (i = 0; i < number; i++)
    {
        forks[i] = i; // numbers forks
    }

    int j = 0;
    while (j < number)
    {
        if (philosphers[j] == forks[j])
        {
            Zem_post(&leftFork); // if the p's number = f's number grab left fork
            Zem_wait(rightFork); // and wait on right fork
        }

        if (forks[j] == ((philosophers[j]+1) %number))
        {
            Zem_post(rightFork); // if f's number == (p+1)%N grab right fork
            Zem_wait(leftFork);  // wait on left fork
        }

        j++;
    }
}
    
