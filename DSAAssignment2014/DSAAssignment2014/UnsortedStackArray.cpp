#pragma once
//UnsortedStackArray.cpp
#include<string>
#include<iostream>
#include "UnsortedStackArray.h"
#include "Song.h"

using namespace std;

typedef Song ItemType;

// constructor
UnsortedStackArray::UnsortedStackArray(int s)
{
	size = s;
	top = -1;
}

//  push new item on top of the stack
void UnsortedStackArray::push(ItemType& item)
{

		++top;
		items[top] = item; // push the item
}

//  pop item from top of the stack
bool UnsortedStackArray::pop()
{
	bool success = !isEmpty();
	if (success)
	{
		--top;  //  pop top
	}
	return success;
}

//  get item from top of the stack
void UnsortedStackArray::getTop(ItemType& item)
{
		item = items[top];
}

//  check if the stack is empty
bool UnsortedStackArray::isEmpty()
{
	return top < 0;
}



