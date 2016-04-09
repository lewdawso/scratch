/*
We're dealing with both scope and lifetime here. 
Since a is local variable, it's visible only inside func().
Static extends the lifetime of a to the lifetime of the program.
It's value is retained between invocations, but it can't be accessed outside of func.
The compiler ensures the static variable isn't initialised each time 
the function is entered. 
*/

#include <stdio.h> 

void func() {
	static int a = 1;
	a++;
 	printf("a is: %d\n", a);
} 

int main() {
	func();
	func();
	func();
	return 0;
}
