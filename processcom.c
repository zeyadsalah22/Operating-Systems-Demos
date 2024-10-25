#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]){
    int fd[2];
    if(pipe(fd)==-1){
        printf("Pipe failed\n");
        exit(1);
    }
    int id = fork();
    if(id==-1){
        printf("Fork failed\n");
        exit(1);
    }
    if(id==0){
        close(fd[0]);
        char* msg = "Hello from child\n";
        if(write(fd[1], msg, strlen(msg)+1)==-1){
            printf("Write failed\n");
            exit(1);
        }
        close(fd[1]);
    }
    else{
        close(fd[1]);
        char msg[100];
        if(read(fd[0], msg, 100)==-1){
            printf("Read failed\n");
            exit(1);
        }
        printf("Message from child: %s", msg);
        close(fd[0]);
    }
}