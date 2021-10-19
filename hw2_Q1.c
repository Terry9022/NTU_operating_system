#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int INTERVAL;
int interval, i;
double rand_x, rand_y, origin_dist, pi;
int circle_points = 0, square_points = 0;
void *estimate(void *param);

int main(int argc, char *argv[])
{

    // Initializing rand()
    srand(time(NULL));

    printf("請輸入一個數字INTERVAL：");
    scanf("%d", &INTERVAL);

    pthread_t tid;       /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */

    /* get the default attributes */
    pthread_attr_init(&attr);

    /* create the thread */
    pthread_create(&tid, &attr, estimate, NULL);

    /* now wait for the thread to exit */
    pthread_join(tid, NULL);
    // estimated pi after this iteration

    double points = 4.0 * circle_points;
    double pi = points / square_points;

    // Final Estimated Value
    printf("Final Estimation of Pi = %f\n", pi);

    return 0;
}

void *estimate(void *param)
{
    for (i = 0; i < (INTERVAL * INTERVAL); i++)
    {

        // Randomly generated x and y values
        rand_x = (double)(rand() % (INTERVAL + 1)) / INTERVAL;
        rand_y = (double)(rand() % (INTERVAL + 1)) / INTERVAL;

        // Distance between (x, y) from the origin
        origin_dist = rand_x * rand_x + rand_y * rand_y;

        // Checking if (x, y) lies inside the define
        // circle with R=1
        if (origin_dist <= 1)
            circle_points++;

        // Total number of points generated
        square_points++;
    }

    pthread_exit(0);
}
