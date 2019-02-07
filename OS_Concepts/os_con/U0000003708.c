//Andre Ripley
//U0000003708
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argv, char** argc) {
    // Pipelining
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);
    int luis;
    
    int numElements = 6; 
    luis = fork();  

    if (luis == 0) { 
        
        close(p1[1]); 
        close(p2[0]); 
        int vals[numElements];
        read(p1[0], &vals, sizeof(vals));

        int sum = 0;
        int p_sum1 = 0;
        int p_sum2 = 0;
        int i;

        for (i=3; i<6; i++){
            p_sum2 += vals[i];
        }
        for (i=0;i<numElements;i++){   
            sum += vals[i];  
        }
        for (i=0; i<3; i++){
            p_sum1 += vals[i]; 
        }
        printf("I am child1 with pid %d: adding the array 2,3,5 and sending partial sum %d ", getpid(),p_sum1); 
        printf("\n"); 

        printf("I am child2 with pid %d: adding the array 7,1,3 and sending partial sum %d ", getpid(),p_sum2);
        printf("\n");

        write(p2[1], &sum, sizeof(sum)); 
        exit(0);     
    } 
    else {
        
        close(p1[0]);  
        close(p2[1]);  
        int valsToSend[6] = {2,3,5,7,1,3};
        write(p1[1], &valsToSend, sizeof(valsToSend));
        printf("I am parent with pid: %d sending the array: 2,3,5,7,1,3  \n", getpid());
        
        int recval;
        read(p2[0], &recval, sizeof(recval));
        printf("I am the parent of pid: %i, and pid: %i. I have pid: %d and got partial results 10, 11, final result is %d",luis,luis,getpid(),recval);
        printf("\n");
        exit(0);
    }
    return 0;
}
