#ifndef SHUNTING_H
#define SHUNTING_H

#include "list.h"

class Shunting {
	private:
		struct Node{
			char* data;
			char op;
			Node* left;
			Node* right;
		};
		Node* top;

		bool is_operator(char*);
		int precedence(char*);

		LinkedList* to_postfix(LinkedList*);
		Shunting::Node* to_expression_tree(LinkedList*);
		void infix(Shunting::Node*);
		void postfix(Shunting::Node*);
		void prefix(Shunting::Node*);
	public:
		Shunting();
		void output_handler(LinkedList*);
};

#endif