//UnsortedArray.cpp
#include "UnsortedArray.h" //header file

//constructor
UnsortedArray::UnsortedArray()
{
	size = 0;
}

//add a new item to the back of the list (append)
bool UnsortedArray::add(ItemType newItem)
{
		items[size] = newItem; //add to the end of the list
		size++;
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


//display items in unsorted array
void UnsortedArray::print()
{
	for (int i = 1; i <= getLength(); i++)
	{
		ItemType item = get(i);// cout << items[i-1] << endl;
		// cout << item << endl;
	}
}

// to do sequential search
int search(int[] dataArray, int n, int target)
{
	for (int i = 0; i<n; i++)
	if (dataArray[i] == target) // found       return i;	      return -1; // not found 
}

	  