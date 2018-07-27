#include <fstream>
#include <iostream>

#include "h/BinarySearchTree.h"
#include "h/MemberType.h"


using namespace std;
///////////////////////////////// UNIT TESTING







bool testMemberTypeclass()
{

	char * outputFileName = "testResults.txt";

	std::fstream file(outputFileName, ios::out);

	if(!file.is_open())
	{
		cout << "File not found!\n";
		return 0;
	}



	// SETTERS / GETTERS
	string   fname;
	string   lname;
	long     uid;
	string	 authority;

	fname = "firstName";
	lname = "lastName";
	uid   = 1234;
	authority = "patron";

	MemberType m;

	// SET
	m.setFirstName(fname);
	m.setLastName(lname);
	m.setUserId(uid);
	m.setAuthority(authority);

	string   fname2;
	string   lname2;
	long     uid2;
	string	 authority2;

	// GET
	m.getFirstName(fname2);
	m.getLastName(lname2);
	m.getUserId(uid2);
	m.getAuthority(authority2);

	//fname = "A";
	//lname = "A";
	//uid2 = 5454;
	//authority2 = "staff";

	if (
		fname     == fname2 &&
		lname     == lname2 &&
		uid       == uid2   &&
		authority == authority2
		)
	{
		file << " MemberType unit test - getters and setters: Passed." << endl;
	}
	else
	{
		file << " MemberType unit test - getters and setters: FAILED." << endl;
	}

	return 1;

}




int main()
{
	// Perform unit testing here.

	testMemberTypeclass();	// member type class

	return 0;
}
