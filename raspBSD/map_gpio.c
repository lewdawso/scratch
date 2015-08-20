#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE 4096
#define PERI_BASE_ADDR 0x20000000
#define GPIO_BASE_ADDR (PERI_BASE_ADDR + 0x20000)
#define GPIO_SET_OUT_0 *(GPIO_BASE_ADDR + 7)
#define GPIO_SET_OUT_1 *(GPIO_BASE_ADDR + 8)

struct peripheral {
	int map_fd; //file descriptor when opening /dev/mem
	void *map; //pointer to map returned by mmap
	unsigned long p_addr; //physical address we want to map = offset in the /dev/mem mmap
}

struct peripheral *p

void map_gpio(unsigned long gpio_addr) {

	//pointer to peripheral structure
	p->p_addr = gpio_addr;

	//open /dev/mem
	if (p->map_fd = open("/dev/mem", O_RDWR) < 0) {
		perror("open");
		exit(1);
	}

	//close file descriptor
	close(p->map_fd);
	//create a mapping to gpio's physical address p_addr
	if (p->map = mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,  p->map_fd, p->p_addr)< 0) {
		perror("mmap");
		exit(1);
	}
}

void unmap_gpio(void) {
	munmap(p->map);
}

//set a GPIO pin as input
void set_input(int pin) {
	unsigned int addr, bit;
	addr = p->p_map + (pin/10); //each function select register allows you to set 10 pins
	//input requires appropriate bits to be set as 000, so bitshift 111 to correct bit position and then take inverse 
	bit = ~(7 << (pin % 10)*3);
	*addr &= bit; //keep old registers values the same
}

void set_output(int pin) {
	unsigned int addr, bit;
	addr = p->p_map + (pin/10);
	//output required appropriate bits to be set as 001, so bit shift decimal 1 to correct bit position
	bit = 1 << (pin % 10)*3;
	*addr |= bit; 
}
