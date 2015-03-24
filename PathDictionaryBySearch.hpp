#ifndef _PATHDICTIONARYBYSEARCH_HPP
#define _PATHDICTIONARYBYSEARCH_HPP

#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include "PathDictionary.hpp"

using namespace std;

//------------------------------------------------------------------------------
class PathDictionaryBySearch : public PathDictionary
{
	static const string defaultRootDir;

	typedef vector<string>::iterator PathIterator;
	string rootDir;
	vector<string> paths;

public:
	PathDictionaryBySearch() : rootDir(defaultRootDir)
	{
		searchFilesIn(rootDir);
	}
	PathDictionaryBySearch(string dir) : rootDir(dir)
	{
		if ( rootDir.empty() )
		{
			rootDir = defaultRootDir;
		}
		searchFilesIn(rootDir);
	}
	virtual ~PathDictionaryBySearch() {}
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
	bool searchFilesIn(const string& dir)
	{
		DIR* dirHandle= opendir(dir.c_str());
		if ( NULL == dirHandle )
		{
			return false;
		}

		for ( struct dirent* entry = readdir(dirHandle); entry != NULL; entry = readdir(dirHandle) )
		{
			handle(dir, string(entry->d_name));
		}

		closedir(dirHandle);
		return true;
	}
	void handle(const string& dir, const string& name)
	{
		if ( ignore(name) )
		{
			return;
		}

		string path(dir + "/" + name);
		if ( !searchFilesIn(path) )
		{
			paths.push_back(path);
		}
	}
};

//------------------------------------------------------------------------------
const string PathDictionaryBySearch::defaultRootDir = ".";
//------------------------------------------------------------------------------

#endif	// _PATHDICTIONARYBYSEARCH_HPP
