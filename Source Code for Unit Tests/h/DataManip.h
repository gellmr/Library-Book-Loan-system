/**
\file		DataManip.h
\brief		DataManip class definition, contains some static helper methods for string manipulation.
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/



#if !defined(_DATA_MANIP_H)
#define _DATA_MANIP_H

#include <string>

using namespace std;



		/**
		\class DataManip.
		\brief Has some static helper methods for removing white space from strings
		*/
class DataManip
{

public:

			/**	\brief
			Default Constructor. \n*/
	DataManip();


			/**	\brief
			Remove leading white space from the given string. \n*/
	static void removeLeadingWhiteSpace(string & inStr);


			/**	\brief
			Remove trailing white space from the given string. \n*/
	static void removeTrailingWhiteSpace(string & inStr);

};

#endif
