/**
\file		BookLoan.cpp
\n
\brief		BookLoan class implementation
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/




#include "../h/BookLoan.h"

#include <fstream>
#include <string>


using namespace std;




		/**
		Default Constructor.  Arguments: none \n

		Calls Reset() method.
		*/
BookLoan::BookLoan()
{
	Reset();
}




		/**
		Destructor.  Arguments: none \n
		*/
BookLoan::~BookLoan()
{
}






		/**
		Copy Constructor.  Arguments: BookLoan
		\n
		@param	otherLoan	(BookLoan) The loan object we are copying.
		\n
		Calls Reset and then copies the given loan.
		*/
BookLoan::BookLoan(const BookLoan & otherLoan)
{
	Reset();
	Copy(otherLoan);
}





		/**
		Assignment op override.  Arguments: BookLoan
		\n
		@param	otherLoan	(BookLoan) The loan object we are copying.
		\n
		@return	(BookLoan)	 The value of the current object (*this)
		\n
		Copies the given loan object.
		*/
const BookLoan & BookLoan::operator=(const BookLoan & otherLoan)
{
	// Avoid self-assignment
	if (this != &otherLoan)
	{
		Copy(otherLoan);
	}
	return *this; // The value of the object that was just assigned.
}








		/**
		Equality comparison operator override..  Arguments: BookLoan
		\n
		@param	otherLoan	(BookLoan) The loan object we are comparing to.
		\n
		@return	bool If the loan objects match
		\n
		Performs member-wise comparison.
		*/
bool BookLoan::operator==(const BookLoan & otherLoan) const
{
	// Checking against self ?
	// This is an address comparison (i think)  OTHERWISE it will be infinite recursion.  AAA!
	if (this != &otherLoan)
	{

		// This BookLoan
		long myBookISBN;
		long myPatronId;
		Date myBorrowedOn;
		Date myDueOn;

		// Get data members.
		getBookISBN    ( myBookISBN);
		getPatronId    ( myPatronId);
		getBorrowedDate( myBorrowedOn);
		getDueDate     ( myDueOn);



		// Other BookLoan
		long otherBookISBN;
		long otherPatronId;
		Date otherBorrowedOn;
		Date otherDueOn;

		// Get data members.
		otherLoan.getBookISBN    ( otherBookISBN);
		otherLoan.getPatronId    ( otherPatronId);
		otherLoan.getBorrowedDate( otherBorrowedOn);
		otherLoan.getDueDate     ( otherDueOn);

		// Equality comparison happens here.
		////////////////////////////////////
		if	(
				myBookISBN		== otherBookISBN	&&
				myPatronId		== otherPatronId	&&
				myBorrowedOn	== otherBorrowedOn	&&
				myDueOn			== otherDueOn
			)
		{
			return true;	// Everything matches exactly. Equal.
		}
		return false;		// Members do not match exactly.  Inequal.
	}
	else
	{
		return true; // this == this.  So they are equal.
	}
}







		/**
		Greater than comparison operator override, uses ISBN..  Arguments: BookLoan
		\n
		@param	otherLoan	(BookLoan) The loan object that we are comparing to.
		\n
		@return	bool		True if the given loan is less than this loan object.
		\n
		Compares the loans by their ISBN.
		*/
bool BookLoan::operator>(const BookLoan & otherLoan) const
{
	long myISBN;
	long otherISBN;

	// Compare by ISBN
	getBookISBN(myISBN);
	otherLoan.getBookISBN(otherISBN);

	if (myISBN > otherISBN)
	{
		return true;
	}
	return false;
}






		/**
		Less than comparison operator override, uses ISBN.  Arguments: BookLoan
		\n
		@param	otherLoan	(BookLoan) The loan object we are comparing to.
		\n
		@return	bool		True if the given loan is greater than this loan object.
		\n
		Compares the loans by their ISBN.
		*/
