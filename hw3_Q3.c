#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#define NUM_OF_THREAD 5
int INTERVAL = 1000;
double rand_x, rand_y, pi;
int circle_points = 0;
void *estimate(void *param);
pthread_mutex_t mutex; // mutex lock

int main(int argc, char *argv[])
{

    pthread_t thread[NUM_OF_THREAD]; // threads' identifier
    pthread_attr_t attr;             // set of attributes for the thread

    // Initializing rand()
    srand(time(NULL));

    // initilise the mutex lock
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_OF_THREAD; i++)
    { // generate 5 separate threads
        pthread_create(&thread[i], 0, &estimate, NULL);
    }

    for (int i = 0; i < NUM_OF_THREAD; i++)
    { // parent thread waits
        pthread_join(thread[i], NULL);
    }

    // estimated pi after this iteration
    double points = 4.0 * circle_points;
    double pi = points / (INTERVAL * NUM_OF_THREAD);

    // Final Estimated Value
    printf("Final Estimation of Pi = %f\n", pi);

    return 0;
}

void *estimate(void *param)
{
    for (int i = 0; i < INTERVAL; i++)
    {
        // Randomly generated x and y values
        rand_x = (double)(rand() % (INTERVAL + 1)) / INTERVAL;
        rand_y = (double)(rand() % (INTERVAL + 1)) / INTERVAL;
        // acquire the mutex lock
        pthread_mutex_lock(&mutex);

        // Checking if (x, y) lies inside the define
        // circle with R=1
        if (rand_x * rand_x + rand_y * rand_y <= 1)
            circle_points++;

        // release the mutex unlock
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}
