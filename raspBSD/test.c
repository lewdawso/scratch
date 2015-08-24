#include "map_gpio.h"

struct peripheral p;

int main() {
	//set pin to output
	p.p_addr = GPIO_BASE_ADDR;
	map_gpio(&p);
	set_as_input(&p, 4);
	//set_as_output(&p, 4);
	set_output(&p, 4, 0);
	clear_output(&p, 4);
	read_pin(&p, 4);	
	return 0;
}
