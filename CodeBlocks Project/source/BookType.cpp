/**
\file		BookType.cpp
\n
\brief		BookType class implementation
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/


#include "../h/BookType.h"

//#include <iostream> // temporarily
#include <fstream>
#include <string>
#include <sstream>


using namespace std;






		/**
		Reset method.  Arguments: none.
		\n
		Reets the data members of this book to the default settings.
		*/
void BookType::Reset()
{
	//cout << " (BookType) Reset()" << endl;
	clearAuthors(); // sets authors = 0;

	title = "";
	authors = new string [4]; //allocate
	publisher = "";
	isbn = 0;
	price = 0.0;
	numberOfCopiesInStock = 0;
	numberOfAuthors = 0;
}





		/**
		Delete authors and deallocate memory.  Arguments: none.
		\n
		*/
void BookType::clearAuthors()
{
	if (authors != 0)
	{
		//cout << " (BookType) clearAuthors() ... delete [] authors" << endl;
		delete [] authors;
	}
	authors = 0;
}




		/**
		Copy Constructor.  Arguments: BookType
		\n
		@param	otherBook	(BookType) The book that we are copying from.
		\n
		Resets this book to defaults, and then copies data into it.
		*/
BookType::BookType(const BookType & otherBook)
{
	authors = 0;
	//cout << " (BookType) (Copy Constructor) authors = 0" << endl;

	//cout << " otherBook: " << endl << otherBook << endl;

	Reset();
	Copy(otherBook);
}




		/**
		Assignment Operator override..  Arguments: BookType
		\n
		@param	otherBook	(BookType) The book object that we are copying from.
		\n
		@return	BookType	The value of this object (*this)
		\n
		Checks for self-assignment first.
		*/
const BookType & BookType::operator=(const BookType & otherBook)
{
	// Avoid self-assignment
	if (this != &otherBook)
	{
		Copy(otherBook);
	}
	return *this; // The value of the object that was just assigned.
}






		/**
		Greater than comparison operator override..  Arguments: BookType
		\n
		@param	otherBook	(BookType) The book object that we are comparing against.
		\n
		@return	bool		Returns true if this book object is greater than the given book object.
		\n
		Compares by ISBN.
		*/
bool BookType::operator>(const BookType & otherBook) const
{
	long volumeIsbn;
	long volumeIsbnOther;
	getIsbn ( volumeIsbn      );
	getIsbn ( volumeIsbnOther );

	return (volumeIsbn > volumeIsbnOther);
}






		/**
		Less than comparison operator override..  Arguments: BookType
		\n
		@param	otherBook	(BookType) The book object that we are comparing against.
		\n
		@return	bool		Returns true if this book object is less than the given book object.
		\n
		Compares by ISBN.
		*/
bool BookType::operator<(const BookType & otherBook) const
{
	long volumeIsbn;
	long volumeIsbnOther;
	getIsbn ( volumeIsbn      );
	getIsbn ( volumeIsbnOther );

	return (volumeIsbn < volumeIsbnOther);
}





		/**
		Equality comparison operator override..  Arguments: BookType
		\n
		@param	otherBook	(BookType) The book object that we are comparing against.
		\n
		@return	bool		Returns true if the two book objects are equal.
		\n
		Performs member-wise comparison for equality.
		*/
bool BookType::operator==(const BookType & otherBook) const
{
	// Checking against self ?
	// This is an address comparison (i think)  OTHERWISE it will be infinite recursion.  AAA!
	if (this != &otherBook)
	{
		// Get the data from this object.

		// Local variables
		string   volumeTitle;
		string   volumePublisher;
		long     volumeIsbn;
		double   volumePrice;
		unsigned volumeCopies;
		unsigned volumeAuthCount;

		getTitle                 ( volumeTitle     );
		getPublisher             ( volumePublisher );
		getIsbn                  ( volumeIsbn      );
		getPrice                 ( volumePrice     );
		getNumberOfCopiesInStock ( volumeCopies    );
		getNumberOfAuthors       ( volumeAuthCount );


		// Get the data from the object we are comparing to.

		// Local variables
		string   volumeTitleOther;
		string   volumePublisherOther;
		long     volumeIsbnOther;
		double   volumePriceOther;
		unsigned volumeCopiesOther;
		unsigned volumeAuthCountOther;

		otherBook.getTitle                 ( volumeTitleOther     );
		otherBook.getPublisher             ( volumePublisherOther );
		otherBook.getIsbn                  ( volumeIsbnOther      );
		otherBook.getPrice                 ( volumePriceOther     );
		otherBook.getNumberOfCopiesInStock ( volumeCopiesOther    );
		otherBook.getNumberOfAuthors       ( volumeAuthCountOther );


		// Equality comparison happens here.
		////////////////////////////////////
		if	(
			volumeTitle		== volumeTitleOther		&&
			volumePublisher	== volumePublisherOther	&&
			volumeIsbn		== volumeIsbnOther		&&
			volumePrice		== volumePriceOther		&&
			volumeCopies	== volumeCopiesOther	&&
			volumeAuthCount	== volumeAuthCountOther
			)
		{
			// All equal so far. Now check each author.
			// Both have the same number of authors.
			///////////////////////////////////////////
			string auth;
			string authOther;
			for(unsigned a = 0; a < volumeAuthCount; a ++)
			{
				getAuthorAt (auth, a);
				getAuthorAt (authOther, a);
				if(auth != authOther)
				{
					return false;  // Authors do not match exactly.  Inequal.
				}
			}
			return true; // Everything matches exactly. Equal.
		}

		return false;  // Members do not match exactly.  Inequal.
	}
	else
	{
		return true; // this == this.  So they are equal.
	}
}





		/**
		Destructor.  Arguments: none.
		\n
		Deallocates dynamic memory.
		*/
