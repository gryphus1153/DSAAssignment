#pragma once
//UnsortedArray.cpp
#include "UnsortedArray.h" //header file

// default constructor
UnsortedArray::UnsortedArray()
{
	count = 0;
}

//constructor
UnsortedArray::UnsortedArray(int s)
{
	count = 0;
	size = s;
	items = new ItemType[size];
}

UnsortedArray::~UnsortedArray()
{

}

//add a new item to the back of the list (append)
bool UnsortedArray::add(ItemType newItem)
{
	bool success = false;
	if (getCount() < size)
	{
		if (getCount() == 0)
		{
			items[0] = newItem;
			success = true;
			count++;
		}
		else
		{
			items[count] = newItem;
			count++;
		}
	}
	return success;
}

// add a new item at a specified position in the list (insert)
bool UnsortedArray::add(int index, ItemType newItem)
{
	bool success = (index >= 1) && (index <= size + 1);
	if (success)
	{  // make room for new item by shifting all items at
		// positions >= index toward the end of the
		// List (no shift if index == size + 1)
		for (int pos = size; pos >= index; pos--)
			items[pos] = items[pos - 1];
		// insert new item
		items[index - 1] = newItem;
		size++;  // increase the size of the list by one
	}
	return success;
}

// remove an item at a specified position in the list
void UnsortedArray::remove(int index)
{
	bool success = (index >= 1) && (index <= size);
	if (success)
	{  // delete item by shifting all items at positions >
		// index toward the beginning of the list
		// (no shift if index == size)
		for (int i = index - 1; i < size - 1; i++)
			items[i] = items[i + 1];
		size--;  // decrease the size of the list by one
	}

}

// get an item at a specified position of the list (retrieve)
ItemType UnsortedArray::get(int index)
{
	ItemType dataItem;
	bool success = (index >= 1) && (index <= size);
	if (success)
		dataItem = items[index - 1];

	return dataItem;
}

// check the size of the list
int UnsortedArray::getCount()
{
	return count;
}



//display items in unsorted array
void UnsortedArray::print()
{
	for (int i = 1; i <= getCount(); i++)
	{
		ItemType item = get(i);
		cout << item.getTid() << endl;
	}
}

// to do sequential search
int UnsortedArray::sequentialSearch(string target)
{
	int pos = -1;
	for (int i = 0; i < getCount(); i++)
	{
		if (items[i].getTid().compare(target) == 0) // found
		{
			pos = i + 1;
			break;
		}
	}
	return pos;
}
	  