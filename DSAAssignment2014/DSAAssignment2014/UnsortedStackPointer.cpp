#pragma once
//UnsortedStackPointer.cpp
#include <iostream>
#include <cstddef>   
#include <new>       
#include "UnsortedStackPointer.h"  

using namespace std;

// constructor
UnsortedStackPointer::UnsortedStackPointer()
{
	topNode = NULL;
}

//	deconstructor
UnsortedStackPointer::~UnsortedStackPointer()
{

}

// add a new item at the top of the list
bool UnsortedStackPointer::push(ItemType& item)
{
	Node *newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;

	if (isEmpty())
	{
		topNode = newNode;
	}
	else
	{
		newNode->next = topNode;
		topNode = newNode;
	}
	return true;

}


//	removes item from the top of the list
bool UnsortedStackPointer::pop()
{
	if (!isEmpty())
	{
		Node *temp = new Node;
		temp = topNode;
		topNode = topNode->next;
		delete(temp);
		return true;
	}
	else {
		topNode = NULL;
		return false;
	}
}

//	removes specified item from the list
bool UnsortedStackPointer::pop(ItemType& item)
{
	Node *temp = new Node;
	if (!isEmpty())
	{
		temp = topNode;
		item = temp->item;
		topNode = topNode->next;
		delete(temp);
		return true;
	}
	else
		return false;
}

//	gets the item at the top of the list
void UnsortedStackPointer::getTop(ItemType& item)
{
	if (!isEmpty())
		item = topNode->item;
}

//	checks if the list is empty
bool UnsortedStackPointer::isEmpty() 
{
	if (topNode == NULL)
		return true;
	else
		return false;
}

//	displays list in order of insertion
void UnsortedStackPointer::print()
{

	UnsortedStackPointer s;
	ItemType t;
	while (!isEmpty())
	{
		getTop(t);
		s.push(t);
		pop();
	}

	while (!s.isEmpty())
	{
		s.getTop(t);
		push(t);
		s.pop();
		cout << t.getTid() << endl;
	}
}

// does sequential seach for items in the list
int UnsortedStackPointer::sequentialSearch(string target)
{
	UnsortedStackPointer s;
	ItemType t;
	int count = 0;
	while (!isEmpty())
	{
		getTop(t);
		if (t.getTid() == target)
			return count;				//returns the item
		else
		s.push(t);
		pop();
		count++;
	}
	return -1;
}
