/**
\file		LibSystem.cpp
\n
\brief		LibSystem class implementation
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/

#include <iostream>
#include <iomanip>

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include <time.h>

#include <map>

#include "../h/LibSystem.h"
#include "../h/BookType.h"
#include "../h/BookLoan.h"
#include "../h/BooksLoader.h"
#include "../h/LoansLoader.h"
#include "../h/MembersLoader.h"
#include "../h/MemberType.h"
#include "../h/SimpleBinaryTree.h"
#include "../h/BinarySearchTree.h"



using namespace std;





		/**
		Default Constructor.  Arguments: none.
		\n
		*/
LibSystem::LibSystem()
{

	// Use the regular versions of the files,
	// which can be saved over when we quit the program.
	BOOKFILE = "LibrarySettings/allBooks.txt";
	USERFILE = "LibrarySettings/allUsers.txt";
	LOANFILE = "LibrarySettings/allLoans.txt";

	BOOK_RESTORE_FILE = "restoreLibraryDefaults/allBooks.txt";
	USER_RESTORE_FILE = "restoreLibraryDefaults/allUsers.txt";
	LOAN_RESTORE_FILE = "restoreLibraryDefaults/allLoans.txt";
}




		/**
		Destructor
		*/


		/**
		Destructor.  Arguments: none.
		\n
		*/
LibSystem::~LibSystem()
{
}



		/**
		Save the books, users and loans, and returns true if successful.  Arguments: none.
		\n
		@return	bool 	True if successful
		\n
		Saves system data to the NON-RESTORE location in the local directory.
		*/
bool LibSystem::saveSystemData()
{
	bool verbose = false; // 1 == debug mode  0 == normal mode

	// Uses the regular input / output files.  NEVER write to the backup files (for restoring default settings).
	string theBooksFile = BOOKFILE;
	string theUsersFile = USERFILE;
	string theLoansFile = LOANFILE;

	vector<BookType> bookVector;
	books.inOrderDump(bookVector);

	if (BooksLoader::SaveLibraryBooks(verbose,	theBooksFile.c_str(), bookVector))
	{
		if (MembersLoader::SaveUsers(verbose,	theUsersFile.c_str(), usersVect))
		{
			if (LoansLoader::SaveLoans(verbose,	theLoansFile.c_str(), loansVect))
			{
				// Success saving all files.
				return true;
			}
		}
	}
	return false;
}





		/**
		Init.  Arguments: bool
		\n
		@param	restore	(bool) Specify 1 if you want to load the default settings.  Otherwise specify false to load the regular settings.
		\n
		@return	bool	True if successful.
		\n
		Wipes current system data and loads data from text files.
		*/
