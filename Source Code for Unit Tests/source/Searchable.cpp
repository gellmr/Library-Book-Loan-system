/**
\file		Searchable.cpp
\n
\brief		Searchable class implementation
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/


#include <string>
#include "../h/Searchable.h"


using namespace std;





		/**
		Default Constructor.  Arguments: none.
		\n
		*/
Searchable::Searchable()
{
}



		/**
		Destructor.  Arguments: none.
		*/
Searchable::~Searchable()
{

}




		/**
		Copy constructor.  Arguments: Searchable
		\n
		@param	s	(Searchable) Object we are copying from.
		\n
		*/
Searchable::Searchable(const Searchable & s)
{
}



		/**
		Assignment operator.  Arguments: Searchable
		\n
		@param	s	(Searchable) 	Object we are copying from.
		\n
		@return	(Searchable)		The value of the current object (*this)
		\n
		Checks to avoid self-assignment.
		*/
const Searchable& Searchable::operator=(const Searchable & s)
{
	// Avoid self-assignment
	if (this != &s)
	{
	}
	return *this; // The value of the object that was just assigned.
}
