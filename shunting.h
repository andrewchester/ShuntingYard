#ifndef SHUNTING_H
#define SHUNTING_H

#include "list.h"

class Shunting {
	private:
		struct Node{
			int data;
			char op;
			Node* child;
			Node* parent;
		};
		Node* top;

		bool is_operator(char*);
		int precedence(char*);
	public:
		Shunting();

		LinkedList* to_postfix(LinkedList*);
		LinkedList* to_expression_tree(LinkedList*);
};

#endif