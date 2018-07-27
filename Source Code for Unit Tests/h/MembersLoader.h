/**
\file		MembersLoader.h
\brief		MembersLoader class definition.
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/


#if !defined(_MEMBERS_LOADER_H)
#define _MEMBERS_LOADER_H


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../h/MemberType.h"



using namespace std;




		/**
		\class MembersLoader
		\brief Load / Save user data from a CSV file in the local directory.
		*/
class MembersLoader
{


public:


	// Constructors / Destructor / Operator Overrides
	////////////////////////////////////////////////////////////////////



			/**	\brief
			Default Constructor\n*/
	MembersLoader();





	// LOAD / SAVE
	////////////////////////////////////////////////////////////////////



			/**	\brief
			Load a list of users from a text file.\n
			Returns a vector of MemberType objects.
			*/
	static bool LoadUsers(bool debugMode, const char * inputFileName, vector<MemberType> & users);




			/**	\brief
			Save a list of users to a text file.\n
			Accepts a vector of MemberType objects.
			*/
	static bool SaveUsers(bool debugMode, const char * outputFileName, vector<MemberType> & users);
};



#endif  //_MEMBERS_LOADER_H
