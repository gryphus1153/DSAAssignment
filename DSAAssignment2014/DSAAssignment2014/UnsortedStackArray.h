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
	int size;
	ItemType * items;
public:
	//	constructor
	UnsortedStackArray(int);

	// add a new item to the top of the stack (push)
	void push(ItemType& item);

	// removes item from top of the stack(pop)
	bool pop();

	//	gets the item from the top of the stack
	void getTop(ItemType& item);

	//	check if the stack is empty
	bool isEmpty();

};