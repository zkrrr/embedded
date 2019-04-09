//
// Created by zk on 19-4-9.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t child1, child2, child;

    child1 = fork();

    if(child1 == -1)
    {
        printf("Child1 fork error\n");
        exit(1);
    } else if(child1 == 0)
    {
        printf("In child: execute 'ls -l'\n");
        if(execlp("ls", "ls", "-l", NULL) < 0)
        {
            printf("Child execlp error\n");
        }
    } else
    {
        child2 = fork();
        if(child2 == -1)
        {
            printf("Child2 fork error\n");
            exit(1);
        } else if(child2 == 0)
        {
            printf("In child: sleep for 5 seconds and then exit\n");
            sleep(5);
            exit(0);
        }

        printf("In father process:\n");

        child = waitpid(child1, NULL, 0);
        if(child == child1)
        {
            printf("Get child1 exit code\n");
        } else
        {
            printf("Error occured!\n");
        }
        do
        {
            child = waitpid(child2, NULL, WNOHANG);
            if(child == 0)
            {
                printf("The child2 process has not exited!\n");
                sleep(1);
            }
        }while (child == 0);
        if(child == child2)
        {
            printf("Get child2 exit code\n");
        } else
        {
            printf("Error occured!\n");
        }
    }
    exit(0);
}