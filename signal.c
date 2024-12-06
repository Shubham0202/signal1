#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


void handle_signal(int sig) {
    switch (sig) {
        case SIGHUP:
            printf("Child process received SIGHUP\n");
            break;
        case SIGINT:
            printf("Child process received SIGINT\n");
            break;
        case SIGQUIT:
            printf("Child process received SIGQUIT\n");
            printf("Parent Process has killed child process!!!\n");
            exit(0);
            break;
        default:
            printf("Child process received unknown signal %d\n", sig);
            break;
    }
}

int main() {
    pid_t pid;
    int status,i;
    struct sigaction sa;


    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;



    if ((pid = fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {

        while (1) {
            pause(); 
        }
    } else {
        
        sleep(3);

        for (i = 0; i < 10; ++i) {
            if (i < 10) {
                
                if (i % 2 == 0) {
                    kill(pid, SIGHUP);
                } else { jh=
                    kill(pid, SIGINT);
                }
                sleep(3);
            }
        }


        kill(pid, SIGQUIT);
        waitpid(pid, &status, 0);

        printf("Parent process exiting\n");
        exit(EXIT_SUCCESS);
    }
}
