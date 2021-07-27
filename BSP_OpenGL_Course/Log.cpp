#include"Log.h"
#include <iostream>

void LogMessage(const char* strMessage)
{
	using namespace std;
	cout << strMessage << endl;
}

void LogMessage(std::string strMessage)
{
	std::cout << strMessage << std::endl;
}