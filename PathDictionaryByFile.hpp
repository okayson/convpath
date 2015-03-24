#ifndef _PATHDICTIONARYBYFILE_HPP
#define _PATHDICTIONARYBYFILE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "PathDictionary.hpp"

using namespace std;

//------------------------------------------------------------------------------
class PathDictionaryByFile : public PathDictionary
{
	static const string defaultRootDir;

	typedef vector<string>::iterator PathIterator;
	string fileName;
	vector<string> paths;
public:
	PathDictionaryByFile(string fileName) : fileName(fileName)
	{
		update();
	}
	virtual ~PathDictionaryByFile() {}
	void update()
	{
		ifstream fin(fileName.c_str());

		while ( !fin.eof() )
		{
			char lineBuffer[1024];
			fin.getline(lineBuffer, sizeof(lineBuffer));
			paths.push_back(lineBuffer);
		}

		fin.close();
	}
	virtual string find(const string& name)
	{
		string compStr("/" + name);

		for ( PathIterator ite = paths.begin(); ite != paths.end(); ite++ )
		{
			if ((compStr.length() <= ite->length()) && 
				(compStr == ite->substr(ite->length() - compStr.length())))
			{
				return *ite;
			}
		}
		return string();
	}
	virtual void print()
	{
		for ( PathIterator ite = paths.begin(); ite != paths.end(); ite++ )
		{
			cout << *ite << endl;
		}
	}
private:
	bool ignore(const string& dir)
	{
		return ((dir == ".") || (dir == ".."));
	}
};
//------------------------------------------------------------------------------

#endif	// _PATHDICTIONARYBYFILE_HPP
