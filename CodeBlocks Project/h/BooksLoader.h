/**
\file		BooksLoader.h
\brief		BooksLoader class - definition
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Sunday 15th May 2011.
*/


#if !defined(_BOOKS_LOADER_H)
#define _BOOKS_LOADER_H


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../h/BookType.h"



using namespace std;




		/**
		\class BooksLoader
		\brief Load / Save book data from a CSV file in the local directory.

		To minimise coupling, this class does not use the BST classes which will eventually store our book records.
		Instead, data is inserted to an STL vector.
		*/
class BooksLoader
{


public:


	// Constructors / Destructor / Operator Overrides
	////////////////////////////////////////////////////////////////////

			/**	\brief
			Default Constructor\n*/
	BooksLoader();



	// LOAD / SAVE
	////////////////////////////////////////////////////////////////////

			/**	\brief
			Load a list of books from a text file.\n
			Returns a vector of BookType objects.
			*/
	static bool LoadLibraryBooks(bool debugMode, const char * inputFileName, vector<BookType> & books);

			/**	\brief
			Save a list of books to a text file.\n
			Accepts a vector of BookType objects.
			*/
	static bool SaveLibraryBooks(bool debugMode, const char * outputFileName, vector<BookType> & books);
};



#endif  //_BOOKS_LOADER_H
