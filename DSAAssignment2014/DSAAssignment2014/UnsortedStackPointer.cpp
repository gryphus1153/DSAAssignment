#pragma once
//UnsortedStackPointer.cpp
#include <iostream>
#include <cstddef>   
#include <new>       
#include "UnsortedStackPointer.h"  

using namespace std;

//default constructor
UnsortedStackPointer::UnsortedStackPointer()
{
	count = 0;
}

// constructor
UnsortedStackPointer::UnsortedStackPointer(int s)
{
	topNode = NULL;
	count = 0;
	size = s;
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
		count++;
	}
	else
	{
		newNode->next = topNode;
		topNode = newNode;
		count++;
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

// gets count
int UnsortedStackPointer::getCount()
{
	return count;
}

//	displays list in order of insertion
void UnsortedStackPointer::print()
{
	Node *temp = topNode;
	if (temp == NULL)
		cout << "The list is empty." << endl;
	else
	{
		while (temp != NULL)
		{
			cout << temp->item.getTid() << endl;
			temp = temp->next;		// move to next node
		}
	}
}


// removes item from index
void UnsortedStackPointer::remove(int index)
{
	bool success = (index >= 1) && (index <= size);
	if (success)
	{
		if (index == 1) // remove front node
			topNode = topNode->next;
		else
		{
			Node *current = topNode;
			Node *previous = topNode;
			for (int i = 1; i<index; i++)
			{
				previous = current;
				current = current->next;		// move to next node
			}

			previous->next = current->next;	// delete the current node by
		}		                                // making previous node point to the node pointed to by current node

		size--;  // decrease the size of the list by one
	}

}

// gets item from index
ItemType UnsortedStackPointer::get(int index)
{
	ItemType dataItem;
	bool success = (index >= 1) && (index <= size);
	if (success)
	{
		Node *current = topNode;
		for (int i = 0; i<index; i++)
			current = current->next;		// move to next node

		dataItem = current->item;
	}

	return dataItem;
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
			return count - 1;				//returns the item
		else
		s.push(t);
		pop();
		count++;
	}
	return -1;
}
