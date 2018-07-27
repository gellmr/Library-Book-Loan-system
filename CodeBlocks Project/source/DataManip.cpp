/**
\file		DataManip.cpp
\n
\brief		DataManip class implementation
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/



#include <string>
#include "../h/DataManip.h"


using namespace std;




		/**
		Default Constructor
		*/
DataManip::DataManip()
{

}



		/**
		Helper method
		*/
void DataManip::removeLeadingWhiteSpace(string & inStr)
{
	// Remove leading whitespaces.
	size_t pos;
	pos = inStr.find_first_not_of(" \t\f\v\n\r");
	inStr = inStr.substr(pos);    // get the string after that position.
}





		/**
		Helper method
		*/
void DataManip::removeTrailingWhiteSpace(string & inStr)
{
	// Erase trailing whitespaces.
	string whitespaces (" \t\f\v\n\r");
	size_t found;

	found = inStr.find_last_not_of(whitespaces);
	if (found != string::npos)
		inStr.erase(found + 1);
	else
		inStr.clear();            // inStr is all whitespace
}
