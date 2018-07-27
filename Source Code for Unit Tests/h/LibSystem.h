/**
\file		LibSystem.h
\brief		LibSystem class definition.
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/


#if !defined(_LIB_SYSTEM_H)
#define _LIB_SYSTEM_H

#include <string>
#include <vector>
#include <map>

#include "../h/BookType.h"
#include "../h/BookLoan.h"
#include "../h/MemberType.h"
#include "../h/BinarySearchTree.h"

using namespace std;




		/**
		\class LibSystem.
		\brief This is the main client program for the library system, and handles all user interaction / menus.
		*/
class LibSystem
{

public:

			/**	\brief
			Default Constructor. \n*/
	LibSystem();

			/**	\brief
			Destructor. \n*/
	~LibSystem();


			/**	\brief
			Initialize the library system, optionally restoring default settings. \n*/
	bool init(const bool restoreSystemDefaults);



			/**	\brief
			Save the current state of the system (to text files on the local hard drive). \n*/
	bool saveSystemData();



			/**	\brief
			Prints a welcom message to the screen. \n*/
	void displayWelcomeMessage();



			/**	\brief
			Displays a list of all the registered users of the system. \n*/
	void displayAllUsers();



			/**	\brief
			Returns true if the given user ID matches an existing user record. \n*/
	bool userExists(const long applicantId) const;



			/**	\brief
			Wait for a user to login. \n*/
	void waitForLogin();



			/**	\brief
			Display the main menu of options. \n*/
	void displayMainMenu();



			/**	\brief
			Respond to the user's choice of main menu option. \n*/
	void mainMenuResponse();



			/**	\brief
			Print all books that are not currently on loan. \n*/
	void printAllVolumes();



			/**	\brief
			Returns a count of the number of books that are not currently on loan. \n*/
	unsigned availableCount();



			/**	\brief
			Given the ISBN of a book, returns true if that book is currently on loan (to any user). \n*/
	bool isLoaned(long & isbn);



			/**	\brief
			Display the menu subsystem for borrowing book(s). \n*/
	void promptBorrowBook();



			/**	\brief
			Display the details of a given book. \n*/
	void displayBookDetails(string spacer, const BookType & b) const;




			/**	\brief
			Show the loans for the user who is currently logged into the system. \n*/
	void showLoansForCurrentUser();



			/**	\brief
			Show the details of a given loan. \n*/
	void displayLoanDetails(string spacer, const BookLoan & b) const;



			/**	\brief
			Given a loan object, renew its borrowed / due dates. \n*/
	void renewBookLoan(BookLoan & theLoan);



			/**	\brief
			Set the given date to today's date. \n*/
	void setToToday(Date & someDate);



			/**	\brief
			Display the given date. \n*/
	void displayDate(string spacer, const Date & d) const;



			/**	\brief
			Show the menu subsystem for returning book(s). \n*/
	void promptReturnBook();



			/**	\brief
			Show the menu subsystem for renewing book(s). \n*/
	void renewBook();



			/**	\brief
			Show the menu subsystem for adding new book(s) to the library. \n*/
	void staffAddBooks();




			/**	\brief
			Show the menu subsystem for adding new user(s) to the library. \n*/
	bool staffAddPatrons();



			/**	\brief
			Run the library system. \n*/
	void run();




private:



			/**	\brief
			Used for finding an ISBN when you only know the book title. \n*/
	map<string, long> bookMap;



			/**	\brief
			Stores all the books in the library system, organised into a searchable structure. \n*/
	BinarySearchTree<BookType> books;



			/**	\brief
			Stores all the loans in the library system, organised into a searchable structure. \n*/
	BinarySearchTree<BookLoan> loans;



			/**	\brief
			Stores all the loans in the library system, organised in a linear structure. \n*/
	vector<BookLoan> loansVect;



			/**	\brief
			Stores all the users in the library system, organised in a linear structure. \n*/
	vector<MemberType> usersVect;



			/**	\brief
			Iterator for traversing the list of library users. \n*/
	vector<MemberType>::iterator userIter;



			/**	\brief
			Indicates if the current user has admin rights (is a staff member). \n*/
	bool admin;



			/**	\brief
			Indicates if anyone is logged in at the moment. \n*/
	bool loggedIn;



			/**	\brief
			Indicates if the library system is running. \n*/
	bool running;



			/**	\brief
			The user who is currently logged in. \n*/
	MemberType currentSysUser;



			/**	\brief
			Contains the (relative) file path of the text file for storing all book data. \n*/
	string BOOKFILE;


			/**	\brief
			Contains the (relative) file path of the text file for storing all user data. \n*/
	string USERFILE;


			/**	\brief
			Contains the (relative) file path of the text file for storing all loan data. \n*/
	string LOANFILE;



			/**	\brief
			Contains the (relative) file path of the text file for storing all BACKUP book data. \n*/
	string BOOK_RESTORE_FILE;


			/**	\brief
			Contains the (relative) file path of the text file for storing all BACKUP user data. \n*/
	string USER_RESTORE_FILE;


			/**	\brief
			Contains the (relative) file path of the text file for storing all BACKUP loan data. \n*/
	string LOAN_RESTORE_FILE;
};

#endif
