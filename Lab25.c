#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 256

int main(int argc, char* argv[]) {

    pid_t pid;
    int potok_fd[2], in_fd, n;
    char buf[BUF_SIZE];

    pipe(potok_fd);
    pid = fork();

    if(pid == 0) {
        close(potok_fd[1]);
        close(0);
        dup(potok_fd[0]);
        close(potok_fd[0]);
        execlp("display", "display", "-", NULL);
    }
    else {
        close(potok_fd[0]);
	if((in_fd = open(argv[1], O_RDONLY)) < 0) {

            fprintf(stderr, "Blad czytania pliku.\n");
            return 2;
        }

        while((n = read(in_fd, &buf, BUF_SIZE)) > 0) {

            if(write(potok_fd[1], &buf, n) < 0) {
                fprintf(stderr, "Blad wpisywania pliku do potoku.\n");
                return 3;
            }
        }
        close(in_fd);
    }
}
