#include <iostream>
#include <string>
#include <memory>
#include "Options.hpp"
#include "PathDictionary.hpp"
#include "PathDictionaryBySearch.hpp"
#include "Convertor.hpp"
#include "PathConvertor.hpp"
#ifdef _MEASURE
#include "Measure.hpp"
Measure measure;
#endif

using namespace std;

//------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	Options opt;

	if ( !opt.parse(argc, argv) )
	{
		return 0;
	}

	auto_ptr<PathDictionary> dic(new PathDictionaryBySearch(opt.getDirectory()));

	if ( opt.isRequiredPrint() )
	{
		dic->print();
		return 0;
	}

	auto_ptr<Convertor> conv(new PathConvertor(dic.get()));

	while ( !cin.eof() )
	{
		char lineBuffer[1024];
		cin.getline(lineBuffer, sizeof(lineBuffer));
		cout << conv->convert(lineBuffer) << endl;
	}

	return 0;
}
