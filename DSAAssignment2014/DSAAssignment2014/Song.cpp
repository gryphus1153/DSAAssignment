#include "Song.h"


Song::Song()
{
	tid = "";
	artistName = "";
	title = "";
	mxmTid = "";
	mxmArtistName = "";
	mxmTitle = "";
}

Song::Song(string tr, string a, string t, string mtr, string ma, string mt)
{
	tid = tr;
	artistName = a;
	title = t;
	mxmTid = mtr;
	mxmArtistName = ma;
	mxmTitle = mt;
}

Song::~Song()
{

}


void Song::setTid(string tr)
{
	tid = tr;
}

string Song::getTid()
{
	return tid;
}

void Song::setArtistName(string a)
{
	artistName = a;
}

string Song::getArtistName()
{
	return artistName;
}

void Song::setTitle(string t)
{
	title = t;
}

string Song::getTitle()
{
	return title;
}

void Song::setMxmTid(string mtr)
{
	mxmTid = mtr;
}

string Song::getMxmtid()
{
	return mxmTid;
}

void Song::setMxmArtistName(string ma)
{
	mxmArtistName = ma;
}

string Song::getMxmArtistName()
{
	return mxmArtistName;
}

void Song::setMxmTitle(string mt)
{
	mxmTitle = mt;
}

string Song::getMxmTitle()
{
	return mxmTitle;
}