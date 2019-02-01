#ifndef LIST_H
#define LIST_H

#include <iostream>

class LinkedList {
 
 struct Node{
   int data;
   Node* next;
   Node* previous;
 };
 Node* first; //First node in list
 Node* last; //Last node in list
 int length; //Length of list
 
 Node* nodeAt(int);
 
 public:
  LinkedList(); //Constructor, defaults first, last, and length to 0

  friend std::ostream& operator<<(std::ostream& os, const LinkedList& list); //Printing out the list using << 

  int operator[] (int); //Overloads the [] operator
  int at(int index); //Accesses a node in the list

  void append(int); //Appends a value to the end, just uses insert() at the end
  void insert(int index, int data); //Inserts a value to a spot in the list
  void remove(int index);  //Removes a node at an index
  void deleteData(int); //Deletes all students matching the pointer
  void clear(); //Delete's all nodes from the array
  int size(); //Returns the size of the list 

  Node* end(); //Returns the last node in the list
  Node* begin(); //Returns the first node in the list
};

#endif