/*
source.cpp: Contains the main

Amirulamin Bin Mohd Osman (S10139137F)
Emmanuelle Myls Joie Gregorio (S10145392)

Highlighted Features:
GnuPlot is implemented to show the comparisons
*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

#include <ctime>
#include <time.h>
#include "Windows.h"
#include "psapi.h"
#include "GnuplotBridge.h"

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

void readSongs();			// reads in a specified amount of song data

void displayWelcome();		//	introduction
void viewList();			//	chooses type of list to display

void sortedArrayOptions(SortedArray &sArr);
void unsortedArrayOptions(UnsortedArray &uArr);
void unsortedPointerOptions(UnsortedPointer &uPtr);
void unsortedStackArrayOptions(UnsortedStackArray &uSArr);
void unsortedStackPointerOptions(UnsortedStackPointer &uSPtr);
void performanceOptions(SortedArray &sArr, UnsortedArray &uArr, UnsortedPointer &uPtr, UnsortedStackArray &uSArr, UnsortedStackPointer &uSPtr);

void displayMenu(int count);			//	shows options for list
void displayBinaryMenu(int count);	// shows options for lists with binary search option
void performanceMenu();
void performanceTypeMenu();

void main()
{
	//Variables
	clock_t t;				//CPU Clock
	SortedArray sArray;
	UnsortedArray uArray;
	UnsortedPointer uPointer;
	UnsortedStackArray uStackArray;
	UnsortedStackPointer uStackPointer;

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

		displayWelcome();	// official introduction
		viewList();			// show options for application
		cin >> option;

		switch (option)
		{
		case 1: //Sorted Array
			sortedArrayOptions(sArray);
			break;
		case 2: //Unsorted Array
			unsortedArrayOptions(uArray);
			break;
		case 3:
			unsortedPointerOptions(uPointer);
			break;
		case 4:
			unsortedStackArrayOptions(uStackArray);
			break;
		case 5:
			unsortedStackPointerOptions(uStackPointer);
			break;
		case 6:
			performanceOptions(sArray, uArray, uPointer, uStackArray, uStackPointer);
			break;
		case 0:
			break;
		default:
			cout << "Invalid option entered" << endl;
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
	cout << "3. Unsorted Pointer" << endl;
	cout << "4. Unsorted Stack Array" << endl;
	cout << "5. Unsorted Stack Pointer" << endl;
	cout << "6. Performance Comparison" << endl;
	cout << "0. Exit" << endl;
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

// displays Sequential Search Menu
void displaySequentialMenu(int count)
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

//  Options for UnsortedArray List
void unsortedArrayOptions(UnsortedArray &uArr)
{
	int option = 0;
	int songsLoaded = 0;
	do
	{
		cout << "\nUnsorted Array" << endl;
		displaySequentialMenu(uArr.getCount());
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

			uArr = UnsortedArray(songsLoaded);
			for (int i = 0; i < songsLoaded; i++)
			{
				uArr.add(songVector[i]);
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
					  uArr.remove(index);
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
					  int index = uArr.sequentialSearch(tid);
					  if (index == -1)
					  {
						  cout << "Song with Track ID " << tid << " not found" << endl;
					  }
					  else
					  {
						  Song s = uArr.get(index);
						  cout << "Tid: " << s.getTid() << " Title:" << s.getTitle() << endl;
					  }
				  }
		}
			break;


		case 4:
			uArr.print();
			break;

		case 0:
			break;

		default:
			cout << "Option entered was invalid." << endl;
			break;
		}
	} while (option != 0);
}

//void unsortedPointerOptions(UnsortedPointer &uPtr);
void unsortedPointerOptions(UnsortedPointer &uPtr)
{
	int option = 0;
	int songsLoaded = 0;
	do
	{
		cout << "\nUnsorted Pointer Array" << endl;
		displaySequentialMenu(uPtr.getCount());
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

			uPtr = UnsortedPointer();
			for (int i = 0; i < songsLoaded; i++)
			{
				uPtr.add(songVector[i]);
				songsLoaded -= 1;
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
					  uPtr.remove(index);
					  songsLoaded -= 1;
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
					  int index = uPtr.sequentialSearch(tid);
					  if (index == -1)
					  {
						  cout << "Song with Track ID " << tid << " not found" << endl;
					  }
					  else
					  {
						  Song s = uPtr.get(index);
						  cout << "Tid: " << s.getTid() << " Title:" << s.getTitle() << endl;
					  }
				  }
		}
			break;


		case 4:
			uPtr.print();
			break;

		case 0:
			break;

		default:
			cout << "Option entered was invalid." << endl;
			break;
		}
	} while (option != 0);

}

//void unsortedStackArrayOptions(UnsortedStackArray &uSArr);
void unsortedStackArrayOptions(UnsortedStackArray &uSArr)
{
	int option = 0;
	int songsLoaded = 0;
	int index = 0;
	do
	{
		cout << "\nUnsorted Stack Array" << endl;
		displaySequentialMenu(uSArr.getCount());
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

			uSArr = UnsortedStackArray(songsLoaded);
			for (int i = 0; i < songsLoaded; i++)
			{
				uSArr.push(songVector[i]);
			}
			break;

		case 2:
		{
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
				uSArr.remove(index);
				songsLoaded -= 1;
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
				int index = uSArr.sequentialSearch(tid);
				if (index == -1)
				{
					cout << "Song with Track ID " << tid << " not found" << endl;
				}
				else
				{
					Song s = uSArr.get(index);
					cout << "Tid: " << s.getTid() << " Title:" << s.getTitle() << endl;
				}
			}
		}
			break;


		case 4:
			uSArr.print();
			break;

		case 0:
			break;

		default:
			cout << "Option entered was invalid." << endl;
			break;
		}
	} while (option != 0);
}

//void unsortedStackPointerOptions(UnsortedStackPointer &uSPtr);
void unsortedStackPointerOptions(UnsortedStackPointer &uSPtr)
{
	int option = 0;
	int songsLoaded = 0;
	do
	{
		cout << "\nUnsorted Stack Pointer" << endl;
		displaySequentialMenu(uSPtr.getCount());
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

			uSPtr = UnsortedStackPointer();

			for (int i = 0; i < songsLoaded; i++)
			{
				uSPtr.push(songVector[i]);
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
					  uSPtr.remove(index);
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
					  int index = uSPtr.sequentialSearch(tid);
					  if (index == -1)
					  {
						  cout << "Song with Track ID " << tid << " not found" << endl;
					  }
					  else
					  {
						  Song s = uSPtr.get(index);
						  cout << "Tid: " << s.getTid() << " Title:" << s.getTitle() << endl;
					  }
				  }
		}
			break;


		case 4:
			uSPtr.print();
			break;

		case 0:
			break;

		default:
			cout << "Option entered was invalid." << endl;
			break;
		}
	} while (option != 0);

}

void performanceOptions(SortedArray &sArr, UnsortedArray &uArr, UnsortedPointer &uPtr, UnsortedStackArray &uSArr, UnsortedStackPointer &uSPtr)
{
	int option;
	int option2;
	Gnuplot plot;
	clock_t t;
	float time;
	int mStart;
	int m;
	PROCESS_MEMORY_COUNTERS pmc;
	int numberOfTimes[8] = { 1, 10, 100, 200, 400, 600, 800, 1000 };
	string dataStructType[5] = { "sArr", "uArr", "uPtr" };
	string dataStructFunction[5] = { "Add", "SeqS", "BinS", "Disp", "Remove" };
	string perfType[2] = { "Cpu", "Mem" };

	ofstream cpuAddFile;
	ofstream memAddFile;

	ofstream cpuSeqSFile;
	ofstream memSeqSFile;

	ofstream cpuBinSFile;
	ofstream memBinSFile;

	ofstream cpuDispFile;
	ofstream memDispFile;

	ofstream cpuRemoveFile;
	ofstream memRemoveFile;

	//sArr
	cpuAddFile.open(dataStructType[0] + dataStructFunction[0] + perfType[0] + ".dat");
	memAddFile.open(dataStructType[0] + dataStructFunction[0] + perfType[1] + ".dat");

	cpuSeqSFile.open(dataStructType[0] + dataStructFunction[1] + perfType[0] + ".dat");
	memSeqSFile.open(dataStructType[0] + dataStructFunction[1] + perfType[1] + ".dat");

	cpuBinSFile.open(dataStructType[0] + dataStructFunction[2] + perfType[0] + ".dat");
	memBinSFile.open(dataStructType[0] + dataStructFunction[2] + perfType[1] + ".dat");

	cpuDispFile.open(dataStructType[0] + dataStructFunction[3] + perfType[0] + ".dat");
	memDispFile.open(dataStructType[0] + dataStructFunction[3] + perfType[1] + ".dat");

	cpuRemoveFile.open(dataStructType[0] + dataStructFunction[4] + perfType[0] + ".dat");
	memRemoveFile.open(dataStructType[0] + dataStructFunction[4] + perfType[1] + ".dat");

	cout << "Processing Sorted Array...";
	for (int i = 0; i < 8; i++)
	{
		//adding
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		sArr = SortedArray(numberOfTimes[i]);
		for (int n = 0; n < numberOfTimes[i]; n++)
		{
			sArr.add(songVector[n]);
		}
		t = clock() - t;

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuAddFile << numberOfTimes[i] << " " << time << endl;
		memAddFile << numberOfTimes[i] << " " << (m/4096) << endl;

		//sequential Search
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		sArr.sequentialSearch("a");

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuSeqSFile << numberOfTimes[i] << " " << time << endl;
		memSeqSFile << numberOfTimes[i] << " " << (m / 4096) << endl;

		//binary Search
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		sArr.binarySearch("a", 0, sArr.getCount()-1);

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuBinSFile << numberOfTimes[i] << " " << time << endl;
		memBinSFile << numberOfTimes[i] << " " << (m / 4096) << endl;

		//display
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		sArr.print();

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuDispFile << numberOfTimes[i] << " " << time << endl;
		memDispFile << numberOfTimes[i] << " " << (m / 4096) << endl;

		//remove
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		sArr.remove(sArr.getCount());

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuRemoveFile << numberOfTimes[i] << " " << time << endl;
		memRemoveFile << numberOfTimes[i] << " " << (m / 4096) << endl;
	}
	cpuAddFile.close();
	memAddFile.close();

	cpuSeqSFile.close();
	memSeqSFile.close();

	cpuBinSFile.close();
	memBinSFile.close();

	cpuDispFile.close();
	memDispFile.close();

	cpuRemoveFile.close();
	memRemoveFile.close();
	cout << "Done" << endl;

	//uArr
	cpuAddFile.open(dataStructType[1] + dataStructFunction[0] + perfType[0] + ".dat");
	memAddFile.open(dataStructType[1] + dataStructFunction[0] + perfType[1] + ".dat");

	cpuSeqSFile.open(dataStructType[1] + dataStructFunction[1] + perfType[0] + ".dat");
	memSeqSFile.open(dataStructType[1] + dataStructFunction[1] + perfType[1] + ".dat");

	cpuDispFile.open(dataStructType[1] + dataStructFunction[3] + perfType[0] + ".dat");
	memDispFile.open(dataStructType[1] + dataStructFunction[3] + perfType[1] + ".dat");

	cpuRemoveFile.open(dataStructType[1] + dataStructFunction[4] + perfType[0] + ".dat");
	memRemoveFile.open(dataStructType[1] + dataStructFunction[4] + perfType[1] + ".dat");

	cout << "Processing Unsorted Array...";
	for (int i = 0; i < 8; i++)
	{
		//adding
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		uArr = UnsortedArray(numberOfTimes[i]);
		for (int n = 0; n < numberOfTimes[i]; n++)
		{
			uArr.add(songVector[n]);
		}
		t = clock() - t;

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuAddFile << numberOfTimes[i] << " " << time << endl;
		memAddFile << numberOfTimes[i] << " " << (m / 4096) << endl;

		//sequential Search
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		uArr.sequentialSearch("a");

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuSeqSFile << numberOfTimes[i] << " " << time << endl;
		memSeqSFile << numberOfTimes[i] << " " << (m / 4096) << endl;

		//display
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		uArr.print();

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuDispFile << numberOfTimes[i] << " " << time << endl;
		memDispFile << numberOfTimes[i] << " " << (m / 4096) << endl;

		//remove
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		uArr.remove(uArr.getCount());

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuRemoveFile << numberOfTimes[i] << " " << time << endl;
		memRemoveFile << numberOfTimes[i] << " " << (m / 4096) << endl;
	}
	cpuAddFile.close();
	memAddFile.close();

	cpuSeqSFile.close();
	memSeqSFile.close();

	cpuDispFile.close();
	memDispFile.close();

	cpuRemoveFile.close();
	memRemoveFile.close();
	cout << "Done" << endl;

	//uArr
	cpuAddFile.open(dataStructType[2] + dataStructFunction[0] + perfType[0] + ".dat");
	memAddFile.open(dataStructType[2] + dataStructFunction[0] + perfType[1] + ".dat");

	cpuSeqSFile.open(dataStructType[2] + dataStructFunction[1] + perfType[0] + ".dat");
	memSeqSFile.open(dataStructType[2] + dataStructFunction[1] + perfType[1] + ".dat");

	cpuDispFile.open(dataStructType[2] + dataStructFunction[3] + perfType[0] + ".dat");
	memDispFile.open(dataStructType[2] + dataStructFunction[3] + perfType[1] + ".dat");

	cpuRemoveFile.open(dataStructType[2] + dataStructFunction[4] + perfType[0] + ".dat");
	memRemoveFile.open(dataStructType[2] + dataStructFunction[4] + perfType[1] + ".dat");

	cout << "Processing Unsorted Array...";
	for (int i = 0; i < 8; i++)
	{
		//adding
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		uPtr = UnsortedPointer();
		for (int n = 0; n < numberOfTimes[i]; n++)
		{
			uPtr.add(songVector[n]);
		}
		t = clock() - t;

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuAddFile << numberOfTimes[i] << " " << time << endl;
		memAddFile << numberOfTimes[i] << " " << (m / 4096) << endl;

		//sequential Search
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		uPtr.sequentialSearch("a");

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuSeqSFile << numberOfTimes[i] << " " << time << endl;
		memSeqSFile << numberOfTimes[i] << " " << (m / 4096) << endl;

		//display
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		uPtr.print();

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuDispFile << numberOfTimes[i] << " " << time << endl;
		memDispFile << numberOfTimes[i] << " " << (m / 4096) << endl;

		//remove
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();

		uPtr.remove(uPtr.getCount());

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		time = ((float)t / CLOCKS_PER_SEC);
		cpuRemoveFile << numberOfTimes[i] << " " << time << endl;
		memRemoveFile << numberOfTimes[i] << " " << (m / 4096) << endl;
	}
	cpuAddFile.close();
	memAddFile.close();

	cpuSeqSFile.close();
	memSeqSFile.close();

	cpuDispFile.close();
	memDispFile.close();

	cpuRemoveFile.close();
	memRemoveFile.close();
	cout << "Done" << endl;

	do
	{
		performanceMenu();
		cin >> option;
		switch (option)
		{
		case 1:
			performanceTypeMenu();
			cin >> option2;
			switch (option2)
			{
			case 1:
				plot("   plot \"sArrAddCpu.dat\" with linespoints, \"uArrAddCpu.dat\" with linespoints, \"uPtrAddCpu.dat\" with linespoints");
				break;
			case 2:
				plot("plot \"sArrAddMem.dat\" with linespoints, \"uArrAddMem.dat\" with linespoints, \"uPtrAddMem.dat\" with linespoints");
				break;
			default:
				break;
			}
			break;

		case 2:
			performanceTypeMenu();
			cin >> option2;
			switch (option2)
			{
			case 1:
				plot("   plot \"sArrRemoveCpu.dat\" with linespoints, \"uArrRemoveCpu.dat\" with linespoints, \"uPtrRemoveCpu.dat\" with linespoints");
				break;
			case 2:
				plot("plot \"sArrRemoveMem.dat\" with linespoints, \"uArrRemoveMem.dat\" with linespoints, \"uPtrRemoveMem.dat\" with linespoints");
				break;
			default:
				break;
			}
			break;
		case 3:
			performanceTypeMenu();
			cin >> option2;
			switch (option2)
			{
			case 1:
				plot("   plot \"sArrSeqSCpu.dat\" with linespoints, \"uArrSeqSCpu.dat\" with linespoints, \"uPtrSeqSCpu.dat\" with linespoints");
				break;
			case 2:
				plot("plot \"sArrSeqSMem.dat\" with linespoints, \"uArrSeqSMem.dat\" with linespoints, \"uPtrSeqSMem.dat\" with linespoints");
				break;
			default:
				break;
			}
			break;

		case 4:
			performanceTypeMenu();
			cin >> option2;
			switch (option2)
			{
			case 1:
				plot("   plot \"sArrDispCpu.dat\" with linespoints, \"uArrDispCpu.dat\" with linespoints, \"uPtrDispCpu.dat\" with linespoints");
				break;
			case 2:
				plot("plot \"sArrDispMem.dat\" with linespoints, \"uArrDispMem.dat\" with linespoints, \"uPtrDispMem.dat\" with linespoints");
				break;
			default:
				break;
			}
			break;

		case 5:
			performanceTypeMenu();
			cin >> option2;
			switch (option2)
			{
			case 1:
				plot("   plot \"sArrSeqSCpu.dat\" with linespoints, \"sArrBinSCpu.dat\" with linespoints");
				break;
			case 2:
				plot("   plot \"sArrSeqSMem.dat\" with linespoints, \"sArrBinSMem.dat\" with linespoints");
				break;
			default:
				break;
			}
			break;

		case 0:
			break;
		default:
			break;
		}
	} while (option != 0);
}

void performanceMenu()
{
	cout << endl;
	cout << "1. Compare add performance for all" << endl;
	cout << "2. Compare remove for all" << endl;
	cout << "3. Compare Sequential Search for all" << endl;
	cout << "4. Compare display performance for all" << endl;
	cout << "5. Compare search performance between Binary and Sequnential" << endl;
	cout << "0. Return to previous menu" << endl;
	cout << "Enter Option: ";
}
void performanceTypeMenu()
{
	cout << endl;
	cout << "1. Compare CPU Time" << endl;
	cout << "2. Compare Memory Usage" << endl;
	cout << "Enter Option: ";
}