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
	public:
		Shunting();
		void test_function(LinkedList*);
};

#endif