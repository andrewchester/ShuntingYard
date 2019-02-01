#include <iostream>

void get_input(char* in){
	std::cout << "Enter operation: ";
	std::cin.get(in, 100);
	std::cin.clear();
	std::cin.ignore(100, '\n');
}

int main(){
	char* in;
	get_input(in);
	
	return 0;
}