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
	typedef vector<string>::iterator IgnoreDirIterator;

	string rootDir;
	vector<string> paths;
	vector<string> ignoreDirs;

public:
	PathDictionaryBySearch(string dir = defaultRootDir) : rootDir(dir)
	{
		if ( rootDir.empty() )
		{
			rootDir = defaultRootDir;
		}
		makeIgnoreDirs();
		makePathsIn(rootDir);
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
	void makeIgnoreDirs()
	{
		ignoreDirs.push_back(".");
		ignoreDirs.push_back("..");
		ignoreDirs.push_back(".git");
		ignoreDirs.push_back(".svn");
	}
	bool ignore(const string& dir)
	{
		for ( IgnoreDirIterator ite = ignoreDirs.begin(); ite != ignoreDirs.end(); ite++ )
		{
			if ( dir == *ite )
			{
				return true;
			}
		}
		return false;
	}
	bool makePathsIn(const string& dir)
	{
		DIR* hDir= opendir(dir.c_str());
		if ( NULL == hDir )
		{
			return false;
		}

		for ( struct dirent* entry = readdir(hDir); entry != NULL; entry = readdir(hDir) )
		{
			handleDir(dir, string(entry->d_name));
		}

		closedir(hDir);
		return true;
	}
	void handleDir(const string& dir, const string& name)
	{
		if ( ignore(name) )
		{
			return;
		}

		string path(dir + "/" + name);
		if ( !makePathsIn(path) )
		{
			paths.push_back(path);
		}
	}
};

//------------------------------------------------------------------------------
const string PathDictionaryBySearch::defaultRootDir = ".";
//------------------------------------------------------------------------------

#endif	// _PATHDICTIONARYBYSEARCH_HPP
