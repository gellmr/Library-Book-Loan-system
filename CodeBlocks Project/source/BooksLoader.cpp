/**
\file		BooksLoader.cpp
\n
\brief		BooksLoader class implementation
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
#include "../h/BookType.h"
#include "../h/ReadCsv.h"
#include "../h/BooksLoader.h"


using namespace std;








////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



		/**
		Default Constructor.  Arguments: none
		\n
		*/
BooksLoader::BooksLoader()
{
}






		/**
		Load all books.  Arguments: bool, char*, vector<BookType>
		\n
		@param	debugMode		(bool) 				true if we want to print verbose status messages to the console.
		\n
		@param	inputFileName	(char*) 			The name of the file to load data from.
		\n
		@param	books			(vector<BookType>) 	list of books to load into.
		\n
		@return	(true) 			if successful.
		\n
		*/
bool BooksLoader::LoadLibraryBooks(bool debugMode, const char * inputFileName, vector<BookType> & books)
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
	//    into the BookType objects we are making.

	cout << fixed << showpoint;
	cout << setprecision(2);

	string stringValue;

	unsigned columnCounter = 0;

	string title;
	unsigned numberOfAuthors;
	string * authors;

	string publisher;
	unsigned numberOfCopiesInStock;
	double price;
	long isbn;

	unsigned TITLE_POS = 0;
	unsigned AUTHC_POS = 1;
	unsigned MAXAUTH_POS = 0;
	unsigned PUBLI_POS = 0;
	unsigned STOCC_POS = 0;
	unsigned PRICE_POS = 0;
	unsigned ISBNL_POS = 0;

	// For each row of data
	for(csvVector::iterator csvRow = csvData.begin(); csvRow != csvData.end(); ++csvRow)
	{
		columnCounter   = 0;
		numberOfAuthors = 0;
		authors = new string[4];

		// For each column of data
		for
		(
			std::vector<std::string>::iterator csvColumn = csvRow->begin(); csvColumn != csvRow->end(); ++csvColumn
		)
		{

			//    There are between 6 and 10 columns of data in the row,
			//    depending upon how many authors the book has.


			if(columnCounter == TITLE_POS)
			{
				// BOOK TITLE
				title = * csvColumn;
				DataManip::removeLeadingWhiteSpace(title);
				DataManip::removeTrailingWhiteSpace(title);

			}
			else if(columnCounter == AUTHC_POS)
			{
				// NUMBER OF AUTHORS
				std::istringstream istr(*csvColumn);
				istr >> numberOfAuthors;

				// Get the positions of the remaining data for this row.
				MAXAUTH_POS = AUTHC_POS + numberOfAuthors;
				PUBLI_POS = MAXAUTH_POS + 1;
				STOCC_POS = MAXAUTH_POS + 2;
				PRICE_POS = MAXAUTH_POS + 3;
				ISBNL_POS = MAXAUTH_POS + 4;

			}
			else if ((columnCounter > AUTHC_POS) && (columnCounter <= MAXAUTH_POS) )
			{
				// AUTHOR NAME

				unsigned authIdx = columnCounter - 2;

				string authName = *csvColumn;

				DataManip::removeLeadingWhiteSpace(authName);
				DataManip::removeTrailingWhiteSpace(authName);

				// Show what number of author this is.
				if (debugMode)
				{
					authName.append("(");
					string theIndex;
					std::stringstream ss;
					ss << authIdx;
					theIndex = ss.str();
					authName.append(theIndex);
					authName.append(")");
				}

				authors[authIdx] = authName;


			}
			else if(columnCounter == PUBLI_POS)
			{
				// PUBLISHER
				publisher = *csvColumn;
				DataManip::removeLeadingWhiteSpace(publisher);
				DataManip::removeTrailingWhiteSpace(publisher);


			}
			else if(columnCounter == STOCC_POS)
			{
				// NUMBER OF COPIES IN STOCK
				std::istringstream istr(*csvColumn);
				istr >> numberOfCopiesInStock;


			}
			else if(columnCounter == PRICE_POS)
			{
				// PRICE
				std::istringstream istr(*csvColumn);
				istr >> price;


			}
			else if(columnCounter == ISBNL_POS)
			{
				// ISBN
				std::istringstream istr(*csvColumn);
				istr >> isbn;


			}
			columnCounter++;
		}




		if (debugMode)
		{
			// Show book data

			cout << " Title:     " << title << endl;
			cout << " #Authors:  " << numberOfAuthors << endl;
			cout << " Author[0]: " << authors[0] << endl;
			cout << " Author[1]: " << authors[1] << endl;
			cout << " Author[2]: " << authors[2] << endl;
			cout << " Author[3]: " << authors[3] << endl;
			cout << " Publisher: " << publisher << endl;
			cout << " #Copies:   " << numberOfCopiesInStock << endl;
			cout << " Price:    $" << price << endl;
			cout << " ISBN:      " << isbn << endl;

			cout << endl;
			cout << endl;
			cout << endl;
		}



		// Make a new book.
		BookType b;

		b.setTitle(title);
		b.setNumberOfAuthors(numberOfAuthors);
		b.setAuthorAt(authors[0], 0);
		b.setAuthorAt(authors[1], 1);
		b.setAuthorAt(authors[2], 2);
		b.setAuthorAt(authors[3], 3);
		b.setPublisher(publisher);
		b.setNumberOfCopiesInStock(numberOfCopiesInStock);
		b.setPrice(price);
		b.setIsbn(isbn);

		// Add the book
		books.push_back(b);

		if (debugMode)
		{
			cout << "Push to books" << endl;
		}

		delete [] authors;
		authors = NULL;
	}
	return 1; // success
}









		/**
		Save all books.  Arguments: bool, char*, vector<BookType>
		\n
		@param	debugMode		(bool) 				true if we want to print verbose status messages to the console.
		\n
		@param	outputFileName	(char*) 			The name of the file to save data into.
		\n
		@param	books			(vector<BookType>) 	list of books to save.
		\n
		@return	(true) 			if successful.
		\n
		*/
