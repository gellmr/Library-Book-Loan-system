
#include <fstream>

#include <iostream>

#include <limits.h>

#include "h/Date.h"


using namespace std;


int main()
{


	char * outputFileName = "testResults.txt";

	std::fstream file(outputFileName, ios::out);

	if(!file.is_open())
	{
		cout << "File not found!\n";
		return 0;
	}





	double testNumber = 0;

	file << "Tesing the Date class  for internal validation." << endl;
	Date d;
	unsigned dd;

	// TEST GETTERS / SETTERS



	///////////////////////////////// Test 1
	++testNumber;
	d.SetMonth(1);
	d.SetYear(2000);
	d.SetDayOfMonth(1);
	d.GetDayOfMonth(dd);
	if ( dd == 1)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}





	///////////////////////////////// Test 2
	++testNumber;
	d.SetMonth(1);
	d.SetYear(2000);
	d.SetDayOfMonth(UINT_MAX); // Method should have no effect.
	d.GetDayOfMonth(dd);
	if ( dd == 1)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}



	///////////////////////////////// Test 3
	++testNumber;
	d.SetMonth(1);
	d.SetYear(2000);
	d.SetDayOfMonth(0); // Method should have no effect.
	d.GetDayOfMonth(dd);
	if ( dd == 1)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}



	///////////////////////////////// Test 4
	++testNumber;
	d.SetMonth(1);
	d.SetYear(2000);
	d.SetDayOfMonth(31); // Method should have no effect.
	d.GetDayOfMonth(dd);
	if ( dd == 31)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}




	///////////////////////////////// Test 5
	++testNumber;
	d.SetMonth(1);
	d.SetYear(2000);
	d.SetDayOfMonth(1);
	d.SetDayOfMonth(32); // Method should have no effect.
	d.GetDayOfMonth(dd);
	if ( dd == 1)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}





	///////////////////////////////// Test 6
	++testNumber;
	d.SetMonth(2);
	d.SetYear(2000);
	d.SetDayOfMonth(28);
	d.GetDayOfMonth(dd);
	if ( dd == 28)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}




	///////////////////////////////// Test 7
	++testNumber;
	d.SetMonth(2);
	d.SetYear(2000);
	d.SetDayOfMonth(1);
	d.SetDayOfMonth(29);  // No effect
	d.GetDayOfMonth(dd);
	if ( dd == 1)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}




	///////////////////////////////// Test 8
	++testNumber;
	d.SetMonth(3);
	d.SetYear(2000);
	d.SetDayOfMonth(31);
	d.GetDayOfMonth(dd);
	if ( dd == 31)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}




	///////////////////////////////// Test 9
	++testNumber;
	d.SetMonth(3);
	d.SetYear(2000);
	d.SetDayOfMonth(1);
	d.SetDayOfMonth(32); // No effect
	d.GetDayOfMonth(dd);
	if ( dd == 1)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}



	///////////////////////////////// Test 10
	++testNumber;
	d.SetMonth(4);
	d.SetYear(2000);
	d.SetDayOfMonth(30);
	d.GetDayOfMonth(dd);
	if ( dd == 30)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}



	///////////////////////////////// Test 11
	++testNumber;
	d.SetMonth(4);
	d.SetYear(2000);
	d.SetDayOfMonth(1);
	d.SetDayOfMonth(31); // no effect
	d.GetDayOfMonth(dd);
	if ( dd == 1)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}




	///////////////////////////////// Test 11.1
	testNumber = 11.1;
	d.SetMonth(5);
	d.SetYear(2000);
	d.SetDayOfMonth(31);
	d.GetDayOfMonth(dd);
	if ( dd == 31)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}



	///////////////////////////////// Test 11.2
	testNumber = 11.2;
	d.SetMonth(5);
	d.SetYear(2000);
	d.SetDayOfMonth(1);
	d.SetDayOfMonth(32); // no effect
	d.GetDayOfMonth(dd);
	if ( dd == 1)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}




	///////////////////////////////// Test 12
	testNumber = 12;
	d.SetMonth(6);      //June
	d.SetYear(2000);
	d.SetDayOfMonth(1);
	d.SetDayOfMonth(30);
	d.GetDayOfMonth(dd);
	if ( dd == 30)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}





	/////////////////////////////////
	testNumber = 13;
	d.SetMonth(6);      //June
	d.SetYear(2000);
	d.SetDayOfMonth(1);
	d.SetDayOfMonth(30);
	d.SetDayOfMonth(31); // no effect
	d.GetDayOfMonth(dd);
	if ( dd == 30)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}




	/////////////////////////////////
	testNumber = 14;
	d.SetMonth(7);      //July
	d.SetYear(2000);
	d.SetDayOfMonth(1);
	d.SetDayOfMonth(31);
	d.GetDayOfMonth(dd);
	if ( dd == 31)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}



	/////////////////////////////////
	testNumber = 15;
	d.SetMonth(7);      //July
	d.SetYear(2000);
	d.SetDayOfMonth(1);
	d.SetDayOfMonth(32); // no effect
	d.GetDayOfMonth(dd);
	if ( dd == 1)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}



	/////////////////////////////////
	testNumber = 16;
	d.SetMonth(8);      //August
	d.SetYear(2000);
	d.SetDayOfMonth(31);
	d.GetDayOfMonth(dd);
	if ( dd == 31)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}


	/////////////////////////////////
	testNumber = 17;
	d.SetMonth(8);      //August
	d.SetYear(2000);
	d.SetDayOfMonth(31);
	d.SetDayOfMonth(32); // no effect
	d.GetDayOfMonth(dd);
	if ( dd == 31)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}



	/////////////////////////////////
	testNumber = 18;
	d.SetMonth(9);      //September
	d.SetYear(2000);
	d.SetDayOfMonth(30);
	d.GetDayOfMonth(dd);
	if ( dd == 30)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}



	/////////////////////////////////
	testNumber = 19;
	d.SetMonth(9);      //September
	d.SetYear(2000);
	d.SetDayOfMonth(30);
	d.SetDayOfMonth(31); // no effect
	d.GetDayOfMonth(dd);
	if ( dd == 30)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}




	/////////////////////////////////
	testNumber = 20;
	d.SetMonth(10);      //October
	d.SetYear(2000);
	d.SetDayOfMonth(31);
	d.SetDayOfMonth(32); // no effect
	d.GetDayOfMonth(dd);
	if ( dd == 31)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}


	/////////////////////////////////
	testNumber = 21;
	d.SetDayOfMonth(2);
	d.SetMonth(11);      //November
	d.SetYear(2000);
	d.SetDayOfMonth(30);
	d.SetDayOfMonth(31); // no effect
	d.GetDayOfMonth(dd);
	if ( dd == 30)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}




	/////////////////////////////////
	testNumber = 22;
	d.SetMonth(12);      //December
	d.SetYear(2000);
	d.SetDayOfMonth(31);
	d.SetDayOfMonth(32); // no effect
	d.GetDayOfMonth(dd);
	if ( dd == 31)
	{
		file << "Passed test " << testNumber << endl;
	}
	else
	{
		file << "Failed test " << testNumber << endl;
	}

	file << endl;






	// TEST the getters and setters

	Date anotherDate;

	unsigned certainMonth = 8;
	unsigned dayOMonth    = 14;
	unsigned fineYear     = 2011;
	anotherDate.SetMonth(      certainMonth );
	anotherDate.SetDayOfMonth( dayOMonth    );
	anotherDate.SetYear(       fineYear     );

	unsigned certainMonth2 = 1;
	unsigned dayOMonth2    = 1;
	unsigned fineYear2     = 2001;
	anotherDate.GetMonth(       certainMonth2 );
	anotherDate.GetDayOfMonth(  dayOMonth2    );
	anotherDate.GetYear(        fineYear2     );

	if (
			certainMonth == certainMonth2 &&
			dayOMonth    == dayOMonth2 &&
			fineYear     == fineYear2
		)
	{
		file << "Passed getters and setters  test "  << endl;
	}
	else
	{
		file << "Failed getters and setters  test "  << endl;
	}

	file << endl;



	file << "End of unit tests for the date class." << endl;

	return 0;
}



