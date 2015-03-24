#ifndef _NULLPATHDICTIONARY_HPP
#define _NULLPATHDICTIONARY_HPP

#include <string>
#include "PathDictionary.hpp"

using namespace std;

//------------------------------------------------------------------------------
class NullPathDictionary : public PathDictionary
{
public:
	NullPathDictionary() {}
	virtual ~NullPathDictionary() {}

	virtual string find(const string& line)
	{
		return string(line);
	}
	virtual void print()
	{
		cout << "Dictionary is empty()." << endl;
	}
};

#endif // _NULLPATHDICTIONARY_HPP
