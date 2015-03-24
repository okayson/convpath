#ifndef _MEASURE_HPP
#define _MEASURE_HPP

#include <chrono>

using namespace std;
using namespace std::chrono;

//------------------------------------------------------------------------------
class Measure
{
	time_point<system_clock> start_;
	time_point<system_clock> end_;

public:
	Measure()
	{
		start();
	}
	virtual ~Measure() 
	{
		stop();
		display();
	}
	void start()
	{
		start_ = system_clock::now();
	}
	void stop()
	{
		end_ = system_clock::now();
	}
	void display()
	{
		auto diff = end_ - start_;
		cout << "=========================================" << endl;
		cout << " Procssing Time: ";
		cout << duration_cast<milliseconds>(diff).count() << " milli secconds" << endl;
		cout << "=========================================" << endl;
	}
};
//------------------------------------------------------------------------------
#endif // _MEASURE_HPP

