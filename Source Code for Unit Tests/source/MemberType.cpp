/**
\file		MemberType.cpp
\n
\brief		MemberType class implementation
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/


#include "../h/MemberType.h"

#include <fstream>
#include <string>


using namespace std;




		/**
		Constructor (default).  Arguments: none
		\n
		*/
MemberType::MemberType()
{
	Reset();
}





		/**
		Destructor.  Arguments: none.
		\n
		*/
MemberType::~MemberType()
{
}






		/**
		Copy constructor.  Arguments: MemberType
		\n
		@param	otherMember	(MemberType) The member object we are copying from.
		\n
		*/
MemberType::MemberType(const MemberType & otherMember)
{
	Reset();
	Copy(otherMember);
}





		/**
		Assignment operator override..  Arguments: MemberType
		\n
		@param	otherMember	(MemberType) The user object we are copying from.
		\n
		@return	MemberType	The value of the current object (*this)
		\n
		Checks to avoid self-assignment.
		*/
const MemberType & MemberType::operator=(const MemberType & otherMember)
{
	// Avoid self-assignment
	if (this != &otherMember)
	{
		Copy(otherMember);
	}
	return *this; // The value of the object that was just assigned.
}





		/**
		Equality comparison operator override..  Arguments: MemberType
		\n
		@param	otherMember	(MemberType) The member object we are comparing against.
		\n
		@return	bool	True if the given object matches this object.
		\n
		*/
bool MemberType::operator==(const MemberType & otherMember) const
{
	// Checking against self ?
	// This is an address comparison (i think)  OTHERWISE it will be infinite recursion.  AAA!
	if (this != &otherMember)
	{


		// This MemberType
		string myFirstName		= "none";
		string myLastName		= "none";
		long myUserId			= 0;
		string myAuthorityLevel	= "patron";

		getFirstName	(myFirstName);
		getLastName		(myLastName);
		getUserId		(myUserId);
		getAuthority	(myAuthorityLevel);



		// Other MemberType
		string otherFirstName		= "none";
		string otherLastName		= "none";
		long otherUserId			= 0;
		string otherAuthorityLevel	= "patron";

		otherMember.getFirstName	(otherFirstName);
		otherMember.getLastName		(otherLastName);
		otherMember.getUserId		(otherUserId);
		otherMember.getAuthority	(otherAuthorityLevel);


		// Equality comparison happens here.
		////////////////////////////////////
		if	(
			myFirstName			== otherFirstName		&&
			myLastName			== otherLastName		&&
			myUserId			== otherUserId			&&
			myAuthorityLevel	== otherAuthorityLevel
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







// Mutators






		/**
		Set the first name of this user.  Arguments: string
		\n
		@param	s	(string)
		*/
void MemberType::setFirstName                 ( const string   & s )
{
	firstName = s;
}



		/**
		Set the last name of this user.  Arguments: string
		\n
		@param	s	(string)
		*/
void MemberType::setLastName             	  ( const string   & s )
{
	lastName = s;
}





		/**
		Set the ID of this user.  Arguments: long
		\n
		@param	l	(long)
		\n
		*/
void MemberType::setUserId                    ( const long     & l )
{
	userId = l;
}





		/**
		Set whether this user is "staff" or "patron"  Arguments: string
		\n
		@param	s	(string)
		*/
void MemberType::setAuthority                 ( const string   & s )
{
	authorityLevel = s;
}








// Accessors




		/**
		Get the first name of this user.  Arguments: string
		\n
		@param	s	(string)
		*/
void MemberType::getFirstName                 (string   & s ) const
{
	s = firstName;
}



		/**
		Get the last name of this user.  Arguments: string
		\n
		@param	s	(string)
		*/
void MemberType::getLastName             	  (string   & s ) const
{
	s = lastName;
}



		/**
		Get the ID of this user.  Arguments: long
		\n
		@param	l	(long) Receives the User ID of this user.
		\n
		*/
void MemberType::getUserId                    (long     & l ) const
{
	l = userId;
}



		/**
		Get whether this user is "staff" or "patron".  Arguments: string
		\n
		@param	s	(string) Receives the data.
		\n
		*/
void MemberType::getAuthority                 (string   & s ) const
{
	s = authorityLevel;
}









		/**
		Reset method.  Arguments: none
		\n
		*/
void MemberType::Reset()
{
	firstName		= "none";
	lastName		= "none";
	userId			= 0;		// User cannot use the system
	authorityLevel	= "patron";
}






		/**
		Copy method.  Arguments: MemberType
		\n
		@param	otherMember	(MemberType) The user object we are copying from
		\n
		*/
void MemberType::Copy(const MemberType & otherMember)
{

	// Other MemberType
	string otherFirstName		= "none";
	string otherLastName		= "none";
	long otherUserId			= 0;
	string otherAuthorityLevel	= "patron";

	// Get properties of other member
	otherMember.getFirstName	(otherFirstName);
	otherMember.getLastName		(otherLastName);
	otherMember.getUserId		(otherUserId);
	otherMember.getAuthority	(otherAuthorityLevel);

	// Set my properties
	setFirstName	(otherFirstName);
	setLastName		(otherLastName);
	setUserId		(otherUserId);
	setAuthority	(otherAuthorityLevel);
}



