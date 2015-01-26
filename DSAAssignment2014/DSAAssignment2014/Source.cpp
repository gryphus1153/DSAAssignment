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
void performanceMenu();
void plot(string);

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
		case 6:
			performanceOptions(sArray, uArray, uPointer);
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
				cout << i << endl;
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
void unsortedPointerOptions(UnsortedPointer &upArr)
{
	int option = 0;
	int songsLoaded = 0;
	do
	{
		cout << "\nUnsorted Pointer Array" << endl;
		displaySequentialMenu(upArr.getCount());////////////////////////
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

			upArr = UnsortedPointer(songsLoaded);
			for (int i = 0; i < songsLoaded; i++)
			{
				upArr.add(songVector[i]);
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
					  upArr.remove(index);
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
					  int index = upArr.sequentialSearch(tid);
					  if (index == -1)
					  {
						  cout << "Song with Track ID " << tid << " not found" << endl;
					  }
					  else
					  {
						  Song s = upArr.get(index);
						  cout << "Tid: " << s.getTid() << " Title:" << s.getTitle() << endl;
					  }
				  }
		}
			break;


		case 4:
			upArr.print();
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
		displaySequentialMenu(uSArr.getCount());////////////////////////
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
				  }
		}
			break;
		}
		}
	} while (true);
}
void performanceOptions(SortedArray &sArr, UnsortedArray &uArr, UnsortedPointer &uPtr)
{
	int option;
	int option2;
	Gnuplot plot;
	clock_t t;
	int mStart;
	int m;
	PROCESS_MEMORY_COUNTERS pmc;
	int numberOfTimes[6] = { 1, 10, 100, 1000, 10000, 100000 };
	string dataStructType[5] = { "sArr", "uArr", "uPtr" };
	string dataStructFunction[5] = { "Add", "Remove", "SeqS", "BinS", "Disp" };
	string perfType[2] = { "Cpu", "Mem" };
	ofstream cpuFile;
	ofstream memFile;

	//sArr
	cpuFile.open(dataStructType[0] + dataStructFunction[0] + perfType[0] + ".dat");
	memFile.open(dataStructType[0] + dataStructFunction[0] + perfType[1] + ".dat");
	cout << "processing..." << endl;
	for (int i = 0; i < 6 ; i++)
	{
		//adding
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		mStart = pmc.WorkingSetSize;
		t = clock();
		sArr = SortedArray(numberOfTimes[i]);
		for (int i = 0; i < numberOfTimes[i]; i++)
		{
			sArr.add(songVector[i]);
		}
		t = clock() - t;
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		m = pmc.WorkingSetSize - mStart;
		float time = ((float)t / CLOCKS_PER_SEC);
		cpuFile << numberOfTimes[i] << " " << time << endl;
		memFile << numberOfTimes[i] << " " << (m/4096) << endl;
	}
	cpuFile.close();
	memFile.close();

	////uArr
	//cpuFile.open(dataStructType[1] + perfType[0] + ".dat");
	//memFile.open(dataStructType[1] + perfType[1] + ".dat");
	//cout << "processing..." << endl;
	//for (int i = 0; i < 4; i++)
	//{

	//	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	//	mStart = pmc.WorkingSetSize;
	//	t = clock();
	//	uArr = UnsortedArray(numberOfTimes[i]);
	//	for (int i = 0; i < numberOfTimes[i]; i++)
	//	{
	//		uArr.add(songVector[i]);
	//	}
	//	t = clock() - t;
	//	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	//	m = pmc.WorkingSetSize - mStart;
	//	float time = ((float)t / CLOCKS_PER_SEC);
	//	cpuFile << numberOfTimes[i] << " " << time << endl;
	//	memFile << numberOfTimes[i] << " " << (m / 4096) << endl;
	//}
	//cpuFile.close();
	//memFile.close();

	////uArr
	//cpuFile.open(dataStructType[2] + perfType[0] + ".dat");
	//memFile.open(dataStructType[2] + perfType[1] + ".dat");
	//cout << "processing..." << endl;
	//for (int i = 0; i < 4; i++)
	//{
	//	//adding
	//	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	//	mStart = pmc.WorkingSetSize;
	//	t = clock();
	//	uPtr = UnsortedPointer();
	//	for (int i = 0; i < numberOfTimes[i]; i++)
	//	{
	//		uPtr.add(songVector[i]);
	//	}
	//	t = clock() - t;
	//	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	//	m = pmc.WorkingSetSize - mStart;
	//	float time = ((float)t / CLOCKS_PER_SEC);
	//	cpuFile << numberOfTimes[i] << " " << time << endl;
	//	memFile << numberOfTimes[i] << " " << (m / 4096) << endl;
	//	
	//}
	//cpuFile.close();
	//memFile.close();

	performanceMenu();
	cin >> option;
	switch (option)
	{
	case 1:

		cin >> option2;
		switch (option2)
		{
		case 1:
			plot("plot \"sArrAddCpu.dat\" with linespoints");// \"uArrCpu.dat\" with linespoints");
			break;
		case 2:
			plot("plot \"sArrMem.dat\" with linespoints, \"uArrMem.dat\" with linespoints");
		default:
			break;
		}
		break;

	case 2:
		break;
	default:
		break;
	}
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

//void unsortedStackPointerOptions(UnsortedStackPointer &uSPtr);
void unsortedStackPointerOptions(UnsortedStackPointer &uSPArr)
{
	int option = 0;
	int songsLoaded = 0;
	do
	{
		cout << "\nUnsorted Stack Pointer" << endl;
		displaySequentialMenu(uSPArr.getCount());////////////////////////
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

			uSPArr = UnsortedStackPointer(songsLoaded);

			for (int i = 0; i < songsLoaded; i++)
			{
				uSPArr.push(songVector[i]);
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
					  uSPArr.remove(index);
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
					  int index = uSPArr.sequentialSearch(tid);
					  if (index == -1)
					  {
						  cout << "Song with Track ID " << tid << " not found" << endl;
					  }
					  else
					  {
						  Song s = uSPArr.get(index);
						  cout << "Tid: " << s.getTid() << " Title:" << s.getTitle() << endl;
					  }
				  }
		}
			break;


		case 4:
			uSPArr.print();
			break;

		case 0:
			break;

		default:
			cout << "Option entered was invalid." << endl;
			break;
		}
	} while (option != 0);

}

//void performanceOptions(SortedArray &sArr, UnsortedArray &uArr, UnsortedPointer &uPtr)
//{

//}