#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "Song.h"
#include <time.h>
#include "SortedArray.h"
#include <Windows.h>

using namespace std;

vector<Song> songVector;
int linesLoaded;

void readSongs();//reads in a specified amount of song data

void main()
{
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