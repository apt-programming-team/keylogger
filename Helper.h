#ifndef HELPER_H
#define HELPER_H

#include <ctime>
#include <string>
#include <sstream>
#include <fstream>

namespace Helper
{

	template <class T> //create generic template to accept all types

	std::string ToString(const T &e);

	struct DateTime
	{

    	DateTime()
    	{
        	time_t ms; //puts system time into this variable
        	time(&ms);

        	struct tm *info = localtime(&ms); //points to system time information

        	//putting system time information into human-readable format
        	D = info->tm_mday; //D is a day
        	m = info->tm_mon + 1; //m is a month, add 1 because it starts from 0
        	y = 1900 + info->tm_year; //y is a year
        	M = info->tm_min; //minutes
        	H = info->tm_hour; //hours
        	S = info->tm_sec; //seconds
    	}

    	//initialize DateTime instance with user parameters
    	DateTime(int D, int m, int y, int H, int M, int S) : D(D), m(m), y(y), H(H), M(M), S(S) {}

    	//initialize the time as zero
    	DateTime(int D, int m, int y) : D(D), m(m), y(y), H(0), M(0), S(0) {}

    	//return current date and time
    	DateTime Now() const
    	{
        	return DateTime();
    	}

    	int D, m, y, H, M, S;

    	//format Date to a human readable string (DD.mm.yyyy)
    	std::string GetDateString() const
    	{
        	return std::string (D < 10 ? "0" : "") + ToString(D) +
               	std::string (m < 10 ? ".0" : ".") + ToString(m) + "." +
               	ToString(y);
    	}

    	//format Time to a human readable string (HH:MM:SS)
    	std::string GetTimeString(const std::string &sep = ":") const
    	{
        	return std::string (H < 10 ? "0" : "") + ToString(H) + sep +
               	std::string (M < 10 ? "0" : "") + ToString(M) + sep +
               	std::string (S < 10 ? "0" : "") + ToString(S);
    	}
    	//combine Date and Time string formatting together
    	std::string GetDateTimeString(const std::string &sep = ":") const
    	{
        	return GetDateString() + " " + GetTimeString(sep);
    	}
	};

template <class T>

std::string ToString(const T &e)
{

	std::ostringstream s;
	s << e;
	return s.str();

}

//error log function
void WriteAppLog(const std::string &s)
{

	std::ofstream file("AppLog.txt", std::ios::app); //append to error log file

	file << "[" << Helper::DateTime().GetDateTimeString() << "]" <<
	"\n" << s << std::endl << "\n";

	file.close();

}
}//end bracket for Helper namespace

#endif // HELPER_H
