#include <vector>
#include <string.h>
#include "shunting.h"

Shunting::Shunting(){

}

bool Shunting::is_operator(char* c){ //Returns a boolean depending on if the token is an operator or not
    char derefc = *c;
    if(derefc == '+' || derefc == '-' || derefc == '/' || derefc == '*' || derefc == '^')
        return true;
    return false;
}
int Shunting::precedence(char* o){ //Returns a value for the precedence of an operator. So * is before + and ^ is before *
    char deref_o = *o;
    if(deref_o == '+' || deref_o == '-') return 0;
    else if(deref_o == '*' || deref_o == '/') return 1;
    else if(deref_o == '^') return 2;
    return -1;
}
LinkedList* Shunting::to_postfix(LinkedList* input_stack){
    LinkedList* output_stack = new LinkedList(); //Output stack to hold the final output
    LinkedList operator_stack = LinkedList(); //Operator stack that holds all the operators

    char* token; //Token of current interation
    while(input_stack->size() != 0){
        token = input_stack->at(0); //Get the first token on the input stack
        if(std::isdigit(*token)){ //Adds the token if its a digit
            output_stack->append(token);
        }
        if(is_operator(token)){ //If it's an operator
            if(operator_stack.size() > 0 && *token != '(' && *token != ')'){ //And not parenthesis and also there are operators on the stack
                int tokenp = precedence(token), headp = precedence(operator_stack.at(operator_stack.size() - 1)); //Calculates precedence for operators
                while(operator_stack.size() > 0 && headp > tokenp){ //While there are operators and the precedence is higher for the top of the stack than the current token
                    tokenp = precedence(token); //Recalculate precedences for the while loop condition
                    headp = precedence(operator_stack.at(operator_stack.size() - 1));
                    
                    output_stack->append(operator_stack.at(operator_stack.size() - 1)); //Pop the top of the stack from the operator stack to the output stack
                    operator_stack.pop();
                }
            }
            operator_stack.append(token); //Adds the token at the end
        }
        if(*token == '('){ //Adds it if its a (
            operator_stack.append(token);
        }
        if(*token == ')'){ //If it's a )
            while(*operator_stack.at(operator_stack.size() - 1) != '('){ //Loops back through the operator stack until it finds a corresponding (
                output_stack->append(operator_stack.at(operator_stack.size() - 1)); //Popping the operators from the operator stack to the output stack
                operator_stack.pop();
            }
            operator_stack.pop(); //Pops what should be the (
        }
        input_stack->remove(0); //Removes the first element, moving onto the next token
    }
    //When we're done reading from the input stack, add the rest of the operator stack to the output from the top down(-1 signifies the direction)
    output_stack->append(&operator_stack, -1);
    return output_stack;
}

Shunting::Node* Shunting::to_expression_tree(LinkedList* input){
    input = to_postfix(input);
    std::vector<Node*> stack = std::vector<Node*>();

    char* token;
    Node* top = new Node();

    while(input->size() != 0){
        token = input->at(0); //Get the token from the input  
        
        //Create the node and give it the data
        Node* newNode = new Node();
        newNode->data = token; 
        if(!is_operator(token)){
            stack.push_back(newNode); //Push the node onto the stack if it's a number
        }else{
            //Get the pointers to the previous two nodes in the list
            Node* left = stack.at(stack.size() - 2);
            Node* right = stack.at(stack.size() - 1);

            //Assign the node's pointer values to the ones from the list
            newNode->left = left;
            newNode->right = right;

            //Remove the last two elements in the list(what should be there is a node pointing to both of them)
            stack.pop_back();
            stack.pop_back();

            stack.push_back(newNode); //Adding the new tree node to the stack
        }

        input->remove(0); //Remove the input thats already been handled from the list
    }
    return stack.at(0); //We should finish the algorithm with 1 node point at the beginning which should be the top of the tree(or bottom????)
}
void Shunting::infix(Shunting::Node* head_node){
	if(is_operator(head_node->data)) //Starts by printing an open parenthesis if the token is an operator
		std::cout << "( ";
	if(head_node->left != 0) //Goes down the left side
		infix(head_node->left);
	std::cout << head_node->data << " "; //Prints out the token
	if(head_node->right != 0) //Goes down the right side
		infix(head_node->right);
	if(is_operator(head_node->data)) //At the end of going through left and right, it will output the closing parenthesis if the token was an operator
		std::cout << ") ";
}
void Shunting::postfix(Shunting::Node* head_node){
	//Goes into the two child nodes
	if(head_node->left != 0)
		postfix(head_node->left);
	if(head_node->right != 0)
		postfix(head_node->right);
	std::cout << head_node->data << " "; //Then prints out the data, hence the name, postfix
}
void Shunting::prefix(Shunting::Node* head_node){ //Outputs to prefix
	std::cout << head_node->data << " "; //Outputs the operator/number first, 
	//Then goes into the two child nodes afterwards(hence the name, prefix)
	if(head_node->left != 0)
		prefix(head_node->left);
	if(head_node->right != 0)
		prefix(head_node->right);
}

void Shunting::output_handler(LinkedList* input){
	Shunting::Node* head_node = to_expression_tree(input); //Get an expression tree from user given input
	int type; //Variable for how to output the tree

	std::cout << "How should the expression tree be outputed(1 = infix, 2 = postfix, 3 = prefix): ";
	std::cin >> type;
	std::cin.clear();
	std::cin.ignore(100, '\n');

	if(type == 1){ //if 1, then infix
		infix(head_node);
	}else if(type == 2){ //if 2, then postfix
		postfix(head_node);
	}else if(type == 3){ //if 3, then prefix
		prefix(head_node);
	}
    std::cout << std::endl;
}