
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


void catch1(int signum) {

    printf("Sygnal wylapany %d, zakonczenie programu\n", signum);
    exit(0);
}

void catch2(int signum) {

    printf("Sygnal wylapany %d\n", signum);
}



void catch3(int signum) {

    ;
}

int main() {

    int i = 0;
    //struct timespec tim, tim2;

    //tim.tv_sec  = 0;
    //tim.tv_nsec = 100000L;
    signal(SIGUSR1, catch2);
    signal(SIGUSR2, catch2);
    signal(SIGTERM, catch2);
    signal(SIGALRM, catch2);

    while (1) {

        ++i;
        printf("%d %d\n", getpid(), i);
        sleep(1);
    }
}
