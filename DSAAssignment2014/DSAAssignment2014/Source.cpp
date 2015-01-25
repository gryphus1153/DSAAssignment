#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <ctime>
#include <time.h>
#include <Windows.h>

#include "Song.h"
#include <vector>
#include "SortedArray.h"
#include "UnsortedArray.h"
#include "UnsortedPointer.h"
#include "UnsortedStackArray.h"
#include "UnsortedStackPointer.h"


using namespace std;

int linesLoaded;
vector<Song> songVector;
int sessionNo = time(0);

void displayWelcome();		//	introduction
void viewList();			//	chooses type of list to display
void displayMenu(int count);			//	shows options for list
void displayBinaryMenu(int count);	// shows options for lists with binary search option
void readSongs();			// reads in a specified amount of song data

void sortedArrayOptions(SortedArray &sArr);
void unsortedArrayOptions(UnsortedArray &uArr);
void unsortedPointerOptions(UnsortedPointer &uPtr);
void unsortedStackArrayOptions(UnsortedStackArray &uSArr);
void unsortedStackPointerOptions(UnsortedStackPointer &uSPtr);
void performanceOptions(SortedArray &sArr, UnsortedArray &uArr, UnsortedPointer &uPtr);

void main()
{
	//Variables
	clock_t t;				//CPU Clock
	//Operations
	cout << "Please enter the number of lines to be pre-loaded (Range: 1 - 150,000). Enter 0 to Exit: ";
	do
	{
		cin >> linesLoaded;
		
		if (cin.fail())
		{
			cout << "Please enter a valid input: ";
		}
		else if (linesLoaded == 0)
		{
			exit(0);
		}
		else if (linesLoaded < 0 || linesLoaded > 150000)
		{
			cout << "Value input is outside the allowed range. Please enter another value: ";
		}
		cin.clear();
		cin.ignore(10000, '\n');
	} while (cin.fail() || (linesLoaded < 0 || linesLoaded > 150000));
	
	t = clock();
	readSongs();
	t = clock() - t;

	cout << linesLoaded << " lines were loaded into an STL Vector in ";
	cout << ((float)t / CLOCKS_PER_SEC) << " seconds" << endl << "\n";
	int option = 0;
	do
	{
		SortedArray sArray;
		UnsortedArray uArray;
		UnsortedPointer uPointer;

		displayWelcome();	// official introduction
		viewList();			// show options for application
		cin >> option;

		switch (option)
		{
		case 1: //Sorted Array
			sortedArrayOptions(sArray);
		case 2: //Unsorted Array
			//unsortedArrayOptions(uArray);
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
	cout << "What data structure do you want to use ?" << endl;
}

// see options for application
void displayMenu(int count)
{
	cout << endl;
	cout << "1. Add to Data Structure" << endl;
	if (count > 0)
	{
		cout << "2. Delete from Data Structure" << endl;
		cout << "3. Do Sequential Search" << endl;
		cout << "4. Print Track ID of all songs in Data Structure" << endl;
	}
	cout << "0. Return to previous menu" << endl;
	if (count == 0)
	{
		cout << "\nAdditional options require Songs to be added to the Data Structure" << endl << "\n";
	}
	cout << "Enter Option: ";
}

void displayBinaryMenu(int count)
{
	cout << endl;
	cout << "1. Add to Data Structure" << endl;
	if (count > 0)
	{
		cout << "2. Delete from Data Structure" << endl;
		cout << "3. Do Sequential Search" << endl;
		cout << "4. Do Binary Search" << endl;
		cout << "5. Print Track ID of all songs in Data Structure" << endl;
	}
	cout << "0. Return to previous menu" << endl;
	if (count == 0)
	{
		cout << "\nAdditional options require Songs to be added to the Data Structure" << endl << "\n";
	}
	cout << "Enter Option: ";
}

//	view data in the list
void viewList()
{
	cout << endl;
	cout << "1. Sorted Array" << endl;
	cout << "2. Unsorted Array" << endl;
	cout << endl;
	cout << "Enter Option: ";
}

void sortedArrayOptions(SortedArray &sArr)
{
	int option = 0;
	int songsLoaded = 0;
	do
	{
		cout << "\nSorted Array" << endl;
		displayBinaryMenu(sArr.getCount());
		cin >> option;
		switch (option)
		{
		case 1:
			cout << "Enter the number of Songs to be loaded (Range: 1 - " << linesLoaded << "). Enter 0 to Exit: ";

			do
			{
				cin >> songsLoaded;

				if (cin.fail())
				{
					cout << "Please enter a valid input: ";
				}
				else if (songsLoaded == 0)
				{
					break;
				}
				else if (songsLoaded < 0 || songsLoaded > linesLoaded)
				{
					cout << "Value input is outside the allowed range. Please enter another value: ";
				}
				cin.clear();
				cin.ignore(10000, '\n');
			} while (cin.fail() || (songsLoaded < 0 || songsLoaded > linesLoaded));

			sArr = SortedArray(songsLoaded);
			for (int i = 0; i < songsLoaded; i++)
			{
				sArr.add(songVector[i]);
			}
			break;

		case 2:
		{
				  int index = 0;
				  cout << "Enter the index of the Song to be removed (Range: 1 - " << songsLoaded << "). Enter 0 to Exit: ";

				  do
				  {
					  cin >> index;

					  if (cin.fail())
					  {
						  cout << "Please enter a valid input: ";
					  }
					  else if (index == 0)
					  {
						  break;
					  }
					  else if (index < 0 || index > songsLoaded)
					  {
						  cout << "Value input is outside the allowed range. Please enter another value: ";
					  }
					  cin.clear();
					  cin.ignore(10000, '\n');
				  } while (cin.fail() || (index < 0 || index > songsLoaded));

				  if (index != 0)
				  {
					  sArr.remove(index);
				  }
		}
			break;

		case 3:
		{
			string tid;
			cout << "Enter a TrackID. Enter 0 to return to previous menu: ";
			cin >> tid;
			if (tid != "0")
			{
				int index = sArr.sequentialSearch(tid);
				if (index == -1)
				{
					cout << "Song with Track ID " << tid << " not found" << endl;
				}
				else
				{
					Song s = sArr.get(index);
					cout << "Tid: " << s.getTid() << " Title:" << s.getTitle() << endl;
				}
			}
		}
			break;

		case 4:
		{
			string tid;
			cout << "Enter a TrackID. Enter 0 to return to previous menu: ";
			cin >> tid;
			if (tid != "0")
			{
				int index = sArr.binarySearch(tid, 0, sArr.getCount() -1);
				if (index == -1)
				{
					cout << "Song with Track ID " << tid << " not found" << endl;
				}
				else
				{
					Song s = sArr.get(index);
					cout << "Tid: " << s.getTid() << " Title:" << s.getTitle() << endl;
				}
			}
		}
			break;

		case 5:
			sArr.print();
			break;

		case 0:
			break;

		default: 
			cout << "Option entered was invalid." << endl;
			break;
		}
	} while (option != 0);
	
}

//void unsortedArrayOptions(UnsortedArray &uArr);
//void unsortedPointerOptions(UnsortedPointer &uPtr);
//void unsortedStackArrayOptions(UnsortedStackArray &uSArr);
//void unsortedStackPointerOptions(UnsortedStackPointer &uSPtr);

void performanceOptions(SortedArray &sArr, UnsortedArray &uArr, UnsortedPointer &uPtr)
{

}