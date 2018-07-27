/**
\file		main.cpp
\n
\brief		Entry point to the program
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/



#include "h/LibSystem.h"


using namespace std;






		/**
		Entry point to the program.  Arguments: none.
		\n
		@return	(int) Operating System thingy.
		\n
		*/
int main()
{

	LibSystem system;

	if(system.init(0))
	{
		system.run();
	}

	return 0;
}
