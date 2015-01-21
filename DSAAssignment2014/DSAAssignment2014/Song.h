#pragma once
#include <string>
using namespace std;

class Song
{
private:
	string tid;
	string artistName;
	string title;
	string mxmTid;
	string mxmArtistName;
	string mxmTitle;

public:
	Song();
	Song(string tr, string a, string t, string mtr, string ma, string mt);
	~Song();

	void setTid(string tr);
	string getTid();

	void setArtistName(string a);
	string getArtistName();

	void setTitle(string t);
	string getTitle();

	void setMxmTid(string mtr);
	string getMxmtid();

	void setMxmArtistName(string ma);
	string getMxmArtistName();

	void setMxmTitle(string mt);
	string getMxmTitle();
};