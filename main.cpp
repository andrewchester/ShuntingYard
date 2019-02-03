#include <iostream>
#include <string.h>
#include "shunting.h"
#include "list.h"

void gen_inputstack(LinkedList* input, char* in){
	char * pch;
	pch = strtok (in," ");
	while (pch != NULL)
	{
		input->append(pch);
		pch = strtok (NULL, " ");
	}
}

void get_input(char* in){
	std::cout << "Enter operation: ";
	std::cin.get(in, 100);
	std::cin.clear();
	std::cin.ignore(100, '\n');
}

int main(){
	Shunting s = Shunting();
	LinkedList* input_stack = new LinkedList();

	char in[100];
	get_input(in);
	gen_inputstack(input_stack, in);

	s.to_expression_tree(input_stack);

	return 0;
}