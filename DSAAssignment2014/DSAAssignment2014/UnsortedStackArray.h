#pragma once
//UnsortedStackArray.h
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

	// does sequential search
	int sequentialSearch(string);

};