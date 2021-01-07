#include <pthread.h>
#include <stdio.h>

#define N 5 //ilosc watkow

void *thread_func() {

    printf("Hello world from thread %ld\n", pthread_self());
    
    pthread_exit(NULL);
}

int main(int arc, char *argv[]) {

    pthread_t id[N];
    int error_code;

    for(int i = 0; i < N; ++i) {

        error_code = pthread_create(&id[i], NULL, thread_func, NULL);

        if(error_code) {
            fprintf(stderr, "Wątek nie został utowrzony prawidłowo.");
        }
    }

    for(int i = 0; i < N; ++i) {

        pthread_join(id[i], NULL);
    }

    pthread_exit(NULL);
} 
