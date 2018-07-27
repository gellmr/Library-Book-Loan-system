/**
\file		BookLoan.h
\brief		BookLoan class definition.
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/


#if !defined(_BOOKLOAN_H)
#define _BOOKLOAN_H

#include "../h/Searchable.h"
#include "../h/BookType.h"
#include "../h/Date.h"

#include <string>


using namespace std;



		/**
		\class BookLoan.
		\brief Stores information about a book on loan to a library patron

		Implements Searchable
		*/
class BookLoan : public Searchable
{

public:


			/**	\brief
			Default Constructor. \n*/
	BookLoan();


			/**	\brief
			Destructor. \n*/
	~BookLoan();



			/**	\brief
			Copy constructor. \n*/
	BookLoan(const BookLoan & b);



			/**	\brief
			Assignment op override. \n*/
	const BookLoan& operator=(const BookLoan & otherLoan);



			/**	\brief
			Equality Comparison operator override. \n*/
	bool operator==(const BookLoan & otherLoan) const;



			/**	\brief
			Greater than comparison operator override, uses ISBN. \n*/
	bool operator>(const BookLoan & otherLoan) const;


			/**	\brief
			Less than comparison operator override, uses ISBN. \n*/
	bool operator<(const BookLoan & otherLoan) const;







	// Mutators

			/**	\brief
			Provide the ISBN of the book that is loaned. \n*/
	void setBookISBN    (const long & bIsbn);


			/**	\brief
			Provide the ID of the patron who borrowed the book. \n*/
	void setPatronId    (const long & l);


			/**	\brief
			Set date the book was borrowed. \n*/
	void setBorrowedDate(const Date & d);


			/**	\brief
			Set the date the book is due back. \n*/
	void setDueDate     (const Date & d);






	// Accessors

			/**	\brief
			Get the ISBN of the book that is loaned. \n*/
	void getBookISBN    ( long & bIsbn) const;


			/**	\brief
			Get the ID of the patron who borrowed the book. \n*/
	void getPatronId    ( long & l) const;


			/**	\brief
			Get date the book was borrowed. \n*/
	void getBorrowedDate( Date & d) const;


			/**	\brief
			Get the date the book is due back. \n*/
	void getDueDate     ( Date & d) const;




			/**	\brief
			Get the seach key for this object. \n*/
	long getKey() const;




private:



			/**	\brief
			Reset method. \n*/
	void Reset();


			/**	\brief
			Copy method. \n*/
	void Copy(const BookLoan & b);




	// Private data members


			/**	\brief
			The ISBN of the book that is on loan. \n*/
	long bookISBN;

			/**	\brief
			The user ID of the patron who borrowed the book. \n*/
	long patronId;

			/**	\brief
			The date that the book was borrowed (or most recently renewed). \n*/
	Date borrowedOn;

			/**	\brief
			The date that the book is due. \n*/
	Date dueOn;

};

#endif
