#ifndef _CONVERTOR_HPP
#define _CONVERTOR_HPP

#include <string>

using namespace std;

//------------------------------------------------------------------------------
class Convertor
{
public:
	Convertor() {}
	virtual ~Convertor() {}

	string convert(const char* line)
	{
		return convert(string(line));
	}
	virtual string convert(const string& line) = 0;
};

#endif // _CONVERTOR_HPP
