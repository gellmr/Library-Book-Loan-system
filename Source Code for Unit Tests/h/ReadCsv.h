/**
\file		ReadCsv.h
\brief		ReadCsv class definition, reads a file of csv data into a 2D vector of strings.
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/


#if !defined(_READ_CSV_H)
#define _READ_CSV_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;



		/**
		\class ReadCsv.
		\brief Read a file of csv data into a 2D vector of strings.
		*/
class ReadCsv
{

public:

			/**	\brief
			Default Constructor. \n*/
	ReadCsv();


			/**	\brief
			Read a file of csv data into a 2D vector of strings. \n*/
	void Read(std::istream &input, std::vector< std::vector<std::string> > & output);

};

#endif
