# Library-Book-Loan-system

This is a C++ application, which allows the user to browse, borrow and return library books.

Upon starting this program, you will see a console application with the following prompt:

```
Welcome to the library system.

There are currently no account passwords in use,
so that you can log in simply.

Registered users:

   FirstName    LastName          ID  MemberType

        Mike        Gell          12       staff
         Ted    Laurence          13      patron
         Meg       March          14      patron
        Hans      Zimmer          15       staff
       Homer     Simpson          16      patron

LIBRARY SYSTEM
---------------------------------
Please enter a user ID to log in.
```

If you enter 12 and press RETURN, you will see the following screen.

```
MAIN MENU.
------------------------------------------
Please enter a choice from the menu below.

(1) Borrow book(s)
(2) Return book(s)
(3) Renew book(s)
(4) Check current loans

(5) Add books to the library
(6) Add patrons to the library

(7) Shut down system

(9) Log out

(0) Restore system to default settings.
```

If you enter 1 and press RETURN, you will see the following.

```
(MAIN MENU) -> BORROW BOOK(s)
-----------------------------

The following volumes are available for borrowing.

     Awesome Book
     How To Read Books
     The Infinity
     Computerness
     Mass Charge
     The Awakening
     The Exiles

Please enter the title of a volume that you would like to borrow,

Or RETURN, to cancel.
```

Type 'The Awakening' and press RETURN

```
You entered The Awakening  isbn: 666

   Press (1) to borrow this book,
   Or RETURN, to cancel.
```

Press 1

```
Borrow another book? (y/n)
```

Press n

```
MAIN MENU.
------------------------------------------
Please enter a choice from the menu below.

(1) Borrow book(s)
(2) Return book(s)
(3) Renew book(s)
(4) Check current loans

(5) Add books to the library
(6) Add patrons to the library

(7) Shut down system

(9) Log out

(0) Restore system to default settings.
```

Press 4

```
(MAIN MENU) -> CHECK CURRENT LOANS
----------------------------------


ITEM (1)

   Book details:
      Title        : Falcon
      #Authors     : 1
       Author 1    : Sprue Nanning,
      Publisher    : Oreilly
      ISBN         : 777
      Price        : 77.50
      Copies       : 3

   Loan details:
      ISBN        : 777
      borrower ID : 12
      Borrowed    : 28 August 2010
      Due         : 28 September 2010

ITEM (2)

   Book details:
      Title        : The Awakening
      #Authors     : 1
       Author 1    : Sprue Nanning,
      Publisher    : Oreilly
      ISBN         : 666
      Price        : 66.50
      Copies       : 1

   Loan details:
      ISBN        : 666
      borrower ID : 12
      Borrowed    : 30 July 2025
      Due         : 30 August 2025


Press ENTER to return to the main menu.
```

The system also allows you to return and renew book loans, and add books / patrons to the system.

### Download

To download and run this program, please see [Library-Book-Loan-system-Executable](https://github.com/gellmr/Library-Book-Loan-system-Executable)
