/*
UnsortedStackArray.h: Unsorted Array Based Stack Data Structure

Amirulamin Bin Mohd Osman (S10139137F)
Emmanuelle Myls Joie Gregorio (S10145392)

*/

#pragma once

#include<string>
#include<iostream>
#include "Song.h"

using namespace std;

typedef Song ItemType;

class UnsortedStackArray
{
private:
	int top;	//index that keeps track of the top of the stack
	int count;
	int size;
	ItemType * items;

public:
	//default constructor
	UnsortedStackArray();

	//	constructor
	UnsortedStackArray(int);

	// destructor
	~UnsortedStackArray();

	// add a new item to the top of the stack (push)
	void push(ItemType& item);

	// removes item from top of the stack(pop)
	bool pop();

	//	gets the item from the top of the stack
	void getTop(ItemType& item);

	//	check if the stack is empty
	bool isEmpty();

	// gets size of array
	int getCount();

	// print out in order of insertion
	void print();

	// remove item from index
	void remove(int index);

	// get item of that index
	ItemType get(int index);

	// does sequential search
	int sequentialSearch(string);
};