bool LibSystem::init(const bool restore)
{

	bool verbose = false;

	bool loadSuccess;

	string inFileName;


	// Wipe data
	bookMap.clear();
	books.destroyTree();
	loans.destroyTree();
	loansVect.clear();
	usersVect.clear();




	string theBooksFile;
	string theUsersFile;
	string theLoansFile;

	if (restore)
	{
		// RESTORE
		// Use the backup versions of the files
		// The program never writes to these files.
		theBooksFile = BOOK_RESTORE_FILE;
		theUsersFile = USER_RESTORE_FILE;
		theLoansFile = LOAN_RESTORE_FILE;
	}
	else
	{
		// NOT RESTORE
		// Use the regular versions of the files,
		// which can be saved over when we quit the program.
		theBooksFile = BOOKFILE;
		theUsersFile = USERFILE;
		theLoansFile = LOANFILE;
	}





	//cout << "Loading all library books..." << endl << endl;

	inFileName = theBooksFile;

	vector<BookType> bookVector;

	loadSuccess = BooksLoader::LoadLibraryBooks(verbose, inFileName.c_str(), bookVector); // 1 == debug mode  0 == normal mode
	if (!loadSuccess)
	{
		cout << "Error while loading Books." << endl;
		return 0;
	}

	/*
	// TEST THE BOOK LOADER - MAKE AN EXTRA BOOK and SAVE.
	BookType b;
		b.setTitle("Extra Book");
		b.setNumberOfAuthors(4);
		b.setAuthorAt("Mike Gell",       0);
		b.setAuthorAt("Patrick Strauss", 1);
		b.setAuthorAt("Josephine March", 2);
		b.setAuthorAt("Chuck Norris",    3);
		b.setPublisher("Handley Books");
		b.setNumberOfCopiesInStock(1000);
		b.setPrice(50.00);
		b.setIsbn(998877);
	bookVector.push_back(b);

	char * outFileName = "allBooks.txt";
	BooksLoader::SaveLibraryBooks(1, outFileName, bookVector); // 1 == debug mode  0 == normal mode
	*/





	// Build existingBooks map (title --- isbn)

	//cout << "Build Binary Search Tree of BookType objects, and Map of title-isbn..." << endl;

	// We now want to store all the BookType objects in the 'books' BST
	// Build the BST of books

	vector<BookType>::iterator currentBook;

	//// Iterate through the vector of books.
	/////////////////////////////////////////
	for(currentBook = bookVector.begin(); currentBook != bookVector.end(); currentBook++)
	{
		BookType someBook;
		long theKey;
		string bookTitle;

		someBook = *currentBook;		// Relies upon copy construction

		someBook.getIsbn(theKey);		// Get the ISBN of this book, to use as the key for our map.
		someBook.getTitle(bookTitle);	// Get the title of the book.

		bookMap[bookTitle] = theKey;		// Insert (the title of the book) into the map.
		books.insert(someBook);	// Insert the BookType into the Binary Search Tree.
	}

	//cout << "Done." << endl << endl << endl;




	//cout << "Loading user data..." << endl << endl;

	// Load user data

	inFileName = theUsersFile;

	loadSuccess = MembersLoader::LoadUsers(verbose, inFileName.c_str(), usersVect); // 1 == debug mode  0 == normal mode
	if (!loadSuccess)
	{
		//cout << "Error while loading Users." << endl;
		return 0;
	}





	/*
	// TEST THE USER LOADER - MAKE AN EXTRA MEMBER and SAVE.
	MemberType m;
		m.setFirstName                 ( "Homer"   );
		m.setLastName             	   ( "Simpson" );
		m.setUserId                    (  5555    );
		m.setAuthority                 ( "patron"  );
	usersVect.push_back(m);

	MembersLoader::SaveUsers(1, inFileName, usersVect); // 1 == debug mode  0 == normal mode
	*/

	userIter = usersVect.begin();






	//cout << "Loading loan data..." << endl << endl;


	// Load loan data

	inFileName = theLoansFile;

	loadSuccess = LoansLoader::LoadLoans(verbose, inFileName.c_str(), loansVect); // 1 == debug mode  0 == normal mode
	if (!loadSuccess)
	{
		//cout << "Error while loading Loans." << endl;
		return 0;
	}

	/*
	// TEST THE LOANS LOADER - MAKE AN EXTRA LOAN and SAVE.
	BookLoan loan;

		Date dateBorrowed;
		Date dateDue;

		dateBorrowed.SetDayOfMonth		(	3			);
		dateBorrowed.SetMonth			(	3			);
		dateBorrowed.SetYear			(	1113		);

		dateDue.SetDayOfMonth			(	4			);
		dateDue.SetMonth				(	4			);
		dateDue.SetYear					(	1114		);

		loan.setBookISBN                ( 444			);
		loan.setPatronId                ( 1357			);
		loan.setBorrowedDate            ( dateBorrowed	);
		loan.setDueDate                 ( dateDue		);

	loansVect.push_back(loan);

	cout << "Saving loan data..." << endl << endl;
	LoansLoader::SaveLoans(1, inFileName.c_str(), loansVect); // 1 == debug mode  0 == normal mode
	*/








	//cout << "Build Binary Search Tree of BookLoan objects..." << endl;

	// We now want to store all the BookLoan objects in the 'loans' BST
	// Build the BST of loans

	vector<BookLoan>::iterator currentLoan;

	//// Iterate through the vector of loans.
	/////////////////////////////////////////
	for(currentLoan = loansVect.begin(); currentLoan != loansVect.end(); currentLoan++)
	{
		BookLoan someLoan;
		someLoan = *currentLoan;	// Relies upon copy construction
		loans.insert(someLoan);		// Insert the BookLoan into the Binary Search Tree.
	}



	//cout << "Done." << endl << endl << endl;
	return 1;

} // </init>









		/**
		Displays a welcome message.  Arguments: none.
		\n
		*/
void LibSystem::displayWelcomeMessage()
{
	// WELCOME MESSAGE

	cout << endl;
	cout << endl;
	cout << "Welcome to the library system."  << endl;
	cout << endl;
	cout << "There are currently no account passwords in use," << endl;
	cout << "so that you can log in simply." << endl;
	cout << endl;
	cout << endl;
	cout << "Registered users:";
	cout << endl;
	cout << endl;
}







		/**
		Display a list of all registered users.  Arguments: none.
		\n
		*/
void LibSystem::displayAllUsers()
{
	// DISPLAY A LIST OF ALL REGISTERED USERS

	cout << setw(12) << "FirstName";
	cout << setw(12) << "LastName";
	cout << setw(12) << "ID";
	cout << setw(12) << "MemberType" << endl << endl;


	for(userIter = usersVect.begin(); userIter != usersVect.end(); userIter++)
	{
		MemberType mem;

		mem = *userIter;

		string fName;
		string lName;
		long uid;
		string auth;

		mem.getFirstName ( fName );
		mem.getLastName  ( lName );
		mem.getUserId    ( uid );
		mem.getAuthority ( auth );

		cout << setw(12) << fName;
		cout << setw(12) << lName;
		cout << setw(12) << uid;
		cout << setw(12) << auth << endl;
	}

	cout << endl;
	cout << endl;
	cout << endl;
}











		/**
		Wait for the user to log in.  When the user logs in, set the current user.  Arguments: none.
		\n
		*/
void LibSystem::waitForLogin()
{
	// USER CAN NOW LOG IN

	cout << "LIBRARY SYSTEM" << endl;
	cout << "---------------------------------" << endl;
	cout << "Please enter a user ID to log in." << endl;
	cout << endl;

	//cin >> applicantId;

	long applicantId;
	string mystr;
	getline (cin, mystr);
	stringstream(mystr) >> applicantId;


	// CHECK GIVEN ID AGAINST THE LIST OF USERS.

	for(userIter = usersVect.begin(); userIter != usersVect.end(); userIter++)
	{
		MemberType mem;
		mem = *userIter;
		long uid;
		mem.getUserId    ( uid );

		if (uid == applicantId)
		{
			currentSysUser = mem;

			string fName;
			string lName;
			string auth;

			currentSysUser.getFirstName ( fName );
			currentSysUser.getLastName  ( lName );
			currentSysUser.getAuthority ( auth );

			if (auth == "staff" || auth == "STAFF" || auth == "Staff")
			{
				admin = true;
			}

			loggedIn = true;


			cout << "Logged in as " << fName << " " << lName << " ("<<auth<<")" << endl;
			cout << endl << endl;
		}
	}
}






		/**
		Display the main menu.  Arguments: none.
		\n
		*/
