#include <iostream>

#include <fstream>

#include "h/BinarySearchTree.h"
#include "h/BookType.h"


using namespace std;
///////////////////////////////// UNIT TESTING








bool testBSTclass()
{
	char * outputFileName = "testResults.txt";

	std::fstream file(outputFileName, ios::out);

	if(!file.is_open())
	{
		cout << "File not found!\n";
		return 0;
	}




	// Default construction
	//		Check that resulting object has a value
	//		isEmpty() returns true, success

	file << "Test Default Construction. \t";
	BinarySearchTree<BookType> bst;
	if (bst.isEmpty())
	{
		file << "Passed" << endl;
	}
	else
	{
		file << "FAILED" << endl;
	}


	// Insertion
	//		Insert an object to tree.
	//		Check that node count is +1
	//		treeNodeCount() returns 1 == success
	file << "Test Insertion  \t\t";
	BookType book;
	bst.insert(book);
	int treeCount = bst.treeNodeCount();
	if (treeCount == 1)
	{
		file << "Passed" << endl;
	}
	else
	{
		file << "FAILED" << endl;
	}


	// Deletion
	//		Delete the object, using deleteNode()
	//		Check that the node count is 0
	//		treeNodeCount() returns 0 == success
	file << "Test Deletion \t\t\t";
	bst.deleteNode(book);
	treeCount = bst.treeNodeCount();
	if (treeCount == 0)
	{
		file << "Passed" << endl;
	}
	else
	{
		file << "FAILED" << endl;
	}



	// Search
	//		Insert some items and search for one of them.
	//		search() returns index of the item: success.
	file << "Test Search \t\t\t";

	book.setIsbn(111);
	bst.insert(book);
	book.setIsbn(333);
	bst.insert(book);
	book.setIsbn(11);
	bst.insert(book);
	book.setIsbn(33);
	bst.insert(book);
	book.setIsbn(22);
	bst.insert(book);
	book.setIsbn(222);
	bst.insert(book);

	BookType anotherBook;
	anotherBook.setIsbn(11);

	if (bst.search(anotherBook))
	{
		file << "Passed" << endl;
	}
	else
	{
		file << "FAILED" << endl;
	}




	// SearchByKey
	//		Insert some items with known ISBN values
	//		search for one of them, providing ISBN.
	//		searchByKey() returns the idx of the item: success.
	file << "Test SearchByKey \t\t";

	if (bst.searchByKey(333))
	{
		file << "Passed" << endl;
	}
	else
	{
		file << "FAILED" << endl;
	}




	// ReplaceNode
	//		Insert some items with known ISBN values,
	//		replace one of them by specifying the ISBN
	//		and replacement object value.
	//		if replaceNode() returns true && node actually changed : success.
	file << "Test replaceNode \t\t";

	BookType yetAnotherBook;
	string theTitle;
	theTitle = "Node 777";
	yetAnotherBook.setTitle(theTitle);
	yetAnotherBook.setIsbn(777);

	if (bst.replaceNode(333, yetAnotherBook)) // Replace node 333 with node 777
	{
		// Replaced node 333
		BookType stillAnotherBook;
		bst.getNodeValue(777, stillAnotherBook); // Get node 777

		string itsTitle;
		stillAnotherBook.getTitle(itsTitle); // Node actually changed ?

		if (itsTitle == "Node 777")
		{
			// Node 333 is now Node 777. The integrity of the search tree has been destroyed, but the unit test has succeeded.
			file << "Passed" << endl;
		}
		else
		{
			file << "FAILED" << endl;
		}
	}
	else
	{
		file << "FAILED" << endl;
	}




	// GetNodeValue
	//		Insert some items with known ISBN values,
	//		retrieve one of them by specifying the ISBN
	//		and providing an object to receive its value.
	//		getNodeValue() returns the object which matches
	//		the original via equality comparison
	//		operator (==) ...success
	file << "Test GetNodeValue \t\t";

	BookType greatBook;

	greatBook.setTitle("Great Book");
	greatBook.setIsbn(444);
	greatBook.setPublisher             ( "Great Publisher" );
	greatBook.setPrice                 ( 44.44 );
	greatBook.setNumberOfCopiesInStock ( 44 );
	greatBook.setNumberOfAuthors       ( 4 );
	greatBook.setAuthorAt ( "Auth 0" , 0 );
	greatBook.setAuthorAt ( "Auth 1" , 1 );
	greatBook.setAuthorAt ( "Auth 2" , 2 );
	greatBook.setAuthorAt ( "Auth 3" , 3 );

	bst.insert(greatBook);

	BookType otherBook;
	bst.getNodeValue(444, otherBook); // Get node 444


	if (otherBook == greatBook)
	{
		file << "Passed" << endl;
	}
	else
	{
		file << "FAILED" << endl; // Problem with the assignment operator override.
	}






	// inOrderDump
	//		Insert some objects and dump them to a vector.
	//		Display the contents of the vector.
	//		Displayed object values match the original
	//		values... success.

	file << "Test inOrderDump \t\t";


	bst.destroyTree();
	vector<BookType> booksVect;
	vector<BookType> booksVectB;

	BookType b;
	b.setIsbn(57);
	booksVect.push_back(b);
	b.setIsbn(58);
	booksVect.push_back(b);
	b.setIsbn(59);
	booksVect.push_back(b);

	bst.insert(booksVect[0]);
	bst.insert(booksVect[1]);
	bst.insert(booksVect[2]);

	bst.inOrderDump(booksVectB);

	if (booksVectB[0] == booksVect[0])
	{
		if (booksVectB[1] == booksVect[1])
		{
			if (booksVectB[2] == booksVect[2])
			{
				file << "Passed" << endl;
			}
			else
			{
				file << "FAILED" << endl; // Problem with the assignment operator override.
			}
		}
		else
		{
			file << "FAILED" << endl; // Problem with the assignment operator override.
		}
	}
	else
	{
		file << "FAILED" << endl; // Problem with the assignment operator override.
	}

	// Finished testing BST class.
	return 1;
}






int main()
{
	// Perform unit testing here.

	testBSTclass();			// binary search tree
//	testBookLoanclass();	// book loan class
//	testBookTypeclass();	// book type class
//
//	testDateclass();		// date class
//	testMemberTypeclass();	// member type class

	return 0;
}
