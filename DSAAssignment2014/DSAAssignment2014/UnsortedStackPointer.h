#pragma once
//UnsortedStackPointer.h

#include <string>
#include <iostream>
#include "Song.h"

using namespace std;

typedef Song ItemType;

class UnsortedStackPointer
{
private:
	struct Node
	{
		ItemType item;	//item
		Node *next;		//pointer pointing to the next item

	};

	Node *topNode;	//point to the first item

public:
	//constructor
	UnsortedStackPointer();
	~UnsortedStackPointer();

	// push item on top of the stack
	bool push(ItemType& newItem);

	// pop item from top of stack
	bool pop();

	// retrieve and pop item from top of stack
	bool pop(ItemType& item);

	// retrieve item from top of stack
	void getTop(ItemType& item);

	// check if the stack is empty
	bool isEmpty();

	// display items in stack in order of insertion
	void displayInOrderOfInsertion();

	// does sequential seach for items in the list
	ItemType search(string target);

};