void LibSystem::displayMainMenu()
{

	cout << endl;

	cout << "MAIN MENU." << endl;
	cout << "------------------------------------------" << endl;
	cout << "Please enter a choice from the menu below." << endl;

	cout << endl;
	cout << "(1) Borrow book(s)"             << endl;
	cout << "(2) Return book(s)"             << endl;
	cout << "(3) Renew book(s)"              << endl;
	cout << "(4) Check current loans"        << endl;

	if(admin)
	{
		cout << endl;
		cout << "(5) Add books to the library"   << endl;
		cout << "(6) Add patrons to the library" << endl;
	}

	cout << endl;
	cout << "(7) Shut down system"           << endl;
	cout << endl;
	cout << "(9) Log out" << endl;

	if(admin)
	{
		cout << endl;
		cout << "(0) Restore system to default settings." << endl;
	}

	cout << endl;
	cout << endl;
	cout << endl;
}





		/**
		Set the borrowed date of the given BookLoan to today, and the due date to one month from now..  Arguments: BookLoan
		\n
		@param	theLoan	(BookLoan) The loan object that we want to renew.
		\n
		Sets the borrowed date to today, and the renewed date to today + 1 month.
		*/
void LibSystem::renewBookLoan(BookLoan & theLoan)
{

	long theKey;
	theLoan.getBookISBN(theKey);

	// Set the borrowed date to today.
	Date bDate;
	setToToday(bDate);
	theLoan.setBorrowedDate(bDate);

	// Set the due date to the borrowed date + 1 month
	unsigned mon;
	bDate.GetMonth(mon);
	++mon;
	if (mon == 13)
	{
		mon = 1;
	}
	bDate.SetMonth(mon);
	theLoan.setDueDate(bDate);

	// Update the BST of loans
	loans.replaceNode(theKey, theLoan); //search by key, then replace data of node if found.

	// NEED TO UPDATE LOANSVECT
}





		/**
		Renew book(s).  Arguments: none.
		\n
		Run the menu subsystem for renewing books.
		*/
void LibSystem::renewBook()
{

	string confirm;

	bool again = true;

	while(again)
	{
		bool userHasLoans = true;

		if (!loansVect.size())
		{
			userHasLoans = false;
		}

		if (!userHasLoans)
		{
			cout << "The current user does not have any books on loan." << endl;
			cout << endl;
			cout << "Please press ENTER to go back to the main menu." << endl;
			cout << endl;
			cout << endl;
			confirm = "";
			getline (cin, confirm);

			again = false;
			return;
		}

		// LIST ALL BOOKS ON LOAN TO THE CURRENT USER.

		unsigned currentLoans;
		currentLoans = 0;

		vector<BookType> loansToUser;
		vector<BookLoan> updateArr;
		vector<unsigned> updateIdxArr;

		cout << "Books on loan to the current user:";

		// For all loans
		vector<BookLoan>::iterator currentLoan;
		for(currentLoan = loansVect.begin(); currentLoan != loansVect.end(); currentLoan++)
		{
			BookLoan someLoan;
			someLoan = *currentLoan;

			long somePatronId;
			someLoan.getPatronId(somePatronId);

			long myPatronId;
			currentSysUser.getUserId(myPatronId);

			// This loan belongs to the current user.
			if (somePatronId == myPatronId)
			{
				// Get the isbn of the loan.
				long isbn;
				someLoan.getBookISBN(isbn);

				if (books.searchByKey(isbn))
				{
					// We have a book for the isbn of the loan.

					if(!currentLoans)
					{
						cout << endl;
					}

					updateIdxArr.push_back(currentLoans);
					currentLoans ++;

					// Retrieve the book details
					BookType b;
					books.getNodeValue(isbn, b);

					cout << endl;
					cout << "ITEM (" << currentLoans << ")" << endl;
					string spc;
					spc = "   ";

					cout << endl;
					///displayBookDetails(spc, b);
					displayLoanDetails(spc, someLoan); // calls displayBookDetails() and displayDate()

					loansToUser.push_back(b);
					updateArr.push_back(someLoan);
				}
			}
		}


		cout << endl;

		if (currentLoans)
		{
			cout << "Type the number of an ITEM to renew it." << endl;
			cout << "Or press ENTER to go back to the main menu." << endl;
			cout << endl;
			confirm = "";
			getline (cin, confirm);
			cout << endl;
			if(confirm.length())
			{
				stringstream ss;
				unsigned idx;
				ss << confirm;
				ss >> idx;
				idx -= 1; // menu is 1 based but we want 0 based.

				BookType bRet = loansToUser[idx];
				string spc;
				spc = "     ";
				cout << spc << "Book to renew: " << endl;
				cout << endl;
				cout << spc << "---------------" << endl;
				displayBookDetails(spc, bRet);
				cout << spc << "---------------" << endl;
				cout << endl;
				cout << spc << "Type (1) to confirm." << endl;
				cout << spc << "Or press ENTER to cancel." << endl;
				cout << endl;
				cout << spc;
				confirm = "";
				getline (cin, confirm);
				if(confirm.length())
				{
					// Change the date borrowed to today.
					// Set the due date to one month from today.

					BookLoan theLoan;
					theLoan = updateArr[idx];

					renewBookLoan(theLoan);

					// Update the loans vector.
					// Replace the existing loan value with the new one.
					unsigned vectIdx = updateIdxArr[idx];
					loansVect[vectIdx] = theLoan; // This should directly affect loansVect

					cout << endl;
					cout << endl;
					cout << "Book has been renewed. Please press ENTER." << endl;
					cout << endl;
					confirm = "";
					getline (cin, confirm);
					cout << endl;
					cout << endl;
				}
			}
			else
			{
				again = false;
				return;
			}
			// back to main menu
		}
		else
		{
			cout << "None." << endl;
			cout << endl;
			cout << endl;
			cout << "Please press ENTER to go back to the main menu." << endl;
			cout << endl;
			cout << endl;
			confirm = "";
			getline (cin, confirm);

			again = false;
			return;
		}
	}// again


}






		/**
		Run the main menu.  Arguments: none.
		\n
		Switch statement with loop. User may log out or shut down the system, or do things.
		*/
