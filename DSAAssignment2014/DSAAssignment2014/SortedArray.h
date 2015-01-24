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
	SortedArray(int);

	~SortedArray();

	bool add(ItemType);

	bool remove(int);

	ItemType get(int);

	int getCount();

	void print();

	bool sequentialSearch(string);

	bool binarySearch(string, int, int);
};

