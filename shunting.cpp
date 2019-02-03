#include "shunting.h"

Shunting::Shunting(){

}

bool Shunting::is_operator(char* c){
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

    LinkedList* output_stack = new LinkedList();
    LinkedList operator_stack = LinkedList();

    char* token;

    while(input_stack->size() != 0){
        token = input_stack->at(0); //Get the first token on the input stack
        if(std::isdigit(*token)){ //Move the token directly to the output stack if its a number
            output_stack->append(token);
        }
        if(is_operator(token)){
            /*
                While loop:
                    while the operator stack has operators and the precedence of the top of the stack is greater than the token or the precedences are equal and it isn't a left to right reading operator 
            */
            while(operator_stack.size() > 0 && (precedence(operator_stack.at(operator_stack.size () -1)) > precedence(token) ||
                   precedence(operator_stack.at(operator_stack.size () -1)) == precedence(token) && *operator_stack.at(operator_stack.size () -1) != '^')){
                output_stack->append(operator_stack.at(operator_stack.size () -1));
                operator_stack.pop();
            }
            operator_stack.append(token); //Add the token to the operator stack, runs if there's an empty operator stack or the operator we're adding has a higher precedence
        }
        if (*token == '('){
            operator_stack.append(token); //Add the ( to the operator stack
        }
        if(*token == ')'){
            while(*operator_stack.at(operator_stack.size () - 1) != '('){ //Go back popping operators to the output until we find the (
                output_stack->append(operator_stack.at(operator_stack.size () -1));
                operator_stack.pop();
            }
            operator_stack.pop(); //Remove the (
        }
        input_stack->remove(0);
    }
    //When we're done reading from the input stack, add the rest of the operator stack to the output from the top down(-1 signifies the direction)
    output_stack->append(&operator_stack, -1);
    return output_stack;
}

LinkedList* Shunting::to_expression_tree(LinkedList* input){
    input = to_postfix(input);
    LinkedList stack = LinkedList();

    while(input->size() != 0){
        stack.append(input->at(0));
        


        input->remove(0);
    }
}