void LibSystem::mainMenuResponse()
{
	unsigned inputUint;
	string mystr;
	getline (cin, mystr);
	stringstream(mystr) >> inputUint;

	//cin >> inputUint;

	switch(inputUint)
	{
		case 0:
			if (admin)
			{
				cout << "(MAIN MENU) -> RESTORE SYSTEM TO DEFAULT SETTINGS" << endl;
				cout << "-----------------------------" << endl << endl;
				init(1);
				cout << "Library System has reverted to default settings." << endl;
				cout << "(Books, Users and Loans have all been affected.)" << endl;
				cout << endl;
				cout << "Press ENTER to return to the main menu." << endl;
				cout << endl;
				getline (cin, mystr);
				cout << endl;
				cout << endl;
			}
		break;



		case 1:
			// Borrow Book(s)
			cout << "(MAIN MENU) -> BORROW BOOK(s)" << endl;
			cout << "-----------------------------" << endl << endl;
			promptBorrowBook();
		break;

		case 2:
			// Return Book(s)
			cout << "(MAIN MENU) -> RETURN BOOK(s)" << endl;
			cout << "-----------------------------" << endl << endl;
			promptReturnBook();
		break;

		case 3:
			// Renew Book(s)
			cout << "(MAIN MENU) -> RENEW BOOK(s)" << endl;
			cout << "----------------------------" << endl << endl;
			renewBook();
		break;

		case 4:
			// Check current loans
			cout << "(MAIN MENU) -> CHECK CURRENT LOANS" << endl;
			cout << "----------------------------------" << endl << endl;
			showLoansForCurrentUser();
			cout << endl;
			cout << endl;
			cout << "Press ENTER to return to the main menu." << endl;
			cout << endl;
			getline (cin, mystr);
			cout << endl;
			cout << endl;
		break;


		case 5:
		if (admin)
		{
			// Add books to the library
			cout << "(MAIN MENU) -> ADD BOOK(s)" << endl;
			cout << "--------------------------" << endl << endl;
			staffAddBooks();
		}
		break;

		case 6:
		if (admin)
		{
			// Add patrons to the library
			cout << "(MAIN MENU) -> ADD PATRON(s)" << endl;
			cout << "----------------------------" << endl << endl;
			while(staffAddPatrons())
			{
				// add another patron
			}
		}
		break;

		case 7:
		//if (admin)
		//{
			// Shut down system
			cout << "Shutting down system." << endl;

			admin    = false;
			loggedIn = false;
			running  = false;

			if (!saveSystemData())// Save users, loans and books to the non-restore text files.
			{
				cout << endl;
				cout << endl;
				cout << "Failed to save settings.\n System will use the defaults next time it starts up." << endl;
				cout << endl;
				cout << "Press ENTER to finish." << endl;
				getline (cin, mystr);
				cout << endl;
				cout << endl;
			}
			else
			{
				cout << endl;
				cout << endl;
				cout << "Saved Book settings to " << BOOKFILE << endl;
				cout << "Saved User settings to " << USERFILE << endl;
				cout << "Saved Loan settings to " << LOANFILE << endl;
				cout << endl;
				cout << "   These settings will be loaded, next time the system starts up." << endl;
				cout << endl;
				cout << "Press ENTER to finish." << endl;
				getline (cin, mystr);
				cout << endl;
				cout << endl;
			}
		//}
		break;





		case 9:
			// Log out
			cout << "Logged out." << endl;
			admin    = false;
			loggedIn = false;
		break;
	}
}







		/**
		Display all books that are not currently on loan (to anyone).  Arguments: none.
		\n
		*/
void LibSystem::printAllVolumes()
{
	// We are searching every record, so we don't need bst features

	// Dump all books into a vector
	vector<BookType> allBks;
	books.inOrderDump(allBks);


	// For every book:
	vector<BookType>::iterator currBk;
	for(currBk = allBks.begin(); currBk != allBks.end(); currBk++)
	{

		// Get book
		BookType bk;
		bk = *currBk;

		// Get title
		string outStr;
		bk.getTitle(outStr);

		// Fetch the ISBN
		long volumeSearchKey = bookMap[outStr];

		if(!loans.isEmpty())
		{
			// There are loans
			if (!loans.searchByKey(volumeSearchKey))
			{
				//cout << "Available:      " << outStr << endl;
				cout << "     " << outStr << endl;
			}
			else
			{
				//cout << "loan:" << outStr << endl;
			}
		}
		else
		{
			// There are no loans
			cout << "     " << outStr << endl;
		}
	}
}




		/**
		Count how many books are available for loan.  Arguments: none.
		\n
		@return	unsigned	The number of books are available for loan.
		\n
		*/
