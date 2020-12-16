#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

int main(){

	pid_t pID;
	char nazwa_pliku[64];
	char obr_map[] = "tlo1.png";
	int fd,fd2;
	struct stat stat_pliku;
	void *addr = NULL;
	
	
	if((pID=fork()) < 0){
		printf("Nie utworzono procesu potomnego\n");
		return 1;
	}
	if(pID == 0){
		execlp("display","display","-update","1",obr_map,NULL);
	}
	if(pID > 0){
		while(1){
			printf("Podaj nazwę pliku:");
			scanf("%s",nazwa_pliku);
			fd = open(nazwa_pliku, O_RDONLY);
			if(fd < 0){
				printf("Nie udało sie otworzyc pliku.");
			}
			printf("\n");
			stat(nazwa_pliku, &stat_pliku);
			fd2 = open(obr_map, O_RDWR);
			truncate(obr_map,stat_pliku.st_size);
			addr = mmap(NULL, stat_pliku.st_size,PROT_WRITE | PROT_READ, MAP_SHARED, fd2, 0);
			read(fd, addr, stat_pliku.st_size);
			msync(addr, stat_pliku.st_size,MS_SYNC);
			close(fd);
			close(fd2);
		}
	}
	munmap(addr, stat_pliku.st_size);
	return 0;
}

