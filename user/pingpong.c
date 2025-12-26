//user/pingpong.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char**argv){
    int pp2c[2],pc2p[2];
    pipe(pp2c);
    pipe(pc2p);
    
    if(fork()!=0){
        //parent sends child a char
        write(pp2c[1],".",1);
        close(pp2c[1]);

        //parent reads a char from child
        char buf;
        read(pc2p[0],&buf,1);
        printf("%d:recieved pong\n",getpid());
        wait(0);
    }else{
        //child reads a char from parent
        char buf;
        read(pp2c[0],&buf,1);
        printf("%d:received ping\n",getpid());

        //child sends parent a char
        write(pc2p[1],&buf,1);
        close(pc2p[1]);
    }
    close(pc2p[0]);
    close(pp2c[1]);
    exit(0);
}