unsigned LibSystem::availableCount()
{
	unsigned countOfAvailableBooks = 0;

	vector<BookType> allBks;
	books.inOrderDump(allBks);
	vector<BookType>::iterator currBk;

	// For every book:
	for(currBk = allBks.begin(); currBk != allBks.end(); currBk++)
	{
		// Fetch the ISBN of the book
		long volumeSearchKey;
		BookType bk;
		bk = *currBk;
		bk.getIsbn(volumeSearchKey);

		// Don't print items that are currently on loan.

		// If there are loans
		if(!loans.isEmpty())
		{
			// If there is no loan for this volume
			if (!loans.searchByKey(volumeSearchKey))
			{
				countOfAvailableBooks++;
			}
		}
		else
		{
			//There are no loans at the moment.
			countOfAvailableBooks++;
		}
	}
	return countOfAvailableBooks;
}





		/**
		Check if the given ISBN is for a book that is on loan.  Arguments: long
		\n
		@param	isbn	(long) The ISBN of a book that we want to check.
		\n
		@return	bool	True if the book with the given ISBN is on loan.
		\n
		*/
bool LibSystem::isLoaned(long & isbn)
{
	// If there are loans
	if(!loans.isEmpty())
	{
		return loans.searchByKey(isbn);
	}
	return false;
}





		/**
		Set the given date object to today.  Arguments: Date
		\n
		@param	someDate	(Date) A date object.
		\n
		*/
void LibSystem::setToToday(Date & someDate)
{
	// Get the current time.

	time_t timeMs1970;
	struct tm * theTime;
	time ( &timeMs1970 );
	theTime = localtime ( &timeMs1970 );

	unsigned day = 			(unsigned)theTime->tm_mday;		// tm struct gives day of the month		1-31
	unsigned mon = 1 + 		(unsigned)theTime->tm_mon;		// tm struct gives months since January	0-11
	unsigned yr  = 1900 + 	(unsigned)theTime->tm_year;		// tm struct gives years since 1900

	someDate.SetDayOfMonth(day);
	someDate.SetMonth(mon);
	someDate.SetYear(yr);
}


		/**
		Menu Subsystem for borrowing books.  Arguments: none.
		\n
		*/
void LibSystem::promptBorrowBook()
{
	bool again = true;
	string confirm;

	while(again)
	{
		if (availableCount() < 1)
		{
			cout << endl;
			cout << endl;
			cout << "   Sorry, no books are currently available." << endl;
			cout << endl;
			cout << endl;
			cout << "   Please press RETURN." << endl;
			confirm = "";
			getline (cin, confirm);
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;

			again = false;
		}
		else
		{
			// books are available
			cout << "The following volumes are available for borrowing." << endl << endl;

			printAllVolumes();

			string requestedTitle;

			cout << endl;
			cout << "Please enter the title of a volume that you would like to borrow," << endl << endl;
			cout << "Or RETURN, to cancel." << endl;
			cout << endl;
			cout << endl;
			getline (cin, requestedTitle);


			if (requestedTitle.length())
			{
				long bisbn;
				bisbn = bookMap[requestedTitle];

				if (bisbn)
				{
					// Confirm borrowing of book.

					cout << endl;
					cout << "You entered " << requestedTitle << "  isbn: " << bisbn << endl;
					cout << endl;

					if (isLoaned(bisbn))
					{
						cout << "   Sorry, that book is currently on loan." << endl;
						cout << "   There is currently no facility available to reserve it either." << endl;
						cout << endl;
						cout << endl;
						cout << "   Please press RETURN." << endl;
						cout << endl;
						cout << endl;
						confirm = "";
						getline (cin, confirm);
						cout << endl;
						cout << endl;
						cout << endl;
						cout << endl;
					}
					else
					{
						cout << "   Press (1) to borrow this book," << endl;
						cout << "   Or RETURN, to cancel." << endl << endl;
						cout << endl;
						confirm = "";
						getline (cin, confirm);

						if (confirm.length())
						{
							// Borrow the book.

							long currId;
							currentSysUser.getUserId(currId);

							Date today;
							Date dueBack;

							setToToday(today);
							setToToday(dueBack);

							unsigned mm;
							dueBack.GetMonth(mm);
							mm ++;
							if (mm == 13)
							{
								mm = 1;
							}
							dueBack.SetMonth(mm);

							BookLoan bloan;
							bloan.setBookISBN(bisbn);
							bloan.setPatronId(currId);
							bloan.setBorrowedDate(today);
							bloan.setDueDate(dueBack);

							loans.insert(bloan);		// Insert into bst
							loansVect.push_back(bloan);	// Insert into loansVect

							// Any books left?
							cout << endl;
							if (availableCount())
							{
								cout << "Borrow another book? (y/n)" << endl;
								cout << endl;
								confirm = "";
								getline (cin, confirm);
							}
							else
							{
								cout << "No books left." << endl;
								again = false; // Done borrowing books.
								cout << endl;
							}
							cout << endl;
							cout << endl;
							cout << endl;

							if (!confirm.length() || confirm == "n" || confirm == "N" || confirm == "no" || confirm == "NO" || confirm == "No")
							{
								again = false; // Done borrowing books.
							}
						}
						else
						{
							again = false; // Done borrowing books.
						}
					}

				}
				else
				{
					cout << endl;
					cout << endl;
					cout << endl;
					cout << endl;
					cout << "Sorry, there is no book by that title." << endl << endl;
				}
			}
			else
			{
				again = false; // Done borrowing books.
			}
		}
	}
}




		/**
		Show all the loans belonging to the current user.  Arguments: none.
		\n
		*/
