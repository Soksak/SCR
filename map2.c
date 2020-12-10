#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

int main()
{

    int fd = 0, fd_in;
    char name[50];
    struct stat stat_file;
    char *addr;

    while(1) {
        fd = open("tekst1.txt", O_RDWR);
        printf("Podaj nazwę pliku :\t");
        scanf("%s", name);
        fd_in = open(name, O_RDWR);

        while(fd_in < 0) {
            printf("Nie otwarto pliku\n");
            printf("Podaj nową nazwę pliku:\t");
            scanf("%s", name);
        }

        stat(name, &stat_file);
        ftruncate(name, stat_file.st_size);
        addr = mmap(NULL, stat_file.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        read(fd_in, addr, stat_file.st_size);
        close(fd);
        close(fd_in);
    }

    munmap(addr, stat_file.st_size);
    return 0;
}
