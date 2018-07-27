/**
\file		LoansLoader.h
\brief		LoansLoader class definition.
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/


#if !defined(_LOANS_LOADER_H)
#define _LOANS_LOADER_H


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../h/BookLoan.h"



using namespace std;




		/**
		\class LoansLoader
		\brief Load / Save loan data from a CSV file in the local directory.
		*/
class LoansLoader
{


public:


	// Constructors / Destructor / Operator Overrides
	////////////////////////////////////////////////////////////////////

			/**	\brief
			Default Constructor\n*/
	LoansLoader();



	// LOAD / SAVE
	////////////////////////////////////////////////////////////////////



			/**	\brief
			Load a vector of loans from a text file.\n
			*/
	static bool LoadLoans(bool debugMode, const char * inputFileName, vector<BookLoan> & loansList);



			/**	\brief
			Save a vector of loans to a text file.\n
			*/
	static bool SaveLoans(bool debugMode, const char * outputFileName, vector<BookLoan> & loansList);

};



#endif  //_LOANS_LOADER_H
