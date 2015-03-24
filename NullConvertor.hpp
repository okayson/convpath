#ifndef _NULLCONVERTOR_HPP
#define _NULLCONVERTOR_HPP

#include <string>
#include "Convertor.h"

using namespace std;

//------------------------------------------------------------------------------
class NullConvertor : public Convertor
{
public:
	NullConvertor() {}
	virtual ~NullConvertor() {}

	virtual string convert(const string& line)
	{
		return string(line);
	}
};

#endif // _NULLCONVERTOR_HPP
