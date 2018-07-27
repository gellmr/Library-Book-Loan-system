/**
\file		Date.cpp
\n
\brief		Date class implementation
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/

#include <iostream>
#include <string>

#include "../h/Date.h"




using namespace std;



		/** Default Constructor.*/
Date::Date()
{
	Reset();
}



		/** Copy Constructor.    Argument: Date \n
		@param d           Date instance whose properties we are copying from.\n*/
Date::Date(const Date& d)
{
	d.GetDayOfMonth(dayOfMonth);
	d.GetMonth(month);
	d.GetYear(year);
}




		/** Destructor.*/
Date::~Date()
{
}


		/** Reset (empty) this object.*/
void Date::Reset()
{
	// Reset member variables.
	dayOfMonth = 1;
	month      = 1;
	year       = 2000;
}




		/**
		Checks if the (dayOfMonth) is valid for the (month).\n
		@return            true if valid.*/
bool Date::DayIsValid() const
{
	unsigned monMax = 31;
	switch(month)
	{
		case 2:
		//"February"
		// Assumes we are not on a leap year.
		// There is room for improvement here.
		monMax = 28;
		break;

		case 4:
		//"April"
		monMax = 30;
		break;

		case 6:
		//"June"
		monMax = 30;
		break;

		case 9:
		//"September"
		monMax = 30;
		break;

		case 11:
		//"November"
		monMax = 30;
		break;
	}

	// Enforce a valid range for the day of the month.
	if (dayOfMonth <= monMax && dayOfMonth > 0)
	{
		return true;
	}
	return false;
}





		/**
		Set the day of the month. Argument: unsigned \n

		@param dd          The day of the month, eg 1 - 31.\n
		If an invalid day is specified (eg 32) then this method will have no effect and will return false.\n

		@return            true if successful.\n
		*/
bool Date::SetDayOfMonth(const unsigned& dd)
{
	// Keep a backup in case this method fails.
	unsigned oldDay = dayOfMonth;
	dayOfMonth = dd;

	// Check validity.
	if (DayIsValid())
	{
		// Success.
		return true;
	}

	// Unsuccessful.
	dayOfMonth = oldDay; // Revert back to previous value.
	return false;
}





		/**
		Set the month. Argument: unsigned \n

		@param mm          The month, eg 1 - 12.\n
		If the current value for the day of the month is not valid with the given month,\n
		(eg, 31 November) then this method will have no effect and will return false.\n

		@return            true if successful.\n
		*/
bool Date::SetMonth(const unsigned& mm)
{
	if (mm <= 12 && mm > 0)
	{
		// Keep a backup in case this method fails.
		unsigned oldMonth = month;
		month = mm;

		// Check validity.
		if (DayIsValid())
		{
			// Success.
			return true;
		}

		// Unsuccessful.
		month = oldMonth; // Revert back to previous value.
	}
	return false;
}





		/**
		Set the year. Argument: unsigned \n
		@param yyyy        The year, eg 2011.*/
void Date::SetYear(const unsigned& yyyy)
{
	year = yyyy;
}








		/**
		Get the day of the month. Argument: unsigned \n
		@param dd          (reference parameter) receives the value of the day of the month.*/
void Date::GetDayOfMonth(unsigned& dd) const
{
	dd = dayOfMonth;
}


		/**
		Get the month. Argument: unsigned \n
		@param mm          (reference parameter) receives the value of the month.*/
void Date::GetMonth(unsigned& mm) const
{
	mm = month;
}

		/**
		Get the month as a string. Argument: string \n
		@param monthStr       (reference parameter) receives the value of the month as a descriptive string.*/
void Date::GetMonthStr(string& monthStr) const
{
	switch(month)
	{
		case 1:
		monthStr = "January";
		break;

		case 2:
		monthStr = "February";
		break;

		case 3:
		monthStr = "March";
		break;

		case 4:
		monthStr = "April";
		break;

		case 5:
		monthStr = "May";
		break;

		case 6:
		monthStr = "June";
		break;

		case 7:
		monthStr = "July";
		break;

		case 8:
		monthStr = "August";
		break;

		case 9:
		monthStr = "September";
		break;

		case 10:
		monthStr = "October";
		break;

		case 11:
		monthStr = "November";
		break;

		case 12:
		monthStr = "December";
		break;
	}
}




		/**
		Get the year. Argument: unsigned \n
		@param yyyy        (reference parameter) receives the value of the year.*/
void Date::GetYear(unsigned& yyyy) const
{
	yyyy = year;
}






		/**
		Overrides the Assignment Operator.  Argument: Date \n
		@param rightDate    The Date instance whose properties we are deep-copying from.\n
		@return             The value of the object just assigned, eg: *this\n*/
const Date& Date::operator=(const Date& rightDate)
{
	// Avoid self-assignment
	if (this != &rightDate)
	{
		unsigned dom, mon, yr;

		rightDate.GetDayOfMonth(dom);
		rightDate.GetMonth(mon);
		rightDate.GetYear(yr);

		SetDayOfMonth(dom);
		SetMonth(mon);
		SetYear(yr);
	}
	return *this; // The value of the object that was just assigned.
}



		/**
		Overrides the Equality Comparison Operator. Argument: Date \n
		@param rightDate    The Date instance whose values we are comparing against.\n
		@return             bool true if these Date objects are equal.\n*/
bool Date::operator==(const Date& rightDate) const
{
	unsigned dom, mon, yr;

	rightDate.GetDayOfMonth(dom);
	rightDate.GetMonth(mon);
	rightDate.GetYear(yr);

	unsigned myDom, myMon, myYr;

	GetDayOfMonth(myDom);
	GetMonth(myMon);
	GetYear(myYr);

	if (
		dom == myDom &&
		mon == myMon &&
		 yr == myYr
		)
	{
		return true;
	}
	return false;
}