BookType::~BookType()
{
	//cout << " (BookType) Destructor() " << endl;
	clearAuthors(); // deallocates and sets authors = 0;
}






		/**
		Constructor (default).  Arguments: none.
		\n
		Calls Reset() method.
		*/
BookType::BookType()
{
	//cout << " (BookType) Constructor (default) authors = 0" << endl;
	authors = 0;
	Reset();
}







		/**
		Copy method.  Arguments: BookType
		\n
		@param	otherBook	(BookType) The book object that we are copying from.
		\n
		Copies the data members of the given object into this book object.
		*/
void BookType::Copy(const BookType & otherBook)
{
	//cout << " (BookType) Copy() ..." << endl;
	clearAuthors(); // deallocates and sets authors = 0;

	otherBook.getTitle(title);
	otherBook.getPublisher(publisher);
	otherBook.getIsbn(isbn);
	otherBook.getPrice(price);
	otherBook.getNumberOfCopiesInStock(numberOfCopiesInStock);
	otherBook.getNumberOfAuthors(numberOfAuthors);

	authors = new string [4]; //allocate

	string auth;
	for(unsigned a = 0; a < 4; a++)
	{
		otherBook.getAuthorAt(auth, a);
		//cout << "COPY CONSTRUCTING AUTHOR... " << a << " auth value: " << auth << endl;
		setAuthorAt(auth, a);
	}
}








		/**
		Set the book title.  Arguments: string
		\n
		@param	t	(string) The title of the book.
		\n
		*/
void BookType::setTitle                 ( const string   & t )
{
	title = t;
}



		/**
		Set the book publisher.  Arguments: string
		\n
		@param	p	(string) The publisher.
		\n
		*/
void BookType::setPublisher             ( const string   & p )
{
	publisher = p;
}



		/**
		Set the ISBN of the book.  Arguments: long
		\n
		@param	l	(long) The ISBN of the book.
		\n
		*/
void BookType::setIsbn                  ( const long     & l )
{
	isbn = l;
}




		/**
		Set the price of the book.  Arguments: double
		\n
		@param	p	(double) The price (dollars.cents) of this book.
		\n
		*/
void BookType::setPrice                 ( const double   & p )
{
	price = p;
}



		/**
		Set the number of copies of this book that the library owns.  Arguments: unsigned
		\n
		@param	n	(unsigned) The number of copies the library owns.
		\n
		*/
void BookType::setNumberOfCopiesInStock ( const unsigned & n )
{
	numberOfCopiesInStock = n;
}



		/**
		Set the number of authors that this book has.  Arguments: unsigned
		\n
		@param	n	(unsigned) The number of authors.
		\n
		Need to call this before you set any authors. Required for dynamic memory allocation.
		*/
void BookType::setNumberOfAuthors       ( const unsigned & n )
{
	numberOfAuthors = n;
}







		/**
		Get the title of this book.  Arguments: string
		\n
		@param	t	(string) Receives the title of this book.
		\n
		*/
void BookType::getTitle                 ( string   & t ) const
{
	t = title;
}



		/**
		Get the publisher of this book..  Arguments: string
		\n
		@param	p	(string) The publisher of this book.
		\n
		*/
void BookType::getPublisher             ( string   & p ) const
{
	p = publisher;
}



		/**
		Get the ISBN of this book.  Arguments: long
		\n
		@param	l	(long) The ISBN of this book
		\n
		*/
void BookType::getIsbn                  ( long     & l ) const
{
	l = isbn;
}



		/**
		Get the price of this book.  Arguments: double
		\n
		@param	p	(double) The price of this book
		\n
		*/
