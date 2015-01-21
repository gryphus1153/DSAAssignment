#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "Song.h"

using namespace std;

vector<Song> songVector;
int linesLoaded;

void readSongs();

void main()
{
	cout << "Please enter the number of lines to be loaded ";
	cin >> linesLoaded;
	readSongs();
}

void readSongs()
{
	int count = 1;
	string line;
	ifstream file ("mxm_779k_matches.txt");
	string delimiter = "<SEP>";
	while (getline(file, line) && count < (19 + linesLoaded))
	{
		string sarray[6];
		size_t pos = 0;
		string token;
		int arraycount = 0;
		if (count > 18 )
		{
			while ((pos = line.find(delimiter)) != string::npos)
			{
				token = line.substr(0, pos);
				sarray[arraycount] = token;
				line.erase(0, pos + delimiter.length());
				arraycount++;
			}
			sarray[5] = line;
			Song s = Song(sarray[0], sarray[1], sarray[2], sarray[3], sarray[4], sarray[5]);
			songVector.push_back(s);
		}
		count++;
	}
}