#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 不輸入任何東西，程式自己random一個長度為10的unsorted array1

void *sorting(void *param);
void *merge(void *param2);
int array1[10];
int array2[10];

int main(int argc, char *argv[])
{
    /* 設定亂數種子 */
    srand(time(NULL));

    /* 指定亂數範圍 */
    int min = 1;
    int max = 100;

    for (int i = 0; i < 10; i++)
    {
        /* 產生 [min , max] 的10個整數亂數 */
        int x = rand() % (max - min + 1) + min;
        array1[i] = x;
    }
    printf("尚未排序以前 \n");
    for (int i = 0; i < 10; i++)
    {
        printf(" %d ", array1[i]);
    }
    printf("\n");
    pthread_t tid[3];    /* the thread identifier */
    pthread_attr_t attr; /* set of attributes for the thread */

    /* get the default attributes */
    pthread_attr_init(&attr);

    /* create the 2 sorting thread */
    int index[2] = {0, 5}; //要傳入的starting index

    pthread_create(&tid[0], &attr, sorting, (void *)(&index[0]));
    pthread_join(tid[0], NULL);

    pthread_create(&tid[1], &attr, sorting, (void *)(&index[1]));
    pthread_join(tid[1], NULL);

    /* 印出排序後的結果 */
    printf("sorting thread各自排序完之後 \n");
    for (int i = 0; i < 10; i++)
    {
        printf(" %d ", array1[i]);
    }
    printf("\n");
    /* create the merge thread */
    pthread_create(&tid[2], &attr, merge, NULL);
    pthread_join(tid[2], NULL);

    /* 印出排序後的結果 */
    printf("merge 排序完之後 \n");
    for (int i = 0; i < 10; i++)
    {
        printf(" %d ", array2[i]);
    }
    printf("\n");
    return 0;
}

void *sorting(void *param)
{
    int start_index = *(int *)param; // 將參數傳入
    int *arr = &array1[start_index]; // 選取array的pointer
    int len = 5;                     // 要排序的長度
    int i, j, temp;
    for (i = 0; i < len - 1; ++i)         //循環N-1次
        for (j = 0; j < len - 1 - i; ++j) //每次循環要比較的次數
            if (arr[j] > arr[j + 1])      //比大小後交換
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
    printf("this is thread %d \n", (start_index / 5) + 1);
    pthread_exit(0);
}

void *merge(void *param2)
{
    int i = 0;
    int j = 0;
    int n1 = 5;
    int n2 = 5;
    int *left = &array1[0];  // 選取array的left part
    int *right = &array1[5]; // 選取array的right part
    int k = 0;               // array2目前的index

    int *a = &array2[0]; // 選取array2

    // merge left and right in ascending order
    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }

    // insert remaining values from left
    while (i < n1)
    {
        a[k++] = left[i++];
    }

    // insert remaining values from right
    while (j < n2)
    {
        a[k++] = right[j++];
    }

    printf("this is merge thread \n");
    pthread_exit(0);
}
