#include <iostream>

#include <fstream>

#include "h/BinarySearchTree.h"
#include "h/BookType.h"
#include "h/BookLoan.h"
#include "h/Date.h"

using namespace std;
///////////////////////////////// UNIT TESTING





bool testBookLoanclass()
{
	char * outputFileName = "testResults.txt";

	std::fstream file(outputFileName, ios::out);

	if(!file.is_open())
	{
		cout << "File not found!\n";
		return 0;
	}



	// SETTERS / GETTERS

	file << "test BookLoan class  Getters/Setters \t\t\t";

	BookLoan myBookLoan;

	// Set
	long bIsbn;
	long patronID;
	Date dBorr;
	Date dDue;

	bIsbn    = 3333;
	patronID = 33;

	dBorr.SetDayOfMonth(3);
	dBorr.SetMonth(3);
	dBorr.SetYear(3);

	dDue.SetDayOfMonth(3);
	dDue.SetMonth(4);
	dDue.SetYear(3);

	myBookLoan.setBookISBN    (bIsbn);
	myBookLoan.setPatronId    (patronID);
	myBookLoan.setBorrowedDate(dBorr);
	myBookLoan.setDueDate     (dDue);

	// Get
	long after_bIsbn;
	long after_patronID;
	Date after_dBorr;
	Date after_dDue;

	myBookLoan.getBookISBN    (after_bIsbn);
	myBookLoan.getPatronId    (after_patronID);
	myBookLoan.getBorrowedDate(after_dBorr);
	myBookLoan.getDueDate     (after_dDue);


	bool pass = false;
	if (after_bIsbn == bIsbn)
	{
		if (after_patronID == patronID)
		{
			if (after_dBorr == dBorr)
			{
				if (after_dDue == dDue)
				{
					pass = true;
				}
			}
		}
	}
	if (pass)
	{
		file << "Passed" << endl;
	}
	else
	{
		file << "Failed" << endl;
	}





	// getKey()
	//		Set the ISBN and call getKey()
	//		The key value matches the original ISBN
	//		...success

	file << "test BookLoan class  getKey() \t\t\t\t";

	BookLoan myBookLoan2;
	myBookLoan2.setBookISBN(5432);
	long someKey;
	someKey = myBookLoan2.getKey();
	if (someKey == 5432)
	{
		file << "Passed" << endl;
	}
	else
	{
		file << "Failed" << endl;
	}

	return true;
}







int main()
{
	// Perform unit testing here.

	testBookLoanclass();	// book loan class

	return 0;
}
