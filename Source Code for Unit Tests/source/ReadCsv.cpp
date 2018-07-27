/**
\file		ReadCsv.cpp
\n
\brief		ReadCsv class implementation
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/



#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "../h/ReadCsv.h"


using namespace std;




		/**
		Default Constructor.  Arguments: none.
		\n
		*/
ReadCsv::ReadCsv()
{
}



		/**
		Read a text file (containing CSV data).  Arguments: istream, vector<vector<string>>
		\n
		@param	input	(istream) The input stream (file) that we are reading from. Must be already open.
		\n
		@param	output	(vector<vector<string>>) A 2D vector of strings to be populated with csv data.
		\n
		Accepts an open input file stream
		*/
void ReadCsv::Read(std::istream & input, std::vector< std::vector<std::string> > & output)
{
	std::string csvLine;

	// read every line from the stream
	while( std::getline(input, csvLine) )
	{
		std::istringstream csvStream(csvLine);
		std::vector<std::string> csvColumn;
		std::string csvElement;

		// read every element from the line that is seperated by commas
		// and put it into the vector of strings
		while( std::getline(csvStream, csvElement, ',') )
		{
			csvColumn.push_back(csvElement);
		}
		output.push_back(csvColumn);
	}
}
