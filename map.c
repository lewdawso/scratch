#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

int fd;
struct stat st;
void *map;

int main () {

	fd = open("test.txt", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);	
	}

	if (fstat(fd, &st) < 0) {
		close(fd);
		perror("fstat");
		exit(1);
	}

	map = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	//now write to the file using the mapping
	strcpy(map, "This string should overwrite the content of test.txt");	

}


