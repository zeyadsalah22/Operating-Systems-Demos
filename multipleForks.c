#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]){
    int id1 = fork();
    int id2 = fork();
    if(id1==0){
        if(id2==0)
            printf("Child 1.1\n");
        else
            printf("Child 0.1\n");
    }
    else{
        if(id2==0)
            printf("Child 0.2\n");
        else
            printf("Parent\n");
    }
    while(wait(NULL)!=-1 || errno!=ECHILD){
        printf("waited for a child to finish\n");
    }
}