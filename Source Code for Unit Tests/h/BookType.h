/**
\file		BookType.h
\brief		BookType class definition.
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/


#if !defined(_BOOKTYPE_H)
#define _BOOKTYPE_H

#include <string>

#include "../h/Searchable.h"

using namespace std;



		/**
		\class BookType.
		\brief Stores information about a book in the library system.

		Implements Searchable
		*/
class BookType : public Searchable
{



			/**	\brief
			Stream insertion operator override. \n*/
	friend ostream & operator<<(ostream & os, const BookType & b);


public:

			/**	\brief
			Copy constructor. \n*/
	BookType(const BookType & b);


			/**	\brief
			Assignment operator override. \n*/
	const BookType& operator=(const BookType & otherBook);


			/**	\brief
			Equality comparison operator override. \n*/
	bool operator==(const BookType & otherBook) const;


			/**	\brief
			Greater than comparison operator override. \n*/
	bool operator>(const BookType & otherBook) const;


			/**	\brief
			Less than comparison operator override. \n*/
	bool operator<(const BookType & otherBook) const;


			/**	\brief
			Destructor. \n*/
	~BookType();


			/**	\brief
			Constructor (default). \n*/
	BookType();




			/**	\brief
			Set the title of the book. \n*/
	void setTitle                 ( const string   & t );


			/**	\brief
			Set the publisher of the book. \n*/
	void setPublisher             ( const string   & p );


			/**	\brief
			Set the ISBN of the book. \n*/
	void setIsbn                  ( const long     & l );


			/**	\brief
			Set the price of the book. \n*/
	void setPrice                 ( const double   & p );


			/**	\brief
			Set the number of copies of the book that are owned by the library. \n*/
	void setNumberOfCopiesInStock ( const unsigned & n );


			/**	\brief
			Set the number of authors of the book. \n*/
	void setNumberOfAuthors       ( const unsigned & n );


			/**	\brief
			Get the title of the book. \n*/
	void getTitle                 ( string   & t ) const;


			/**	\brief
			Get the publisher of the book. \n*/
	void getPublisher             ( string   & p ) const;


			/**	\brief
			Get the ISBN of the book. \n*/
	void getIsbn                  ( long     & l ) const;


			/**	\brief
			Get the price of the book. \n*/
	void getPrice                 ( double   & p ) const;


			/**	\brief
			Get the number of copies of the book that are owned by the library. \n*/
	void getNumberOfCopiesInStock ( unsigned & n ) const;


			/**	\brief
			Get the number of authors of the book. \n*/
	void getNumberOfAuthors       ( unsigned & n ) const;



			/**	\brief
			Set the author at the given index. \n*/
	void setAuthorAt ( const string & a , const unsigned & idx );


			/**	\brief
			Get the author at the given index. \n*/
	void getAuthorAt (       string & a , const unsigned & idx ) const;



			/**	\brief
			Produce a string from this book's data members. \n*/
	void toString(string & ss) const;



			/**	\brief
			Get the search key of this searchable object. \n*/
	long getKey() const;

private:


			/**	\brief
			Reset this book to its default data member settings. \n*/
	void Reset();


			/**	\brief
			Deallocates and sets authors = 0  (NULL). \n*/
	void clearAuthors();



			/**	\brief
			Copy method. \n*/
	void Copy(const BookType & b);



			/**	\brief
			The title of the book. \n*/
	string title;


			/**	\brief
			Points to the first item in a dynamically allocated array of strings, containing the (full) name(s) of the author(s). \n*/
	string * authors;


			/**	\brief
			The publisher of the book. \n*/
	string publisher;


			/**	\brief
			The ISBN of the book. \n*/
	long isbn;


			/**	\brief
			The price of the book. \n*/
	double price;


			/**	\brief
			The number of copies of the book that are owned by the library. \n*/
	unsigned numberOfCopiesInStock;


			/**	\brief
			The number of authors of this book. \n*/
	unsigned numberOfAuthors;


};

#endif
