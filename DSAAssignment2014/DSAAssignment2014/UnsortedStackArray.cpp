#pragma once
//UnsortedStackArray.cpp
#include<string>
#include<iostream>
#include "UnsortedStackArray.h"
#include "Song.h"

using namespace std;

typedef Song ItemType;

// default constructed
UnsortedStackArray::UnsortedStackArray()
{
	count = 0;
}

// constructor
UnsortedStackArray::UnsortedStackArray(int s)
{
	count = 0;
	size = s;
	top = -1;
}

// destructor
UnsortedStackArray::~UnsortedStackArray()
{
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

// gets size of Array
int UnsortedStackArray::getCount()
{
	return count;
}

int UnsortedStackArray::sequentialSearch(string target)
{
	int pos = -1;
	for (int i = 0; i < getCount(); i++)
	{
		if (items[i].getTid().compare(target) == 0) // found
		{
			pos = i;
			break;
		}
	}
	return pos;
}
