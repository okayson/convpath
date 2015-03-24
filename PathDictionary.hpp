#ifndef _PATHDICTIONARY_HPP
#define _PATHDICTIONARY_HPP

#include <string>

using namespace std;

//------------------------------------------------------------------------------
class PathDictionary
{
public:
	PathDictionary() {}
	virtual ~PathDictionary() {}

	string find(const char* line)
	{
		return find(string(line));
	}
	virtual string find(const string& line) = 0;
	virtual void print() = 0;
};

#endif // _PATHDICTIONARY_HPP
