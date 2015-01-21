#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "Song.h"

using namespace std;

vector<Song> songVector;
int linesLoaded;

void readSongs();//reads in a specified amount of song data

void main()
{
	cout << "Please enter the number of lines to be pre-loaded: ";
	cin >> linesLoaded;
	readSongs();
	cout << linesLoaded << " lines were loaded into an STL Vector" << endl;
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