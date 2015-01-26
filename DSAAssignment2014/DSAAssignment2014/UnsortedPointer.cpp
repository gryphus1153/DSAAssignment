//UnsortedPointer.cpp
#include "UnsortedPointer.h"	// firstNodeer file
#include <cstddef>  // for NULL
#include <new>      // for bad_alloc

// default constructor
UnsortedPointer::UnsortedPointer()
{
	count = 0;
}

//constructor
UnsortedPointer::UnsortedPointer(int s)
{
	count = s;
	firstNode = NULL;
}

// deconstructor
UnsortedPointer::~UnsortedPointer()
{
}

// add a new item to the back of the list (append)
bool UnsortedPointer::add(ItemType newItem)
{
	// create a new node to store the data item
	Node *newNode = new Node;
	newNode->item = newItem;
	newNode->next = NULL;

	if (isEmpty())
		firstNode = newNode;
	else
	{
		Node *temp = firstNode;
		while (temp->next != NULL)
			temp = temp->next;		// move to last node
		temp->next = newNode;		// make last node point to the new node
	}

	size++;

	return true;  // no size constraint
}

// add a new item at a specified position in the list (insert)
bool UnsortedPointer::add(int index, ItemType newItem)
{
	bool success = (index >= 1) && (index <= size + 1);

	if (success)
	{
		// create a new node to store the data item
		Node *newNode = new Node;
		newNode->item = newItem;
		newNode->next = NULL;

		if (index == 1) // inserting in front
		{
			newNode->next = firstNode;
			firstNode = newNode;
		}
		else
		{
			Node *temp = firstNode;
			for (int i = 1; i<index - 1; i++)
				temp = temp->next;		// move to node at the position before the index

			newNode->next = temp->next;	// make new node point to the node pointed to by temp
			temp->next = newNode;		// make temp point to the new node
		}
		size++;
	}

	return success;
}

// remove an item at a specified position in the list
void UnsortedPointer::remove(int index)
{
	bool success = (index >= 1) && (index <= size);
	if (success)
	{
		if (index == 1) // remove front node
			firstNode = firstNode->next;
		else
		{
			Node *current = firstNode;
			Node *previous = firstNode;
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

// get an item at a specified position of the list (retrieve)
ItemType UnsortedPointer::get(int index)
{
	ItemType dataItem;
	bool success = (index >= 1) && (index <= size);
	if (success)
	{
		Node *current = firstNode;
		for (int i = 1; i<index; i++)
			current = current->next;		// move to next node

		dataItem = current->item;
	}

	return dataItem;
}

// check if the list is empty
bool UnsortedPointer::isEmpty()
{
	return size == 0;
}

// check the size of the list
int UnsortedPointer::getCount()
{
	return size;
}


void UnsortedPointer::print()
{
	Node *temp = firstNode;

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

//	to do sequential search

int UnsortedPointer::sequentialSearch(string target)
{
	ItemType dataItem;
	int count = 0;

		Node *current = firstNode;
	
		while (current->next !=NULL)
		{
			if (current->item.getTid() == target)
				return count;				//returns the item
			else
				current = current->next;		// move to next node
			count++;
		}
		return -1;

}


