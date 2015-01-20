#include <iostream>
#include <string>
#include<fstream>
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
	while (getline(file, line) && count < (19 + linesLoaded))
	{
		if (count > 18 )
		{
			cout << count - 18 << " : " << line << "\n";
		}
		count++;
	}
}