void LibSystem::showLoansForCurrentUser()
{
	unsigned currentLoans = 0;

	// For all loans
	vector<BookLoan>::iterator currentLoan;
	for(currentLoan = loansVect.begin(); currentLoan != loansVect.end(); currentLoan++)
	{
		BookLoan someLoan;
		someLoan = *currentLoan;

		long somePatronId;
		someLoan.getPatronId(somePatronId);

		long myPatronId;
		currentSysUser.getUserId(myPatronId);

		// This loan belongs to the current user.
		if (somePatronId == myPatronId)
		{
			// Get the isbn of the loan.
			long isbn;
			someLoan.getBookISBN(isbn);

			if (books.searchByKey(isbn))
			{
				// We have a book for the isbn of the loan.
				currentLoans ++;
				cout << endl;
				cout << "ITEM (" << currentLoans << ")" << endl;
				string spc;
				spc = "   ";
				cout << endl;
				displayLoanDetails(spc, someLoan); // calls displayBookDetails() and displayDate()
			}
		}
	}
}





		/**
		Display the details of a given BookLoan.  Arguments: string, BookLoan
		\n
		@param	spacer	(string) 	Used to format output nicely.
		\n
		@param	b		(BookLoan) 	The BookLoan that we want to display.
		\n
		Calls displayBookDetails() and also displayDate().
		*/
void LibSystem::displayLoanDetails(string spacer, const BookLoan & b) const
{
	long theIsbn;
	long patId;
	Date borDate;
	Date dueDate;

	string e = "";

	b.getBookISBN(theIsbn);
	b.getPatronId    ( patId);
	b.getBorrowedDate( borDate);
	b.getDueDate     ( dueDate);

	BookType theBook;
	books.getNodeValue(theIsbn, theBook);

	cout << spacer << "Book details:" << endl;

	string spacer2(spacer);
	spacer2.append("   ");

	displayBookDetails(spacer2, theBook);

	cout << endl;
	cout << spacer  << "Loan details: " << endl;
	cout << spacer2 << "ISBN        : " << theIsbn << endl;
	cout << spacer2 << "borrower ID : " << patId << endl;

	cout << spacer2 << "Borrowed    : ";
	displayDate(e, borDate);

	cout << spacer2 << "Due         : ";
	displayDate(e, dueDate);

}



		/**
		Display the details of a Date, using a descriptive string for the month.  Arguments: string, Date
		\n
		@param	spacer	(string) 	Used to format output nicely.
		\n
		@param	d		(Date) 		The Date object that we want to display.
		\n
		*/
void LibSystem::displayDate(string spacer, const Date & d) const
{
	unsigned dd;
	string mstr;
	unsigned yyyy;

	d.GetDayOfMonth(dd);
	d.GetMonthStr(mstr);
	d.GetYear(yyyy);

	cout << spacer << dd << " " << mstr << " " << yyyy << endl;
}







		/**
		Display the details of a given book.  Arguments: string, BookType
		\n
		@param	spacer	(string) 	Used to format output nicely.
		\n
		@param	b		(BookType) 	The book object that we want to display.
		\n
		*/
void LibSystem::displayBookDetails(string spacer, const BookType & b) const
{
	string   volumeTitle;
	string   volumePublisher;
	long     volumeIsbn;
	double   volumePrice;
	unsigned volumeCopies;
	unsigned volumeAuthCount;

	b.getTitle(volumeTitle);
	b.getNumberOfAuthors(volumeAuthCount);
	b.getPublisher(volumePublisher);
	b.getIsbn(volumeIsbn);
	b.getPrice(volumePrice);
	b.getNumberOfCopiesInStock(volumeCopies);

	cout << spacer << "Title        : " << volumeTitle << endl;
	cout << spacer << "#Authors     : " << volumeAuthCount << endl;

	string authorName;
	for(unsigned aaa = 0; aaa < volumeAuthCount; aaa++)
	{
		b.getAuthorAt(authorName, aaa);
		cout << spacer << " Author " << (aaa + 1) << "    : " << authorName << ",   " << endl;
	}

	cout << spacer << "Publisher    : " << volumePublisher	<< endl;
	cout << spacer << "ISBN         : " << volumeIsbn			<< endl;
	cout << spacer << "Price        : " << volumePrice		<< endl;
	cout << spacer << "Copies       : " << volumeCopies		<< endl;
	//cout << endl;
}








		/**
		Menu subsystem to allow the user to return book(s).  Arguments: none.
		\n
		*/
