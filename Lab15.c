#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define Buf_rozmiar 256


int main(int argc, char *argv[]) {

    pid_t pid;
    int potok_fd[2], in_fd, n;
    char buf [Buf_rozmiar];

    pipe(potok_fd);
    pid = fork();
    if(pid==0)
        {
        close(potok_fd[1]);
        while(read(potok_fd[0],&buf,4)>0)
            {
                write(STDOUT_FILENO,"#",4);
                write(STDOUT_FILENO,&buf,4);
                write(STDOUT_FILENO,"#",4);
            }
	close(potok_fd[0]);
        }

    else if(pid>0)
    {
        close(potok_fd[0]);
        in_fd=open(argv[1],O_RDONLY);
	n= read(in_fd, &buf,Buf_rozmiar);
        write(potok_fd[1],&buf,n);
    close (in_fd);
    }
}
