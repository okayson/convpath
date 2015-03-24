#ifndef _OPTIONS_HPP
#define _OPTIONS_HPP

#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

class Options
{
	bool isRequiredPrint_;
	string directory;

public:
	Options() : isRequiredPrint_(false) {}
	~Options() {}

	bool parse(int argc, char* argv[])
	{
		int option;

		while ( (option = getopt(argc, argv, "hpd:")) != -1 )
		{
			switch (option)
			{
			case 'h':	// display help
				displayUsage();
				return false;
			case 'p':	// print dictionary
				isRequiredPrint_ = true;
				break;
			case 'd':	// specify a directory
				directory = optarg;
				break;
			case 'f':	// <TBD>
				// This option is able to specify a file which means dictionary.
				break;
			case 't':	// <TBD>
				// This option measure processing time.
				break;
			case '?':
				return false;
			}
		}
		return true;
	}
	void displayUsage() const
	{
		cout << "Usage: convpath [OPTION]..." << endl;
		cout << "Convert path strings. ";
		cout << "Input is standard input. ";
		cout << "Output is standard output." << endl;
		cout << endl;
		cout << "OPTION:" << endl;
		cout << "  -h     " << "display this help and exit." << endl;
		cout << "  -d     " << "specify a target directory(the default is '.')." << endl;
		cout << "  -p     " << "list files in a target directory and exit." << endl;
		cout << endl;
		cout << "EXAMPLE:" << endl;
		cout << "  Convert a result of 'make':" << endl;
		cout << "    $ make 2>&1 | convpath" << endl;
		cout << "  ...and output to a file:" << endl;
		cout << "    $ make 2>&1 | convpath > filename" << endl;
		cout << "  ...output to standard output and filename:" << endl;
		cout << "    $ make 2>&1 | convpath | tee filename" << endl;
		cout << endl;
		cout << "  Input from a file:" << endl;
		cout << "    $ cat filename | convpath" << endl;
	}
	bool isRequiredPrint() const
	{
		return isRequiredPrint_;
	}
	const string& getDirectory() const
	{
		return directory;
	}
};

#endif // _OPTIONS_HPP
