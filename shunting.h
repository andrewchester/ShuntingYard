#ifndef SHUNTING_H
#define SHUNTING_H

class Shunting {
	private:
		struct Node{
			int data;
			char op;
			Node* child;
			Node* parent;
		};
		Node* top;
	public:
		
};

#endif