void BookType::getPrice                 ( double   & p ) const
{
	p = price;
}



		/**
		Get the number of copies of this book that the library owns.  Arguments: unsigned
		\n
		@param	n	(unsigned) The number of copies of this book that the library owns
		\n
		*/
void BookType::getNumberOfCopiesInStock ( unsigned & n ) const
{
	n = numberOfCopiesInStock;
}



		/**
		Get the number of authors that this book has.  Arguments: unsigned
		\n
		@param	n	(unsigned) The number of authors that this book has
		\n
		*/
void BookType::getNumberOfAuthors ( unsigned & n ) const
{
	n = numberOfAuthors;
}







		/**
		Get the search key.  Arguments: none.
		\n
		@return	long	The search key used for searching for this object in special data structures
		\n
		This method is provided so that this class can implement the Searchable interface.
		*/
long BookType::getKey() const
{
	long theKey;
	getIsbn(theKey);
	return theKey;
}













		/**
		Set the author at the given index.  Arguments: string, unsigned
		\n
		@param	a	(string) 	The (full name) of the author. May include spaces.
		\n
		@param	idx	(unsigned) 	The index to set. (3 == maximum)
		\n
		*/
void BookType::setAuthorAt ( const string & a , const unsigned & idx )
{
	//cout << "    setAuthorAt() string: " << a << "  idx: " << idx << endl;

	if (idx < numberOfAuthors)
	{

		string s;
		s = a;
		authors[idx] = s;
		//cout << "SET AUTHOR: " << a << endl;
	}
}





		/**
		Get the author at the given index.  Arguments: string, unsigned
		\n
		@param	theStr	(string) 	The (full name) of the author. May include spaces.
		\n
		@param	idx		(unsigned) 	The index to get. (3 == maximum)
		\n
		*/
void BookType::getAuthorAt ( string & theStr, const unsigned & idx ) const
{
	if (idx < numberOfAuthors)
	{
		theStr = authors[idx];
	}
}





		/**
		Give the data members of this object as a descriptive string.  Arguments: string
		\n
		@param	outstr	(string) The string to receive the data.
		\n
		*/
void BookType::toString(string & outstr) const
{

	string title;
	getTitle(title);

	outstr.append("Title:             ");
	outstr.append(title);
	outstr.append("\n");

	stringstream ss;
	string appStr;

	unsigned authCount;
	getNumberOfAuthors(authCount);

	ss << authCount;
	ss >> appStr;

	outstr.append("Number of Authors: ");
	outstr.append(appStr);
	outstr.append("\n");

	string auth;
	for (unsigned aa = 0; aa < authCount; aa++)
	{
		getAuthorAt(auth, aa);

		ss << aa;
		ss >> appStr;

		outstr.append("Author ");
		outstr.append(appStr);
		outstr.append(":          ");

		ss << auth;
		ss >> appStr;

		outstr.append(appStr);
		outstr.append("\n");
	}

	long isb;
	getIsbn(isb);
	ss << isb;
	ss >> appStr;
	outstr.append("ISBN:              ");
	outstr.append(appStr);
	outstr.append("\n");

	unsigned num;
	getNumberOfCopiesInStock(num);
	outstr.append("Copies in stock:   ");
	ss << num;
	ss >> appStr;
	outstr.append(appStr);
	outstr.append("\n");

	double thePrice;
	getPrice(thePrice);
	outstr.append("Price:             ");
	ss << thePrice;
	ss >> appStr;
	outstr.append(appStr);
	outstr.append("\n");

}




		/**
		Stream insertion operator override.  Arguments: ostream, BookType
		\n
		@param	os	(ostream) 	The output stream
		\n
		@param	b	(BookType) 	the book object to insert into the stream.
		\n
		@return	ostream 		The output stream again.
		\n
		Writes the data members of this book to the stream, in a nice formatted block of text.
		*/
ostream & operator<<(ostream & os, const BookType & b)
{
	// This is basically a "to string" routine.

	string title;
	b.getTitle(title);
	os << "Title:             " << title << endl;

	unsigned authCount;
	b.getNumberOfAuthors(authCount);

	os << "Number of Authors: " << authCount << endl;

	string auth;
	for (unsigned aa = 0; aa < authCount; aa++)
	{
		b.getAuthorAt(auth, aa);
		os << "Author " << aa << ":          " << auth << endl;
	}

	long isb;
	b.getIsbn(isb);
	os << "ISBN:              " << isb << endl;

	unsigned num;
	b.getNumberOfCopiesInStock(num);
	os << "Copies in stock:   " << num << endl;

	double thePrice;
	b.getPrice(thePrice);
	os << "Price:             " << thePrice << endl;

	return os;
}

