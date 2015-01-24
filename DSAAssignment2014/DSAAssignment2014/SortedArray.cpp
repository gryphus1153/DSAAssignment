#include "SortedArray.h"


// default constructor
SortedArray::SortedArray()
{

}

SortedArray::SortedArray(int s)
{
	count = 0;
	size = s;
	items = new ItemType[size];
}

SortedArray::~SortedArray()
{

}

bool SortedArray::add(ItemType newItem)
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
			int index = 0;
			for (int i = 0; i < size; i++)
			{
				if (items[i].getTid().compare(newItem.getTid()) > 0)
				{
					index = i;
					break;
				}
				else 
					index = count;
			}
			for (int i = count; i > index; i--)
			{
				items[i] = items[i - 1];
			}
			items[index] = newItem;
			count++;
		}
	}
	return success;
}

bool SortedArray::remove(int index)
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
	return success;
}

ItemType SortedArray::get(int index)
{
	ItemType dataItem;
	bool success = (index >= 0) && (index <= size);
	if (success)
		dataItem = items[index];

	return dataItem;
}

int SortedArray::getCount()
{
	return count;
}

void SortedArray::print()
{
	for (int i = 0; i < getCount(); i++)
	{
		cout << get(i).getTid() << endl;
	}
}

bool SortedArray::sequentialSearch(string target)
{
	bool success = false;
	for (int i = 1; i < getCount(); i++)
	{
		if (get(i).getTid() == target) // found
		{
			success = true;
			break;
		}
	}
	return success;
}

bool SortedArray::binarySearch(string target, int start, int end)
{
	int middle = (start + end) / 2;

	if (end < start)
	{
		return false;
	}
	else if (items[middle].getTid().compare(target) < 0)
	{
		return binarySearch(target, middle, end);
	}
	else if (items[middle].getTid().compare(target) > 0)
	{
		return binarySearch(target, start, middle);
	}
	else
	{
		return true;
	}
}