bool BooksLoader::SaveLibraryBooks(bool debugMode, const char * outputFileName, vector<BookType> & books)
{

	std::fstream file(outputFileName, ios::out);

	if(!file.is_open())
	{
		std::cout << "File not found!\n";
		return 0;
	}


	// Write the data from all the books in the vector to the text file, using CSV format.
	// One book per row.

	vector<BookType>::iterator currentBook;

	for(
		currentBook  = books.begin();

		currentBook != books.end();

		currentBook++)
	{

		// Local variables

		string   volumeTitle;
		string   volumePublisher;
		long     volumeIsbn;
		double   volumePrice;
		unsigned volumeCopies;
		unsigned volumeAuthCount;

		BookType b;

		b = *currentBook;


		// Write this record.

		b.getTitle(volumeTitle);
		file << volumeTitle << ", ";

		b.getNumberOfAuthors(volumeAuthCount);
		file << volumeAuthCount << ", ";

		string authorName;
		for(unsigned aaa = 0; aaa < volumeAuthCount; aaa++)
		{
			b.getAuthorAt(authorName, aaa);
			file << authorName << ", ";
		}

		b.getPublisher(volumePublisher);
		b.getIsbn(volumeIsbn);
		b.getPrice(volumePrice);
		b.getNumberOfCopiesInStock(volumeCopies);

		file <<  volumePublisher << ", ";
		file <<  volumeCopies    << ", ";
		file <<  volumePrice     << ", ";
		file <<  volumeIsbn      << ", ";
		file <<  endl;



		if (debugMode)
		{
			cout      << volumeTitle     << ", ";
			cout      << volumeAuthCount << ", ";

			for(unsigned aaa = 0; aaa < volumeAuthCount; aaa++)
			{
				b.getAuthorAt(authorName, aaa);
				cout      << "("<<aaa<<")" << authorName << ", ";
			}

			cout <<  volumePublisher << ", ";
			cout <<  volumeCopies    << ", ";
			cout <<  volumePrice     << ", ";
			cout <<  volumeIsbn      << ", ";
			cout <<  endl;
			cout <<  endl;
		}


	}

	file.close();

	return 1; // success
}