void LibSystem::promptReturnBook()
{
	string confirm;

	bool again = true;

	vector<vector<BookLoan>::iterator> deletionIterators;


	while(again)
	{
		bool userHasLoans = true;

		if (!loansVect.size())
		{
			userHasLoans = false;
		}

		if (!userHasLoans)
		{
			cout << "The current user does not have any books on loan." << endl;
			cout << endl;
			cout << "Please press ENTER to go back to the main menu." << endl;
			cout << endl;
			cout << endl;
			confirm = "";
			getline (cin, confirm);

			again = false;
			return;
		}

		// LIST ALL BOOKS ON LOAN TO THE CURRENT USER.

		unsigned currentLoans;
		currentLoans = 0;

		vector<BookType> loansToUser;
		vector<BookLoan> delArr;

		cout << "Books on loan to the current user:";

		// For all loans
		vector<BookLoan>::iterator currentLoan;
		for(currentLoan = loansVect.begin(); currentLoan != loansVect.end(); currentLoan++)
		{
			BookLoan someLoan;
			someLoan = *currentLoan;

			long somePatronId;
			someLoan.getPatronId(somePatronId);

			long myPatronId;
			currentSysUser.getUserId(myPatronId);

			// This loan belongs to the current user.
			if (somePatronId == myPatronId)
			{
				// Get the isbn of the loan.
				long isbn;
				someLoan.getBookISBN(isbn);

				if (books.searchByKey(isbn))
				{
					// We have a book for the isbn of the loan.

					if(!currentLoans)
					{
						cout << endl;
					}

					currentLoans ++;

					// Retrieve the book details
					BookType b;
					books.getNodeValue(isbn, b);

					cout << endl;
					cout << "ITEM (" << currentLoans << ")" << endl;
					string spc;
					spc = "   ";

					cout << endl;
					///displayBookDetails(spc, b);
					displayLoanDetails(spc, someLoan); // calls displayBookDetails() and displayDate()

					loansToUser.push_back(b);
					delArr.push_back(someLoan);
					deletionIterators.push_back(currentLoan);
				}
			}
		}


		cout << endl;

		if (currentLoans)
		{
			cout << "Type the number of an ITEM to return it." << endl;
			cout << "Or press ENTER to go back to the main menu." << endl;
			cout << endl;
			confirm = "";
			getline (cin, confirm);
			cout << endl;
			if(confirm.length())
			{
				stringstream ss;
				unsigned idx;
				ss << confirm;
				ss >> idx;

				BookType bRet = loansToUser[idx - 1];
				string spc;
				spc = "     ";
				cout << spc << "Book to return: " << endl;
				cout << endl;
				cout << spc << "---------------" << endl;
				displayBookDetails(spc, bRet);
				cout << spc << "---------------" << endl;
				cout << endl;
				cout << spc << "Type (1) to confirm." << endl;
				cout << spc << "Or press ENTER to cancel." << endl;
				cout << endl;
				cout << spc;
				confirm = "";
				getline (cin, confirm);
				if(confirm.length())
				{
					// Delete from BST
					BookLoan l;
					l = delArr[idx - 1];
					loans.deleteNode(l);

					// Delete from loans vector.
					vector<BookLoan>::iterator deletionIter;
					deletionIter = deletionIterators[idx - 1];
					loansVect.erase(deletionIter);

					cout << endl;
					cout << endl;
					cout << "Book has been returned." << endl;
					cout << endl;
					cout << endl;
				}
			}
			else
			{
				again = false;
				return;
			}
			// back to main menu
		}
		else
		{
			cout << "None." << endl;
			cout << endl;
			cout << endl;
			cout << "Please press ENTER to go back to the main menu." << endl;
			cout << endl;
			cout << endl;
			confirm = "";
			getline (cin, confirm);

			again = false;
			return;
		}
	}// again
}











		/**
		Menu subsystem to allow the user to add book(s) to the library.  Arguments: none.
		\n
		*/
void LibSystem::staffAddBooks()
{
	bool again = true;

	while(again)
	{
		BookType book;

		string mystr;

		string title;
		string publisher;
		long isbn;
		double price;
		unsigned numberOfCopiesInStock;
		unsigned numberOfAuthors;

		cout << "Enter title of book:";
		getline (cin, title);
		//stringstream(mystr) >> title;

		cout << endl;
		cout << "Enter publisher:";
		getline (cin, publisher);
		//stringstream(mystr) >> publisher;

		cout << endl;
		cout << "Enter ISBN:";
		getline (cin, mystr);
		stringstream(mystr) >> isbn;

		cout << endl;
		cout << "Enter price:";
		getline (cin, mystr);
		stringstream(mystr) >> price;

		cout << endl;
		cout << "Enter number of copies available:";
		getline (cin, mystr);
		stringstream(mystr) >> numberOfCopiesInStock;

		cout << endl;
		cout << "Enter number of authors:";
		getline (cin, mystr);
		stringstream(mystr) >> numberOfAuthors;

		if (numberOfAuthors > 4)
		{
			cout << "Enter number of authors has been set to 4 (max)";
			numberOfAuthors = 4;
		}

		book.setTitle                 ( title);
		book.setPublisher             ( publisher);
		book.setIsbn                  ( isbn);
		book.setPrice                 ( price);
		book.setNumberOfCopiesInStock ( numberOfCopiesInStock);
		book.setNumberOfAuthors       ( numberOfAuthors);

		string auth;
		for(unsigned aaaa = 0; aaaa < numberOfAuthors; aaaa++)
		{
			cout << endl;
			cout << "Enter author ("<<(aaaa+1)<<"): ";
			getline (cin, auth);
			//stringstream(mystr) >> auth;
			book.setAuthorAt ( auth, aaaa);
		}
		// Finished manual construction of book.



		// Show the book details
		cout << endl;
		cout << endl;
		string spc = "     ";
		cout << spc << "Finished entering book details: " << endl;
		cout << endl;
		cout << spc << "---------------" << endl;
		displayBookDetails(spc, book);
		cout << spc << "---------------" << endl;



		string confirm = "";
		while(!confirm.length())
		{
			// Ask to commit.
			cout << "Do you want to add this book to the library? (y/n)" << endl;
			cout << endl;
			confirm = "";
			getline (cin, confirm);
			if (confirm == "y" || confirm == "Y" || confirm == "yes" || confirm == "YES" || confirm == "Yes")
			{
				// Commit
				books.insert(book);
				bookMap[title] = isbn;
				cout << "Book has been added to the library." << endl;
				cout << endl;
			}
			else
			{
				// Discard
				cout << "New book details have been discarded." << endl;
				cout << endl;
			}
		}


		cout << endl;
		cout << endl;
		cout << "Add another book? (y/n)" << endl;
		cout << endl;
		confirm = "";
		getline (cin, confirm);
		if (!confirm.length() || confirm == "n" || confirm == "N" || confirm == "no" || confirm == "NO" || confirm == "No")
		{
			again = false; // Done borrowing books.
		}
		cout << endl;
		cout << endl;
		cout << endl;
	}
}




		/**
		Find if the given ID belongs to an existing system user.  Arguments: long
		\n
		@param	applicantId	(long) the User ID of the patron / staff member we are searching for.
		\n
		@return	(true) 		if the given ID belongs to an existing system user
		\n
		*/
