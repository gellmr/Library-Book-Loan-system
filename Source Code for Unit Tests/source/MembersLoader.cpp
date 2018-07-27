/**
\file		MembersLoader.cpp
\n
\brief		MembersLoader class implementation
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <iomanip>

#include <string>
#include <sstream>

#include <vector>

#include <fstream>

#include <algorithm>

#include "../h/DataManip.h"
#include "../h/MemberType.h"
#include "../h/ReadCsv.h"
#include "../h/MembersLoader.h"


using namespace std;








////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



		/**
		Default Constructor. Arguments: none
		\n
		*/
MembersLoader::MembersLoader()
{
}








		/**
		Load all users.  Arguments: bool, char*, vector<MemberType>
		\n
		@param	debugMode		(bool) 					true if we want to print verbose status messages to the console.
		\n
		@param	inputFileName	(char*) 				The name of the file to load data from.
		\n
		@param	allUsers		(vector<MemberType>) 	list of users to load into.
		\n
		@return	(true) 			if successful.
		\n
		*/
bool MembersLoader::LoadUsers(bool debugMode, const char * inputFileName, vector<MemberType> & allUsers)
{

	std::fstream file(inputFileName, ios::in);

	if(!file.is_open())
	{
		std::cout << "File not found!\n";
		return 0;
	}

	// vector of vectors of strings
	typedef std::vector< std::vector<std::string> > csvVector;

	csvVector csvData; // VVS

	// Populate the VVS
	ReadCsv reader;
	reader.Read(file, csvData);
	file.close();



	//    Now read through the VVS and extract data
	//    into the MemberType objects we are making.

	cout << fixed << showpoint;
	cout << setprecision(2);

	string stringValue;

	unsigned columnCounter = 0;

	string firstName;
	string lastName;
	long userId;
	string authorisationLevel;

	unsigned FIRSTNAME_POS = 0;
	unsigned LAST_NAME_POS = 1;
	unsigned USER_ID_POS   = 2;
	unsigned AUTHORITY_POS = 3;


	// For each row of data
	for(csvVector::iterator csvRow = csvData.begin(); csvRow != csvData.end(); ++csvRow)
	{
		columnCounter   = 0;


		// For each column of data
		for
		(
			std::vector<std::string>::iterator csvColumn = csvRow->begin();

			csvColumn != csvRow->end();

			++csvColumn
		)
		{

			//    There are 4 columns of data per row.

			if(columnCounter == FIRSTNAME_POS)
			{
				// First name
				firstName = * csvColumn;
				DataManip::removeLeadingWhiteSpace(firstName);
				DataManip::removeTrailingWhiteSpace(firstName);

			}
			if(columnCounter == LAST_NAME_POS)
			{
				// Last name
				lastName = * csvColumn;
				DataManip::removeLeadingWhiteSpace(lastName);
				DataManip::removeTrailingWhiteSpace(lastName);

			}
			else if(columnCounter == USER_ID_POS)
			{
				// Member ID
				std::istringstream istr(*csvColumn);
				istr >> userId;

			}
			if(columnCounter == AUTHORITY_POS)
			{
				// Staff / Patron
				authorisationLevel = * csvColumn;
				DataManip::removeLeadingWhiteSpace(authorisationLevel);
				DataManip::removeTrailingWhiteSpace(authorisationLevel);

			}
			columnCounter++;
		}


		// Add the member
		MemberType m;
		m.setFirstName(firstName);
		m.setLastName(lastName);
		m.setUserId(userId);
		m.setAuthority(authorisationLevel);
		allUsers.push_back(m);


		if (debugMode)
		{
			// Show user data

			cout << " First Name:          " << firstName          << endl;
			cout << " Last Name:           " << lastName           << endl;
			cout << " User Id:             " << userId             << endl;
			cout << " Authorisation Level: " << authorisationLevel << endl;

			cout << endl;
			cout << endl;
			cout << endl;
		}

	}
	return 1; // success
}










		/**
		Save all users.  Arguments: bool, char*, vector<MemberType>
		\n
		@param	debugMode		(bool) 					true if we want to print verbose status messages to the console.
		\n
		@param	outputFileName	(char*) 				The name of the file to save data into.
		\n
		@param	membs			(vector<MemberType>) 	list of users to save.
		\n
		@return	(true) 			if successful.
		\n
		*/
bool MembersLoader::SaveUsers(bool debugMode, const char * outputFileName, vector<MemberType> & membs)
{

	std::fstream file(outputFileName, ios::out);

	if(!file.is_open())
	{
		std::cout << "File not found!\n";
		return 0;
	}


	// Write the data from all the MemberType objects in the vector to the text file, using CSV format.
	// One member per row.

	vector<MemberType>::iterator currentMemb;

	for(
		currentMemb  = membs.begin();

		currentMemb != membs.end();

		currentMemb++)
	{

		// Local variables

		string   fname;
		string   lname;
		long     uid;
		string	 authority;

		MemberType m;

		m = *currentMemb; // Get the next member to write with


		// Write this record.

		m.getFirstName(fname);
		m.getLastName(lname);
		m.getUserId(uid);
		m.getAuthority(authority);

		file << fname		<< ", ";
		file << lname		<< ", ";
		file << uid			<< ", ";
		file << authority	<< ", ";
		file << endl;


		if (debugMode)
		{
			cout <<  fname			<< ", ";
			cout <<  lname			<< ", ";
			cout <<  uid			<< ", ";
			cout <<  authority		<< ", ";

			cout << endl;
			cout << endl;
		}
	}

	file.close();

	return true;
}