bool BookLoan::operator<(const BookLoan & otherLoan) const
{
	long myISBN;
	long otherISBN;

	// Compare by ISBN
	getBookISBN(myISBN);
	otherLoan.getBookISBN(otherISBN);

	if (myISBN < otherISBN)
	{
		return true;
	}
	return false;
}






// Mutators



		/**
		Provide the ISBN for the book object that this loan concerns.  Arguments: long
		\n
		@param	bIsbn	(long) The ISBN value we are setting with.
		\n
		*/
void BookLoan::setBookISBN    (const long & bIsbn)
{
	bookISBN = bIsbn;
}




		/**
		Provide the User ID of the patron who this loan concerns.  Arguments: long
		\n
		@param	l	(long) the ID of the patron.
		\n
		*/
void BookLoan::setPatronId    (const long & l)
{
	patronId = l;
}


		/**
		Set the date of borrowing.  Arguments: Date
		\n
		@param	d	(Date) The date the book was borrowed.
		\n
		*/
void BookLoan::setBorrowedDate(const Date & d)
{
	borrowedOn = d;
}


		/**
		Set the date that the book is due back.  Arguments: Date
		\n
		@param	d	(Date) The date the book is due.
		\n
		*/
void BookLoan::setDueDate     (const Date & d)
{
	dueOn = d;
}



// Accessors


		/**
		Get the ISBN of the book that is on loan.  Arguments: long
		\n
		@param	bIsbn	(long) The ISBN
		\n
		*/
void BookLoan::getBookISBN    ( long & bIsbn) const
{
	bIsbn = bookISBN;
}


		/**
		Get the ID of the patron that borrowed the book.  Arguments: long
		\n
		@param	l	(long) the User ID of the patron
		\n
		*/
void BookLoan::getPatronId    ( long & l) const
{
	l = patronId;
}


		/**
		Get the date that the book was borrowed.  Arguments: Date
		\n
		@param	d	(Date) The date that the book was borrowed.
		\n
		*/
void BookLoan::getBorrowedDate( Date & d) const
{
	d = borrowedOn;
}


		/**
		Get the date that the book is due.  Arguments: Date
		\n
		@param	d	(Date) The date that the book is due.
		\n
		*/
void BookLoan::getDueDate     ( Date & d) const
{
	d = dueOn;
}







		/**
		Get the search key for this searchable object.  Arguments: none.
		\n
		@return	(long) The key used to search for this object in a Binary Search Tree or other special data structure.
		\n
		This method is provided so that this class may implement the Searchable interface.
		*/
long BookLoan::getKey() const
{
	long theKey;
	getBookISBN(theKey);
	return theKey;
}




		/**
		Reset method. Reset this loan object to default parameters.  Arguments: none.
		\n
		Resets all data members.
		*/
void BookLoan::Reset()
{
	bookISBN	= 0;	// Not a legal ISBN
	patronId    = 0;	// This is the user ID of a patron who cannot use the system.
	borrowedOn.Reset();
	dueOn.Reset();
}




		/**
		Copy method.  Arguments: BookLoan
		\n
		@param	otherLoan	(BookLoan) The loan object we are copying from.
		\n
		Performs a member-wise copy.
		*/
void BookLoan::Copy(const BookLoan & otherLoan)
{
	// Data to get
	long otherIsbn;
	long otherPatronId;
	Date otherBorrowedDate;
	Date otherDueDate;

	// Get the data from the other object.
	otherLoan.getBookISBN    ( otherIsbn          );
	otherLoan.getPatronId    ( otherPatronId     );
	otherLoan.getBorrowedDate( otherBorrowedDate );
	otherLoan.getDueDate     ( otherDueDate      );

	// Set my data
	setBookISBN    	(otherIsbn			);
	setPatronId    	(otherPatronId		);
	setBorrowedDate	(otherBorrowedDate	);
	setDueDate     	(otherDueDate		);
}



