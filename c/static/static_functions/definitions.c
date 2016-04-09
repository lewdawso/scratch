/*
A static function cannot be used outside of its translation unit.
The static qualifier stops the function being made available to the linker.

*/

#include <stdio.h>

static void print_static() {
	printf("static print\n");
}

void print() {
	printf("print\n");
}
