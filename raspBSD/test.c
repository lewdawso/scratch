#include "map_gpio.h"

struct peripheral p;

int main() {
	//set pin to outputi
	p.p_addr = GPIO_BASE_ADDR;
	map_gpio(&p);
	set_as_input(&p, 1);
	//set_as_output(&p, 1);
	//clear_output(1);
	return 0;
}
