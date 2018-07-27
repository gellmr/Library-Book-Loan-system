/**
\file		LoansLoader.cpp
\n
\brief		LoansLoader class implementation
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
#include "../h/ReadCsv.h"
#include "../h/LoansLoader.h"
#include "../h/BookLoan.h"


using namespace std;








////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



		/**
		Default Constructor. Arguments: none.
		\n
		*/
LoansLoader::LoansLoader()
{
}




		/**
		Load all loans.  Arguments: bool, char*, vector<BookLoan>
		\n
		@param	debugMode		(bool) 				true if we want to print verbose status messages to the console.
		\n
		@param	inputFileName	(char*) 			The name of the file to load data from.
		\n
		@param	loansList		(vector<BookLoan>) 	list of loans to load.
		\n
		@return	(true) 			if successful.
		\n
		*/
bool LoansLoader::LoadLoans(bool debugMode, const char * inputFileName, vector<BookLoan> & loansList)
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
	//    into the BookLoan objects we are making.

	cout << fixed << showpoint;
	cout << setprecision(2);

	string stringValue;

	unsigned columnCounter = 0;

	long loadedIsbn;
	long patronID;
	string dateBorrowed;
	string dateDue;

	//  ROW FORMAT:
	//  ISBN, PatronId, BorrowDate(DD MM YYYY), DueDate(DD MM YYYY)
	//  111,  1357,    14 03 2011,               30 03 2011,

	unsigned ISBN_POS			= 0;
	unsigned PATRON_ID_POS		= 1;
	unsigned BORROW_DATE_POS	= 2;
	unsigned DUE_DATE_POS		= 3;


	unsigned someBorrDD;
	unsigned someBorrMM;
	unsigned someBorrYYYY;

	unsigned someDueDD;
	unsigned someDueMM;
	unsigned someDueYYYY;

	stringstream ss (stringstream::in | stringstream::out);

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

			if(columnCounter == ISBN_POS)
			{
				// The ISBN of the book that was borrowed.
				std::istringstream istr(*csvColumn);
				istr >> loadedIsbn;

			}
			if(columnCounter == PATRON_ID_POS)
			{
				// The ID of the Patron who borrowed this book.
				std::istringstream istr(*csvColumn);
				istr >> patronID;

			}
			else if(columnCounter == BORROW_DATE_POS)
			{
				// The date that the book was borrowed.  DD MM YYYY
				dateBorrowed = * csvColumn;

				ss.clear();
				ss.str("");

				ss << dateBorrowed;

				ss >> someBorrDD;
				ss >> someBorrMM;
				ss >> someBorrYYYY;

			}
			if(columnCounter == DUE_DATE_POS)
			{
				// The date that the book is due.  DD MM YYYY
				dateDue = * csvColumn;

				ss.clear();
				ss.str("");

				ss << dateDue;

				ss >> someDueDD;
				ss >> someDueMM;
				ss >> someDueYYYY;

			}
			columnCounter++;
		}


		// Probably should check if the ISBN exists in the BookType bst.
		// I will assume that it does exist.



		// Make a book loan object
		BookLoan bLoan;

		Date dBorrow;
		dBorrow.SetDayOfMonth(		someBorrDD		);
		dBorrow.SetMonth(			someBorrMM		);
		dBorrow.SetYear(			someBorrYYYY	);

		Date dDue;
		dDue.SetDayOfMonth(			someDueDD	);
		dDue.SetMonth(				someDueMM	);
		dDue.SetYear(				someDueYYYY	);

		bLoan.setBookISBN(			loadedIsbn); // !!!!!!!!
		bLoan.setPatronId(			patronID);
		bLoan.setBorrowedDate(		dBorrow);
		bLoan.setDueDate(			dDue);

		loansList.push_back(bLoan);





		if (debugMode)
		{
			// Show loan data

			cout << "isbn: "			<< loadedIsbn	<< endl;
			cout << "patronID: "		<< patronID		<< endl;
			cout << "dateBorrowed: "	<< dateBorrowed	<< endl;
			cout << "dateDue: "			<< dateDue		<< endl;

			cout << endl;
			cout << endl;
			cout << endl;
		}

	}
	return 1; // success
}





		/**
		Save all loans.  Arguments: bool, char*, vector<BookLoan>
		\n
		@param	debugMode		(bool) 				true if we want to print verbose status messages to the console.
		\n
		@param	outputFileName	(char*) 			The name of the file to receive data.
		\n
		@param	loansList		(vector<BookLoan>) 	list of loans to save.
		\n
		@return	(true) 		if successful.
		\n
		*/
bool LoansLoader::SaveLoans(bool debugMode, const char * outputFileName, vector<BookLoan> & loansList)
{

	std::fstream file(outputFileName, ios::out);

	if(!file.is_open())
	{
		std::cout << "File not found!\n";
		return 0;
	}


	// Write the data from all the BookLoan objects in the vector to the text file, using CSV format.
	// One member per row.

	vector<BookLoan>::iterator currentLoan;

	for(
		currentLoan  = loansList.begin();

		currentLoan != loansList.end();

		currentLoan++)
	{

		// Local variables

		long loadedIsbn;
		long patronID;
		Date dateBorrowed;
		Date dateDue;

		unsigned someBorrDD;
		unsigned someBorrMM;
		unsigned someBorrYYYY;

		unsigned someDueDD;
		unsigned someDueMM;
		unsigned someDueYYYY;


		BookLoan bookLoan;

		bookLoan = *currentLoan; // Get the next loan to write with

		// Example row from allLoans.txt
		// 111, 1357, 28 8 1111, 28 8 1112,

		bookLoan.getBookISBN    	(	loadedIsbn		);
		bookLoan.getPatronId    	(	patronID		);
		bookLoan.getBorrowedDate	(	dateBorrowed	);
		bookLoan.getDueDate    	 	(	dateDue			);

		dateBorrowed.GetDayOfMonth	(	someBorrDD		);
		dateBorrowed.GetMonth		(	someBorrMM		);
		dateBorrowed.GetYear		(	someBorrYYYY	);

		dateDue.GetDayOfMonth		(	someDueDD		);
		dateDue.GetMonth			(	someDueMM		);
		dateDue.GetYear				(	someDueYYYY		);




		// Write this record.

		//  ROW FORMAT:
		//  ISBN, PatronId, BorrowDate(DD MM YYYY), DueDate(DD MM YYYY)
		//  111,  1357,    14 03 2011,               30 03 2011,

		file << loadedIsbn			<< ", ";
		file << patronID			<< ", ";

		file << someBorrDD			<< " ";
		file << someBorrMM			<< " ";
		file << someBorrYYYY		<< ", ";

		file << someDueDD			<< " ";
		file << someDueMM			<< " ";
		file << someDueYYYY			<< ", ";

		file << endl;


		if (debugMode)
		{
			cout << loadedIsbn		<< ", ";
			cout << patronID		<< ", ";

			cout << someBorrDD			<< " ";
			cout << someBorrMM			<< " ";
			cout << someBorrYYYY		<< ", ";

			cout << someDueDD			<< " ";
			cout << someDueMM			<< " ";
			cout << someDueYYYY			<< ", ";

			cout << endl;
		}
	}

	file.close();

	return 1; // success
}




