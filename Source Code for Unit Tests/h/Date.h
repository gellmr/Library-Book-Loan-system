/**
\file		Date.h
\brief		Date class - definition\n\n
Author:  	Michael Gell  (Student Number: 30276096)\n
Modified: 	7th April 2011.
*/


#if !defined(_DATE_H)
#define _DATE_H

#include <string>

using namespace std;



		/**
		\class Date
		\brief Stores dd mm yyyy (all unsigned int values)

		Stores the date, eg: 31 December 2011\n
		Valid ranges are enforced by mutator methods, eg: November has 30 days.
		*/
class Date
{


public:


	// Constructors / Destructor / Operator Overrides
	////////////////////////////////////////////////////////////////////

			/**	\brief
			Default Constructor\n*/
	Date();


			/**	\brief
			Destructor\n*/
	~Date();


			/** \brief
			Reset (empty) this object\n*/
	void Reset();



			/**	\brief
			Copy Constructor\n*/
	Date(const Date& d);



			/**	\brief
			Override for the assignment operator\n*/
	const Date& operator=(const Date& rightDate);



			/**	\brief
			Override for the equality comparison operator\n*/
	bool operator==(const Date& rightDate) const;




	// Mutator Methods
	////////////////////////////////

			/** \brief
			Set the day of the month (1 - 31)\n*/
	bool SetDayOfMonth(const unsigned& dd);

			/** \brief
			Set the month (1 - 12)\n*/
	bool SetMonth(const unsigned& mm);

			/** \brief
			Set the year\n*/
	void SetYear(const unsigned& yyyy);



	// Accessor Methods
	////////////////////////////////

			/** \brief
			Get the day of the month (1 - 31)\n*/
	void GetDayOfMonth(unsigned& dd) const;

			/** \brief
			Get the month (1 - 12)\n*/
	void GetMonth(unsigned& mm) const;

			/** \brief
			Get the month as a string (January - December)\n*/
	void GetMonthStr(string &monthStr) const;

			/** \brief
			Get the year\n*/
	void GetYear(unsigned& yyyy) const;



private:


	// Private Method (would be better as a nonmember function.)
	////////////////////////////////

	/** \brief
	Check if the day of the month is valid for the given month\n*/
	bool DayIsValid() const;



	// Private Member Variables
	////////////////////////////////

	/** \brief
	The day of the month\n*/
	unsigned dayOfMonth;

	/** \brief
	The month\n*/
	unsigned month;

	/** \brief
	The year\n*/
	unsigned year;
};






#endif  //_DATE_H
