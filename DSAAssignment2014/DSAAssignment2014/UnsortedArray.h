#pragma once
//UnsortedArray.h
#include<string>
#include<iostream>
#include "Song.h"

using namespace std;

typedef Song ItemType;

class UnsortedArray
{
	private:
		int size;
		ItemType * items;

	public:
		//constructor
		UnsortedArray(int s);

		//add a new item to the back of the list(append)
		// pre : size < MAX_SIZE
		// post: item is added to the end of the list
		bool add(ItemType newItem);

		// add a new item at a specified position in the list (insert)
		// pre : 1 <= index <= size && size < MAX_SIZE
		// post: item is added to a specified position in the list
		// items at the back are shifted backwards by 1 position
		bool add(int index, ItemType newItem);

		// remove an item at a specified position in the list
		// pre : 1 <= index <= size
		// post: item is removed the specified position in the list
		//       items after the position are shifted forward by 1 position
		//       size of list is decreased by 1
		void remove(int index);

		// get an item at a specified position of the list (retrieve)
		// pre : 1 <= index <= size
		// post: none
		// return the item in the specified index of the list
		ItemType get(int index);

		// check the size of the list
		// pre : none
		// post: none
		// return the number of items in the list
		int getLength();

		// to display all the items in the list
		// pre : none
		// post: none
		void print();

		// to do sequential search in the list
		ItemType search(string target);

};