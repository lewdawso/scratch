#include "map_gpio.h"

int main() {
	struct peripheral p;
	//set pin to output
	set_as_input(&p, 1);
	set_as_output(&p, 1);
	return 0;
}
