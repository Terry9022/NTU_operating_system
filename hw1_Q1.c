#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>

int main() {
	pid_t pid;
	pid = fork(); /* fork another process */ 
	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed\n"); 
	return 1; // exit(1);
	}
	else if (pid == 0) { /* child process */
		int i, n, t1 = 0, t2 = 1, nextTerm;
    		
    		scanf("%d", &n);
   	if (n < 0) { /* error occurred */
		fprintf(stderr, "please enter non-negative number\n"); 
	return 1; // exit(1);
	}

    		for (i = 0; i < n; i++) {
        	nextTerm = t1 + t2;
        	t1 = t2;
        	t2 = nextTerm;
        	printf("%d, ", t1);
    		}

    	}
    	else { /* parent process */
		/* parent will wait for the child to complete */
  		wait(NULL);
  		printf ("Child Complete\n");
	}
  
    return 0 ; // exit(0);
}
