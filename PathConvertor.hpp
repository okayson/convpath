#ifndef _PATHCONVERTOR_HPP
#define _PATHCONVERTOR_HPP

#include <string>
#include "Convertor.hpp"
#include "PathDictionary.hpp"

using namespace std;

//------------------------------------------------------------------------------
class PathConvertor : public Convertor
{
	PathDictionary* dic;

public:
	PathConvertor(PathDictionary* dic) : dic(dic) {}
	virtual ~PathConvertor() {}

	virtual string convert(const string& line)
	{
		if ( !isTargetLine(line) )
		{
			return string(line);
		}

		string path = getPath(line);
		string filename = getFileName(path);
		string newPath = dic->find(filename);
		return newPath.empty() ? string(line) : string(newPath + line.substr(path.length()));
	}
private:
	bool isTargetLine(const string& line)
	{
		return (isErrorLine(line) || isWarningLine(line) || isNoteLine(line));
	}
	bool isErrorLine(const string& line)
	{
		// Format is "xxx.c:999: error: ".
		return (string::npos != line.find(": error: "));
	}
	bool isWarningLine(const string& line)
	{
		// Format is "xxx.c:999: warning: ".
		return (string::npos != line.find(": warning: "));
	}
	bool isNoteLine(const string& line)
	{
		// Format is "xxx.c:999: note: ".
		return (string::npos != line.find(": note: "));
	}
	string getPath(const string& line)
	{
		return line.substr(0, line.find(":"));
	}
	string getFileName(const string& line)
	{
		string path = line.substr(0, line.find(":"));
		unsigned int pos = path.rfind("/");
		return (string::npos == pos) ? path : path.erase(0, pos + 1);
	}
};

#endif // _PATHCONVERTOR_HPP
