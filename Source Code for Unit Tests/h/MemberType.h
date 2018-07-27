/**
\file		MemberType.h
\brief		MemberType class definition.
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/

#if !defined(_MEMBERTYPE_H)
#define _MEMBERTYPE_H

#include <string>

using namespace std;



		/**
		\class MemberType.
		\brief Stores information about a user (staff / patron) of the Library System.
		*/
class MemberType
{

public:

			/**	\brief
			Default Constructor. \n*/
	MemberType();



			/**	\brief
			Destructor. \n*/
	~MemberType();



			/**	\brief
			Copy constructor. \n*/
	MemberType(const MemberType & b);



			/**	\brief
			Assignment op override. \n*/
	const MemberType& operator=(const MemberType & otherMember);



			/**	\brief
			Equality Comparison operator override. \n*/
	bool operator==(const MemberType & otherMember) const;





	// Mutators


			/**	\brief
			Set the first name of this Member. \n*/
	void setFirstName                 ( const string   & s );


			/**	\brief
			Set the last name of this Member. \n*/
	void setLastName             	  ( const string   & s );


			/**	\brief
			Set the user ID of this Member. \n*/
	void setUserId                    ( const long     & l );


			/**	\brief
			Set whether this Member is staff or a patron of the Library. \n*/
	void setAuthority                 ( const string   & s );







	// Accessors


			/**	\brief
			Get the first name of this member. \n*/
	void getFirstName                 ( string   & s ) const;


			/**	\brief
			Get the last name of this member. \n*/
	void getLastName             	  ( string   & s ) const;


			/**	\brief
			Get the user ID of this member. \n*/
	void getUserId                    ( long     & l ) const;


			/**	\brief
			Get whether this Member is staff or a patron of the Library. \n*/
	void getAuthority                 ( string   & s ) const;







private:

			/**	\brief
			Reset method. \n*/
	void Reset();



			/**	\brief
			Copy method. \n*/
	void Copy(const MemberType & b);




	// Private data members



			/**	\brief
			First name of the member. \n*/
	string firstName;



			/**	\brief
			Last name of the member. \n*/
	string lastName;



			/**	\brief
			User ID of the member. \n*/
	long userId;



			/**	\brief
			"staff" or "patron". \n*/
	string authorityLevel;

};

#endif
