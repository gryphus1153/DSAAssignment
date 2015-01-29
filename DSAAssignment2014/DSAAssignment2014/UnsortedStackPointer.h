/*
UnsortedStackPointer.h: Unsorted Pointer Based Stack Data Structure

Amirulamin Bin Mohd Osman (S10139137F)
Emmanuelle Myls Joie Gregorio (S10145392)

*/
#pragma once


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
	int count;
	int size;

public:
	//constructor
	UnsortedStackPointer();
	UnsortedStackPointer(int s);
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

	//	 gets count
	int getCount();

	// display items in stack in order of insertion
	void print();

	// remove the item from index
	void remove(int index);

	//gets the item index
	ItemType get(int index);

	// does sequential seach for items in the list
	int sequentialSearch(string target);

};