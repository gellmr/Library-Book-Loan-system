#include <iostream>

#include <fstream>

#include "h/BinarySearchTree.h"
#include "h/BookType.h"
#include "h/Date.h"

using namespace std;
///////////////////////////////// UNIT TESTING


















bool testBookTypeclass()
{



	char * outputFileName = "testResults.txt";

	std::fstream file(outputFileName, ios::out);

	if(!file.is_open())
	{
		cout << "File not found!\n";
		return 0;
	}




	// SETTERS / GETTERS

	file << "test BookType class  Getters/Setters \t\t\t";

	BookType b;

	string		title;
	unsigned	numberOfAuthors;
	string		publisher;
	string auth0;
	string auth1;
	string auth2;
	unsigned	numberOfCopiesInStock;
	double		price;
	long		isbn;

	title = "SomeBook";
	numberOfAuthors = 3;
	publisher = "SomePublisher";
	auth0 = "Adam";
	auth1 = "Beth";
	auth2 = "Celina";
	numberOfCopiesInStock = 3;
	price = 3.33;
	isbn = 12345;

	b.setTitle(title);
	b.setNumberOfAuthors(numberOfAuthors);
	b.setAuthorAt(auth0, 0);
	b.setAuthorAt(auth1, 1);
	b.setAuthorAt(auth2, 2);
	b.setPublisher(publisher);
	b.setNumberOfCopiesInStock(numberOfCopiesInStock);
	b.setPrice(price);
	b.setIsbn(isbn);


	string		title2;
	unsigned	numberOfAuthors2;
	string		publisher2;
	string auth02;
	string auth12;
	string auth22;
	unsigned	numberOfCopiesInStock2;
	double		price2;
	long		isbn2;

	b.getTitle(title2);
	b.getNumberOfAuthors(numberOfAuthors2);
	b.getAuthorAt(auth02, 0);
	b.getAuthorAt(auth12, 1);
	b.getAuthorAt(auth22, 2);
	b.getPublisher(publisher2);
	b.getNumberOfCopiesInStock(numberOfCopiesInStock2);
	b.getPrice(price2);
	b.getIsbn(isbn2);

	// Climbe ze mountain...

	bool pass = false;

	if (title == title2)
	{
		if (numberOfAuthors == numberOfAuthors2)
		{
			if (publisher == publisher2)
			{
				if (auth0 == auth02)
				{
					if (auth1 == auth12)
					{
						if (auth2 == auth22)
						{
							if (publisher == publisher2)
							{
								if (numberOfCopiesInStock == numberOfCopiesInStock2)
								{
									if (price == price2)
									{
										if (isbn == isbn2)
										{
											pass = true; // Phew. Now climb back down.
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// Use && next time.

	if (pass)
	{
		file << "Passed" << endl;
	}
	else
	{
		file << "Failed" << endl;
	}






	// Test the assignment operator override.
	//		Compare two objects with same values.
	//		Object comparison == true
	//		...success

	file << "test BookType class  Assignment Operator Override() \t";

	BookType bookOne;
	BookType bookTwo;

	title = "SomeBook";
	numberOfAuthors = 3;
	publisher = "SomePublisher";
	auth0 = "Adam";
	auth1 = "Beth";
	auth2 = "Celina";
	numberOfCopiesInStock = 3;
	price = 3.33;
	isbn = 12345;

	bookOne.setTitle(title);
	bookOne.setNumberOfAuthors(numberOfAuthors);
	bookOne.setAuthorAt(auth0, 0);
	bookOne.setAuthorAt(auth1, 1);
	bookOne.setAuthorAt(auth2, 2);
	bookOne.setPublisher(publisher);
	bookOne.setNumberOfCopiesInStock(numberOfCopiesInStock);
	bookOne.setPrice(price);
	bookOne.setIsbn(isbn);

	bookTwo.setTitle(title);
	bookTwo.setNumberOfAuthors(numberOfAuthors);
	bookTwo.setAuthorAt(auth0, 0);
	bookTwo.setAuthorAt(auth1, 1);
	bookTwo.setAuthorAt(auth2, 2);
	bookTwo.setPublisher(publisher);
	bookTwo.setNumberOfCopiesInStock(numberOfCopiesInStock);
	bookTwo.setPrice(price);
	bookTwo.setIsbn(isbn);

	bookTwo.setAuthorAt("Harry", 2); // This should make the test fail. Something is wrong.

	if (bookOne == bookTwo)
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
	file << "test BookType class  getKey() \t\t\t\t";

	BookType mbt;
	mbt.setIsbn(5432);
	long someKey;
	someKey = mbt.getKey();
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

	testBookTypeclass();	// book type class

	return 0;
}
