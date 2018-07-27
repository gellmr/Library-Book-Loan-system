/**
\file		Searchable.h
\brief		Searchable class definition.
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/

#if !defined(_SEARCHABLE_H)
#define _SEARCHABLE_H


using namespace std;



		/**
		\class Searchable.
		\brief This is an interface to provide a (long) variable to use as a search key.
		*/
class Searchable
{

public:



			/**	\brief
			Default Constructor. \n*/
	Searchable();




			/**	\brief
			Copy Constructor. \n*/
	Searchable(const Searchable & s);




			/**	\brief
			Assignment Operator override. \n*/
	const Searchable& operator=(const Searchable & s);




			/**	\brief
			Virtual Destructor. \n*/
	virtual ~Searchable();




			/**	\brief
			Set the key of this searchable object. \n*/
	virtual long getKey() const = 0;

};

#endif
