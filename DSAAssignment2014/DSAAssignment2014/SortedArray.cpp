#include "SortedArray.h"


// default constructor
SortedArray::SortedArray()
{
	count = 0;
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
		for (int i = index - 1; i < count - 1; i++)
			items[i] = items[i + 1];
		count--;  // decrease the size of the list by one
	}
	return success;
}

ItemType SortedArray::get(int index)
{
	ItemType dataItem;
	bool success = (index >= 0) && (index <= size);
	if (success)
		return items[index];

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

int SortedArray::sequentialSearch(string target)
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

int SortedArray::binarySearch(string target, int start, int end)
{
	int middle = (start + end) / 2;

	if (end < start)
	{
		return -1;
	}
	else if (items[middle].getTid().compare(target) < 0)
	{
		return binarySearch(target, middle + 1, end);
	}
	else if (items[middle].getTid().compare(target) > 0)
	{
		return binarySearch(target, start, middle - 1);
	}
	else
	{
		return middle;
	}
}