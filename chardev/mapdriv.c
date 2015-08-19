#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {

	int fd;
	void *ptr;
	struct stat st;

	fd = open("/dev/echo", O_RDWR);
	if (fd < 0) {
		perror("open");
		exit(1);
	}

	if (fstat(fd, &st) < 0) {
		printf("Hit an fstat issue\n");
		perror("fstat");
		close(fd);
		exit(1);
	}
	
	printf("file descriptor is %d\n", fd);	

	ptr = mmap(0, 256, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

  	close(fd);
	if (ptr == MAP_FAILED) {
		perror("mmap failed");
		close(fd);
		exit(1);
	}

	printf("pointer returned is %p\n", ptr);
	//printf("hello %c", *(char *)ptr);
	sleep(2);
	strncpy(ptr, "t", 256);
	//munmap(ptr, 32);
	return (0);

}
