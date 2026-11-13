#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//#include <semaphore.h>

#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"


Zem_t forks[25]; // picked 25 because there can be between 3 - 20 and 25 give a bit of wiggle room

void getForks (int p)
{
    Zem_wait(&forks[p]); // the left fork wait til left fork is available
    Zem_wait(&forks[((p+1)%5)]); // the right fork wait til right fork is avaliable
}

void putForks(int p)
{
    Zem_post(&forks[p]); // left fork put down
    Zem_post(&forks[((p+1)%5)]); // right fork put down
}


void *algo1(void *arg)
{
    long long int value = (long long int) arg;
    int philosophers = (int) value;
    while(true)
    {
        printf("I am thinking... \n");
        getForks(philosophers);
        printf("If you see this, you did it wrong. \n");
        putForks(philosophers);
    }
}



int main (int argc, char *argv[])
{
    int n;
    if (argc >1)
         n = (atoi(argv[1]));

    for (int i = 0; i < n; i++)
    {
        Zem_init(&forks[i], 1); // initializes the first n values of the array
    }
   
    for(int i = 0; i < n; ++i) // <20 because max philosphers we can have is 20
    {
        pthread_t c;
        long long int me = i;
        Pthread_create(&c, NULL, algo1, (void*) me);
    }

    while (true){
    
    }
    return 0;
}


/* void algo1(int number) // where N is the number of philosophers provided by the command line
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
    while (j < number) // this
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
 */   
