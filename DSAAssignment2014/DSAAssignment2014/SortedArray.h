#pragma once
#include<string>
#include<iostream>
#include "Song.h"

using namespace std;

typedef Song ItemType;

class SortedArray
{
private:
	int count;
	int size;
	ItemType * items;

public:
	
	SortedArray();//Default Constructor

	SortedArray(int); //Constructor

	~SortedArray(); //Deconstructor

	//Sorted adding of an item into a list
	//Pre-Condition: count < size
	//Post-Condition: Item is added to the list. Items after it are shifted 1 position
	bool add(ItemType);

	//Sorted adding of an item into a list
	//Pre-Condition: There is an item in the array
	//Post-Condition: Item at index is removed from the array
	bool remove(int);

	ItemType get(int);

	int getCount();

	void print();

	int sequentialSearch(string);

	int binarySearch(string, int, int);
};

