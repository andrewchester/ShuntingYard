#include <iostream>
#include <string.h>
#include "shunting.h"
#include "list.h"

//Tokenize the input into a linked list
void gen_inputstack(LinkedList* input, char* in){
	char * pch;
	pch = strtok (in," ");
	while (pch != NULL)
	{
		input->append(pch);
		pch = strtok (NULL, " ");
	}
}

void get_input(char* in){ //Get input from the user
	std::cout << "Put spaces between each term please" << std::endl;
	std::cout << "Enter operation: ";
	std::cin.get(in, 100);
	std::cin.clear();
	std::cin.ignore(100, '\n');
}

int main(){
	//Create the shunting and input stack objects
	Shunting s = Shunting();
	LinkedList* input_stack = new LinkedList();

	char in[100];
	get_input(in); //Get the input and input stack
	gen_inputstack(input_stack, in);

	s.output_handler(input_stack); //Calls the output handler, which also converts the input stack to postfix, then to what the user specifies

	return 0;
}