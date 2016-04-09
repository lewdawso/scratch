//prototypes
void static_print();
void print();

int main() {
	print();
	//this will give an undefined symbol error when compiling.
	//static_print();
	return 0;
}