bool LibSystem::userExists(const long applicantId) const
{
	vector<MemberType>::const_iterator cIter;

	for(cIter = usersVect.begin(); cIter != usersVect.end(); cIter++)
	{
		MemberType mem;
		mem = *cIter;
		long uid;
		mem.getUserId(uid);

		if (uid == applicantId)
		{
			return true;
		}
	}
	return false;
}






		/**
		Menu subsystem to allow the user to add patrons to the library.  Arguments: none.
		\n
		*/
bool LibSystem::staffAddPatrons()
{
	bool again = true;

	while(again)
	{
		string mystr;

		MemberType patron;

		string firstName;
		string lastName;
		long userId;
		string authorisationLevel;



		// Get the new user details.

		// Get a user ID that is not already taken.
		//////////////////////////////////////////////
		do
		{
			cout << "Please provide a numeric ID\n(one that is not already taken)\nfor this new Patron:";
			getline (cin, mystr);
			if (!mystr.length())
			{
				again = false;
				return true;  // Back to top of function.
			}
			stringstream(mystr) >> userId;
		}
		while (userExists(userId));
		cout << endl;




		// staff or regular user
		//////////////////////////////////////////////
		bool authGood = false;
		do
		{

			cout << "Select authorisation level:" << endl;
			cout << "     (1) Regular User" << endl;
			cout << "     (2) Library Staff" << endl;
			cout << "     " << endl;
			getline (cin, mystr);
			if (mystr == "1")
			{
				authorisationLevel = "patron";
				authGood = true;
			}
			else if (mystr == "2")
			{
				authorisationLevel = "staff";
				authGood = true;
			}
			cout << endl;
		}
		while(!authGood);




		//////////////////////////////////////////////
		do
		{
			cout << "Enter first name:";
			getline (cin, firstName);
			cout << endl;
		}
		while(!firstName.length());



		//////////////////////////////////////////////
		do
		{
			cout << "Enter last name:";
			getline (cin, lastName);
			cout << endl;
		}
		while(!lastName.length());



		// Construct the new user
		//////////////////////////////////////////////
		patron.setFirstName(firstName);
		patron.setLastName(lastName);
		patron.setUserId(userId);
		patron.setAuthority(authorisationLevel);


		//////////////////////////////////////////////
		// Finished manual construction of MemberType.
		//////////////////////////////////////////////





		// Show the patron details
		//////////////////////////////////////////////
		cout << endl;
		cout << endl;
		string spc = "     ";
		cout << spc << "Finished entering patron details: " << endl;
		cout << endl;
		cout << spc << "---------------" << endl;
		cout << spc << " First Name:          " << firstName          << endl;
		cout << spc << " Last Name:           " << lastName           << endl;
		cout << spc << " User Id:             " << userId             << endl;
		cout << spc << " Authorisation Level: " << authorisationLevel << endl;
		cout << spc << "---------------" << endl;
		cout << endl;






		string confirm = "";
		while(!confirm.length())
		{
			// Ask to commit.
			cout << "Do you want to add this patron to the system? (y/n)" << endl;
			cout << endl;
			confirm = "";
			getline (cin, confirm);
		}
		if (confirm == "y" || confirm == "Y" || confirm == "yes" || confirm == "YES" || confirm == "Yes")
		{
			// Commit
			usersVect.push_back(patron);
			cout << "Patron has been added to the system." << endl;
			cout << endl;
		}
		else
		{
			// Discard
			cout << "New patron details have been discarded." << endl;
			cout << endl;
		}


		cout << endl;
		cout << endl;
		cout << "Add another patron? (y/n)" << endl;
		cout << endl;
		confirm = "";
		getline (cin, confirm);
		if (!confirm.length() || confirm == "n" || confirm == "N" || confirm == "no" || confirm == "NO" || confirm == "No")
		{
			again = false; // Done adding patrons.
		}
		cout << endl;
		cout << endl;
		cout << endl;
	}
	return false;
}



		/**
		Run the main menu.  Arguments: none.
		*/
void LibSystem::run()
{

	running = true;

	loggedIn = false;

	admin = false;


	while(running)
	{

		if (!loggedIn)
		{
			// NOT LOGGED IN

			displayWelcomeMessage();

			displayAllUsers();

			waitForLogin();

		}
		else
		{
			// LOGGED IN

			displayMainMenu();

			mainMenuResponse();

		}
	}
}
