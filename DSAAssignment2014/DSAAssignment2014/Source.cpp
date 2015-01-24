#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "Song.h"
#include <time.h>
#include "SortedArray.h"
#include "UnsortedArray.h"
#include <Windows.h>

using namespace std;

vector<Song> songVector;
int linesLoaded;

void displayWelcome();	//	introduction
void displayMenu();		//	shows options for application
void viewList();		//	chooses type of list to display
void readSongs();		//reads in a specified amount of song data

void main()
{

	UnsortedArray uList;	// empty Unsorted List
	SortedArray sList;		// empty Sorted List

	clock_t t;
	cout << "Please enter the number of lines to be pre-loaded (Range: 1 - 150,000): ";
	do
	{
		cin >> linesLoaded;
		if (cin.fail())
		{
			cout << "Please enter a valid input: ";
		}
		else if (linesLoaded < 1 || linesLoaded > 150000)
		{
			cout << "Value input is outside the allowed range. Please enter another value: ";
		}
		cin.clear();
		cin.ignore(10000, '\n');
	} while (cin.fail() || (linesLoaded < 1 || linesLoaded > 150000));
	
	t = clock();
	readSongs();
	t = clock() - t;
	cout << linesLoaded << " lines were loaded into an STL Vector in ";
	cout << ((float)t / CLOCKS_PER_SEC) << " seconds" << endl;

	do
	{
		int option;			// init the inital option
		int option2 = 0;		// secondary option for selecting array
		int index = 0;			// Index for deleting 
		string trackID = ""		// Track ID when searching

		displayWelcome();		// official introduction
		displayMenu();			// show options for application
		
		if (option > 5)
			cout << "Invalid option. Choose from 0-5." << endl;
		else
			cout << endl;
		cout << "Enter option: ";

		cin >> option;		// to read users option

		switch (option)		// Selects according to user option
		{
			case 1:			// View List
				cout << "View List" << endl;
				viewList();	// show options for viewing list

				cout << "Enter option:" << endl;
				cin >> option2;	//

				if (option2 == 1)		// Displays data as Unsorted Array
				{
					uList.print();
					// INSERT SOMETHING TO STOP IT FROM GOING MENU
				}

				else if (option2 == 2)	// Displays data as Sorted Array
				{
					sList.print();
					// INSERT SOMETHING TO STOP IT FROM GOING MENU
				}

				break;

			case 2:		// Deletes
				
				system("cls");
				cout << "Delete from List" << endl;
				viewList();		// show options for viewing lists

				cout << "Enter option: ";
				cin >> option2;

				if (option2 == 1)	// delete from Unsorted Array
				{
					uList.print();
					cout << "Enter which index to delete: ";
					cin >> index;

					uList.remove(index);
					cout << "Succesful deletion." << endl;

					//INSERT SOMETHING TO KEEP IT FROM JUMPING TO THE MENU
				}

				else if (option2 == 2)
				{
					sList.print();
					cout << "Enter which index to delete: ";
					cin >> index;

					sList.remove(index);
					cout << "Succesful deletion." << endl;

					//INSERT SOMETHING TO KEEP IT FROM JUMPING TO THE MENU
				}

				break;

			case 3:		// perform sequential search

				system("cls");
				cout << "Sequential Search" << endl;
				viewList;	// options for viewing list

				cout << "Enter option: ";
				cin >> option;

				if (option2 == 1)	// Search data from Unsorted Array
				{
					cout << "Enter the Track ID: ";
					cin >> trackID;

					uList.search(trackID);

					//INSERT SOMETHING TO KEEP IT FROM JUMPING TO THE MENU
				}

				else if (option2 == 2)	// search data from Sorted Array
				{
					cout << "Enter the Track ID: ";
					cin >> trackID;

					sList.sequentialSearch(trackID);

					// INSERT SOMETHING TO KEEP IT FROM JUMPING TO THE MENU
				}

				break;
				
			case 4:		// performs binary search

				system("cls");
				cout << "Binary Search for Sorted Array" << endl;

				cout << "Enter the Track ID: ";
				cin >> trackID;

				sList.binarySearch(trackID);

				// INSERT SOMETHING TO KEEP IT FROM JUMPING TO THE MENU

				break;

			//case 5:       // Performance

			case 0: 
				cout << "Terminating..." << endl;
				break;

			default:
				break;
		}
	}while (option != 0);	// Loop the menu
}


void readSongs()
{
	int count = 1;
	string line;
	ifstream file ("mxm_779k_matches.txt");
	string delimiter = "<SEP>";//splits by delimiter
	while (getline(file, line) && count < (19 + linesLoaded))
	{
		string sarray[6]; //creates a temp array to store the strings
		size_t pos = 0; //position of the character
		string token; //token
		int arraycount = 0;
		if (count > 18 )
		{
			while ((pos = line.find(delimiter)) != string::npos)//gets the position of the delimiter within the line
			{
				token = line.substr(0, pos);//gets token from position 0 to position pos
				sarray[arraycount] = token;//stores the token in the temparray
				line.erase(0, pos + delimiter.length());//removes the token + "<SEP>" from line
				arraycount++;
			}
			sarray[5] = line; //gets the remaining data that is not added to the array
			Song s = Song(sarray[0], sarray[1], sarray[2], sarray[3], sarray[4], sarray[5]);//creates Song
			songVector.push_back(s);//stores Song into the array
		}
		count++;
	}
}

//	Intro 
void displayWelcome()
{
	cout << "Welcome to Data Structure Comparison Application." << endl;
	cout << "What do you want to do ?" << endl;
}

// see options for application
void displayMenu()
{
	cout << endl;
	cout << "1. View List" << endl;
	cout << "2. Delete from List" << endl;
	cout << "3. Do Sequential Search" << endl;
	cout << "4. Do Binary Search" << endl;
	cout << "5. View Performance Information" << endl;
	cout << "0. Terminate Application" << endl;
	cout << endl;
}

//	view data in the list
void viewList()
{
	cout << endl;
	cout << "1. Unsorted Array" << endl;
	cout << "2. Sorted Array" << endl;
	cout << endl;
}

bool loadToUnsorted(vector<Song>*SongData, UnsortedArray* uList, int size)
{
	for (int i = 0; i < size; i++)
	{
		uList->add(SongData->at(i));
	}
	return true;
}

bool loadToSorted(vector<Song>*SongData, SortedArray* sList)
{
	int size = sList->getCount();

	for (int i = 0; i < size; i++)
	{
		if (i == 5000)
			cout << "placeholder";
		sList->add(SongData->at(i));   // I DONT KNOW HOW TO ADD IT IN ASCENDING MANNER
	}

	return true;
}
