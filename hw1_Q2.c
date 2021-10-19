#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <sys/mman.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

# define MAX_SEQUENCE 10
# define STORAGE_ID "/SHM_HW1"

typedef struct {
	long fib_sequence[MAX_SEQUENCE];
	int sequence_size;
	} shared_data;

int main()
{
int a,b,m,n,i,j;
a=0; b=1;
printf("Enter the number of a Fibonacci Sequence:\n");
scanf("%d", &m);

if (m < 0){
        printf("Please enter a non-negative integer\n");
        return 1;
        }
else if (m> MAX_SEQUENCE){
        printf("Please enter an integer less than 10\n");
        return 1;
        }


    const char *name = "OS";
    /* the identifier for the shared memory segment */
    int segment_id;

    /* the size (in bytes) of the shared memory segment */
    size_t segment_size = sizeof(shared_data);


    /* allocate  a shared memory segment */
    segment_id =  shm_open(STORAGE_ID, O_CREAT | O_RDWR, 0666);
    ftruncate(segment_id , segment_size);
    
    /* attach the shared memory segment */
    shared_data *shared_memory = mmap(0, segment_size, PROT_WRITE, MAP_SHARED, segment_id, 0);
    
    printf("\nshared memory segment %d attached at address %p\n", segment_id, (void*)shared_memory);
    
    

shared_memory->sequence_size = m;


    pid_t pid;
    pid = fork();
    if (pid == 0){
        printf("Child is producing the Fibonacci Sequence...\n");
        
        for (i = 0; i < shared_memory->sequence_size; i++){
            n = a+b;
            a = b;
            b = n;
            shared_memory->fib_sequence[i] = a;
        }
        printf("Child ends\n"); 
    }
    else{
        printf("Parent is waiting for child to complete...\n");
        wait(NULL);
        printf("Parent process output Fibonacci Sequence:\n");
        for(i = 0; i < shared_memory->sequence_size; i++) {
            printf("%ld ", shared_memory->fib_sequence[i]);
        }
        printf("\n");
    }

  
    /* now remove the shared memory segment */
    shm_unlink(STORAGE_ID); 

    return 0;
}








