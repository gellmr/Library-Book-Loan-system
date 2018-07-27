/**
\file		BinarySearchTree.h
\brief		BinarySearchTree class definition and implementation
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/

#if !defined(_BINARY_SEARCH_TREE_H)
#define _BINARY_SEARCH_TREE_H

#include <vector>

#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>

#include "../h/SimpleBinaryTree.h"
#include "../h/Searchable.h"



using namespace std;


		/**
		\class BinarySearchTree
		\brief A templated tree to perform a binary search, with some extra features to search by a key (long) and to return a node's data, or replace a specified node.

		Derived from SimpleBinaryTree, implementing its abstract methods.
		*/
template <class T>
class BinarySearchTree : public SimpleBinaryTree<T>
{
public:

			/**	\brief
			Default Constructor. \n*/
	BinarySearchTree();


			/**	\brief
			Copy Constructor. \n*/
	BinarySearchTree(const BinarySearchTree<T> & otherTree);


			/**	\brief
			Destructor. \n*/
	~BinarySearchTree();


			/**	\brief
			Assignment Operator override. \n*/
	const BinarySearchTree& operator=(const BinarySearchTree<T> & otherTree);


			/**	\brief
			Search for the given item, returns true if found. \n*/
	bool search(const T& searchItem) const;



			/**	\brief
			Get the value of the node found using the given search key (long). \n*/
	void getNodeValue(const long & searchKey, T & outNode) const;



			/**	\brief
			Search the binary search tree, using the given search key (long), returns true if found. \n*/
	bool searchByKey(const long & searchKey) const;



			/**	\brief
			Search for a node matching the given key (long), and replace it's data with the given node data value, returning true if successful. \n*/
	bool replaceNode(const long & searchKey, const T & nodeData);



			/**	\brief
			Insert the given item into the search tree, creating a new node if successful, but aborting if a duplicate is found in the tree. \n*/
	void insert(const T & dataToInsert);


			/**	\brief
			If a node with the same data as the given item is found, it is deleted from the binary search tree. \n

			If the binary search tree is empty or deleteItem is not in the tree, a message is printed.*/
	void deleteNode(const T & deleteItem);


			/**	\brief
			Perform an in-order traversal of the tree, outputting its contents to the given vector. \n*/
	void inOrderDump(vector<T> & vect) const;

			/**	\brief
			Perform a pre-order traversal of the tree, outputting its contents to the given vector. \n*/
	void preOrderDump(vector<T> & vect) const;

			/**	\brief
			Perform a post-order traversal of the tree, outputting its contents to the given vector. \n*/
	void postOrderDump(vector<T> & vect) const;

private:


			// Helper:
			// CORRECT:                       var is a reference to a pointer to an int that is const.
			//    void methodA( const int * & var );

			// Helper:
			// MEANINGLESS:     you cannot have a pointer to a reference.
			//    void methodA( int & * var);


			/**	\brief
			Delete (from the binary search tree) the node to which p points. \n*/
	void deleteFromTree(nodeType<T> * & p);




			/**	\brief
			Perform an in-order traversal, printing each node to a T vector. \n*/
	void fillVectorInOrder(vector<T> & vect, nodeType<T> * p) const;


			/**	\brief
			Perform a pre-order traversal, printing each node to a T vector. \n*/
	void fillVectorPreOrder(vector<T> & vect, nodeType<T> * p) const;


			/**	\brief
			Perform a post-order traversal, printing each node to a T vector. \n*/
	void fillVectorPostOrder(vector<T> & vect, nodeType<T> * p) const;


};


// There is no .cpp file, because this is a template.



#include <math.h>



using namespace std;





		/**
		Default Constructor.
		*/
template <class T>
BinarySearchTree<T>::BinarySearchTree()
{

}








		/**
		Copy Constructor.  Argument: BinarySearchTree<T>
		\n
		@param	otherTree	The tree we are copying to this object.
		\n
		*/
template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> & otherTree)
{
}



		/**
		Destructor
		*/
template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{

}



		/**
		Assignment Operator override.  Argument: BinarySearchTree<T>
		\n
		@param	otherTree	The tree we are copying to this object.
		\n
		*/
template <class T>
const BinarySearchTree<T> & BinarySearchTree<T>::operator=(const BinarySearchTree<T> & otherTree)
{
}




		/**
		Get the value of the specified node.  Arguments: long, T
		\n
		@param	searchKey	(long) the value used for searching through the nodes of the tree.
		\n
		@param	outNode		(T) receives the value of the node when found.
		\n
		Search the binary search tree for a T with the given key (long).
		Gets the value of the node data T, if found.
		*/
template <class T>
void BinarySearchTree<T>::getNodeValue(const long & searchKey, T & outNode) const
{
	nodeType<T> * current;
	bool found = false;

	if (this->root == 0)
	{
		cout << "Cannot search an empty tree." << endl;
	}
	else
	{
		// Tree is not empty...

		current = this->root;

		while(   (current != 0) && !(found)   )
		{
			// Keep searching...

			// Get the search key for the current item
			T currentItem = current->data;


			// Not sure how to enforce that T is required to implement Searchable.

			long itemKey;
			itemKey = currentItem.getKey(); // gets the ISBN value from the BookType or BookLoan object.

			// Compare key
			if (itemKey == searchKey)
			{
				// Found at this node.
				found = true;
				outNode = currentItem;
				return;
			}
			else if (itemKey > searchKey)
			{
				// Search left subtree
				current = current->left;
			}
			else
			{
				// Search right subtree
				current = current->right;
			}
		}	// end while
	}		// end else
}






		/**
		Replace the value of the specified node.  Arguments: long, T
		\n
		@param	searchKey	(long) the value used for searching through the nodes of the tree.
		\n
		@param	nodeData	(T) the replacement value for the node if found.
		\n
		Search for a node matching the given key (long), and replace it's data with the given node data value.
		Returns true if successful.
		*/
template <class T>
bool BinarySearchTree<T>::replaceNode(const long & searchKey, const T & nodeData)
{
	bool found = false;

	nodeType<T> * current;


	if (this->root == 0)
	{
		cout << "Cannot search an empty tree." << endl;
	}
	else
	{
		// Tree is not empty...

		current = this->root;

		while(   (current != 0) && !(found)   )
		{
			// Keep searching...

			// Get the search key for the current item
			T currentItem = current->data;


			// Not sure how to enforce that T is required to implement Searchable.

			long itemKey;
			itemKey = currentItem.getKey(); // gets the ISBN value from the BookType or BookLoan object.

			// Compare key
			if (itemKey == searchKey)
			{
				// Found at this node.
				// Replace node data
				current->data = nodeData;
				found = true;
			}
			else if (itemKey > searchKey)
			{
				// Search left subtree
				current = current->left;
			}
			else
			{
				// Search right subtree
				current = current->right;
			}
		}	// end while
	}		// end else

	return found;
}







		/**
		Search the tree using the specified key (long).  Arguments: long
		\n
		@param	searchKey	(long) the value used for searching through the nodes of the tree.
		\n
		@return	true if found.
		\n
		Search the binary search tree for a T with the given key.
		*/
template <class T>
bool BinarySearchTree<T>::searchByKey(const long & searchKey) const
{
	nodeType<T> * current;
	bool found = false;

	if (this->root == 0)
	{
		cout << "Cannot search an empty tree." << endl;
	}
	else
	{
		// Tree is not empty...

		current = this->root;

		while(   (current != 0) && !(found)   )
		{
			// Keep searching...

			// Get the search key for the current item
			T currentItem = current->data;


			// Not sure how to enforce that T is required to implement Searchable.

			long itemKey;
			itemKey = currentItem.getKey(); // gets the ISBN value from the BookType or BookLoan object.

			// Compare key
			if (itemKey == searchKey)
			{
				// Found at this node.
				found = true;
			}
			else if (itemKey > searchKey)
			{
				// Search left subtree
				current = current->left;
			}
			else
			{
				// Search right subtree
				current = current->right;
			}
		}	// end while
	}		// end else

	return found;
}







		/**
		Search the tree using the specified item (T).  Arguments: T
		\n
		@param	searchItem	(T) the item used for searching through the nodes of the tree.
		\n
		@return	true if found.
		\n
		Search the binary search tree for the given T.
		Type T must have equality and greater than comparison operators defined.
		*/
template <class T>
bool BinarySearchTree<T>::search(const T& searchItem) const
{
	nodeType<T> * current;
	bool found = false;

	if (this->root == 0)
	{
		cout << "Cannot search an empty tree." << endl;
	}
	else
	{
		// Tree is not empty...

		current = this->root;

		while(   (current != 0) && !(found)   )
		{
			// Keep searching...

			if (current->data == searchItem)
			{
				// Found at this node.
				found = true;
			}
			else if (current->data > searchItem)
			{
				// Search left subtree
				current = current->left;
			}
			else
			{
				// Search right subtree
				current = current->right;
			}
		}	// end while
	}		// end else

	return found;
}













		/**
		Insert the given item (T) into the tree.  Arguments: T
		\n
		@param	dataToInsert	(T) the item to insert.
		\n
		Insert the given item into the search tree.
		Creates a new node if successful.
		Aborts if a duplicate item is found in the tree.
		*/
template <class T>
void BinarySearchTree<T>::insert(const T & dataToInsert)
{
	nodeType<T> * current;			// pointer to traverse the tree.
	nodeType<T> * trailCurrent;		// pointer to follow current.
	nodeType<T> * newNode;			// pointer to create the node.

	newNode = new nodeType<T>;
	newNode->data = dataToInsert;
	newNode->left = 0;
	newNode->right = 0;

	if(this->root == 0)
	{
		// Tree is currently empty. Make this new item the root of the tree.
		this->root = newNode;

		// done
	}
	else
	{
		current = this->root; // Start at the root of the tree.
		while(current != 0)
		{
			trailCurrent = current;

			if(current->data == dataToInsert)
			{
				cout << "The item to be inserted is already\n in the tree. Duplicates are not allowed!" << endl;
				return;
				// done
			}
			else if (current->data > dataToInsert)
			{
				// Follow left subtree
				current = current->left;
			}
			else
			{
				// Follow right subtree
				current = current->right;
			}
		}		// end while.

		// current is now NULL. We have found the place to insert at.
		// trailCurrent is the parent of this NULL.

		if (trailCurrent->data > dataToInsert)
		{
			// Make the new node the LEFT child of trailCurrent.
			trailCurrent->left = newNode;
		}
		else
		{
			// Make the new node the RIGHT child of trailCurrent.
			trailCurrent->right = newNode;
		}
	}
}



		/**
		Delete the pointed (nodeType<T>) from the tree.  Arguments: Reference to a pointer to a nodeType<T>
		\n
		@param	p	(nodeType<T>) The pointed-to value of the node to be deleted.
		\n
		Delete (from the binary search tree) the node to which p points.
		*/
template <class T>
void BinarySearchTree<T>::deleteFromTree(nodeType<T> * & p)
{
	nodeType<T> * temp;			// pointer to delete the node.
	nodeType<T> * predecessor;	// pointer used in CASE 4.
	nodeType<T> * trailCurrent;	// pointer behind predecessor.

	if (p == 0)
	{
		cout << "Error: the node to be deleted is NULL." << endl;
	}
	else if(p->left == 0 && p->right == 0)
	{

		// CASE 1
		// Node to be deleted has no right or left subtree.
		// Go ahead and delete the node.
		temp = p;
		p = 0;
		delete temp;
	}
	else if(p->left == 0)
	{

		// CASE 2
		// Node to be deleted has no left subtree.
		// Bypass and then delete.
		temp = p;
		p = temp->right; // Bypass.
		delete temp;
	}
	else if(p->right == 0)
	{

		// CASE 3
		// Node to be deleted has no right subtree.
		// Bypass and then delete.
		temp = p;
		p = temp->left; // Bypass.
		delete temp;
	}
	else
	{

		// CASE 4
		// Node to be deleted has left and right subtrees.
		// Find the predecessor of the node to be deleted...

		// Go left.
		predecessor = p->left;
		trailCurrent = 0;

		// Go right until null.
		while (predecessor->right != 0)
		{
			trailCurrent = predecessor;
			predecessor = predecessor->right;
		}

		//   predecessor->right == NULL

		//   Overwrite the data of the node to be deleted,
		//   "swapping" in the data of the predecessor.
		p->data = predecessor->data; // Perform the "swap"



		// Bypass the predecessor.
		if (trailCurrent == 0)
		{
			// predecessor did not move.
			// predecessor == p->left.
			// we need to adjust p.

			p -> left = predecessor -> left; // bypass predecessor
		}
		else
		{
			// predecessor has no right subtree.
			// Get the left subtree of predecessor (might be NULL anyway. Does not matter)
			// ...call it LS
			// Set the right subtree of trailCurrent to LS.
			// predecessor has now been bypassed.

			trailCurrent->right = predecessor->left; // bypass predecessor
		}

		// Predecessor has been bypassed.
		// Delete the predecessor.

		delete predecessor;
		predecessor = 0;
	}
}




		/**
		Search for the given T and if found, delete it from the tree.  Arguments: T
		\n
		@param	deleteItem	(T) the item to be deleted.
		\n
		If a node with the same data as the given item is found, it is deleted from the binary search tree.
		If the binary search tree is empty or deleteItem is not in the tree, a message is printed.
		*/
template <class T>
void BinarySearchTree<T>::deleteNode(const T & deleteItem)
{
	nodeType<T> * current;		// pointer to traverse the tree.
	nodeType<T> * trailCurrent;	// pointer behind current.

	bool found = false;

	if (this->root == 0)
	{
		// Tree is empty.
		cout << "Cannot delete from an empty tree." << endl;
	}
	else
	{
		// Tree is not empty.

		current = this->root;
		trailCurrent = this->root;

		while
		(
				 current != 0
					&&
				!found
		)
		{
			if (current -> data == deleteItem)
			{
				// Found the item at this node.
				found = true;
			}
			else
			{
				// Not equal to this node.
				// Search one of the subtrees of this node...

				trailCurrent = current;

				if (current -> data > deleteItem)
				{
					// (Current-> data) > (deleteItem)
					// Search the left subtree for deleteItem
					current = current -> left;
				}
				else
				{
					// (Current-> data) <= (deleteItem)
					// Search the right subtree for deleteItem
					current = current -> right;
				}
			}
		}

		// current becomes null when we reach the end of a subtree without finding the item.
		// found becomes true when we find the item.


		if (current == 0)
		{
			// Searched the whole tree. Did not find the item.
			cout << "The item to be deleted is not in the tree." << endl;
		}
		else if(found)
		{
			// Found the item in the tree.

			if (current == this->root)
			{
				// The item is at the root node of the tree.
				deleteFromTree(this->root);
			}
			else if (trailCurrent -> data > deleteItem)
			{
				// The item was found in the tree, not at the root.
				// Current node is the LEFT subnode of trailCurrent
				deleteFromTree(trailCurrent->left); // delete current
			}
			else
			{
				// The item was found in the tree, not at the root.
				// Current node is the RIGHT subnode of trailCurrent
				deleteFromTree(trailCurrent->right); // delete current
			}
		}
		else
		{
			// How can this happen?  (found == true)  &&  (current != 0)
			cout << "How can this happen? The item to be deleted is not in the tree." << endl;
		}
	}
}




		/**
		Fill the given vector of (T) items, by in-order traversal of the tree.  Arguments: vector<T>
		\n
		@param	vect	(vector<T>) receives the data
		*/
template <class T>
void BinarySearchTree<T>::inOrderDump(vector<T> & vect) const
{
	fillVectorInOrder(vect, this->root);
}



		/**
		Fill the given vector of (T) items, by pre-order traversal of the tree.  Arguments: vector<T>
		\n
		@param	vect	(vector<T>) receives the data
		*/
template <class T>
void BinarySearchTree<T>::preOrderDump(vector<T> & vect) const
{
	fillVectorPreOrder(vect, this->root);
}



		/**
		Fill the given vector of (T) items, by post-order traversal of the tree.  Arguments: vector<T>
		\n
		@param	vect	(vector<T>) receives the data
		*/
template <class T>
void BinarySearchTree<T>::postOrderDump(vector<T> & vect) const
{
	fillVectorPostOrder(vect, this->root);
}






		/**
		Perform an in-order traversal, adding each node to the given vector of (T) items.  Arguments: vector<T>, vector<T>*
		\n
		@param	vect	((vector<T>) receives the values of the tree
		\n
		@param	p		((vector<T>*) the node of the current sub-tree being traversed.
		\n
		Process the left sub-tree first, then the current node, then the right sub-tree.
		*/
template <class T>
void BinarySearchTree<T>::fillVectorInOrder(vector<T> & vect, nodeType<T> * p) const
{
	if (p != 0)
	{
		fillVectorInOrder(vect, p->left);
		//cout << p->data.getKey() << endl;
		vect.push_back(p->data);			// process me in the middle.
		fillVectorInOrder(vect, p->right);
	}
}



		/**
		Perform an pre-order traversal, adding each node to the given vector of (T) items.  Arguments: vector<T>, vector<T>*
		\n
		@param	vect	((vector<T>) receives the values of the tree
		\n
		@param	p		((vector<T>*) the node of the current sub-tree being traversed.
		\n
		Process the current node, then the left sub-tree, then  right sub-tree.
		*/
template <class T>
void BinarySearchTree<T>::fillVectorPreOrder(vector<T> & vect, nodeType<T> * p) const
{
	if (p != NULL)
	{
		vect.push_back(p->data);			// process me first
		fillVectorPreOrder(vect, p->left);
		fillVectorPreOrder(vect, p->right);
	}
}




		/**
		Perform an post-order traversal, adding each node to the given vector of (T) items.  Arguments: vector<T>, vector<T>*
		\n
		@param	vect	((vector<T>) receives the values of the tree
		\n
		@param	p		((vector<T>*) the node of the current sub-tree being traversed.
		\n
		Process the left sub-tree, then the right sub-tree, then the current node.
		*/
template <class T>
void BinarySearchTree<T>::fillVectorPostOrder(vector<T> & vect, nodeType<T> * p) const
{
	if (p != NULL)
	{
		fillVectorPostOrder(vect, p->left);
		fillVectorPostOrder(vect, p->right);
		vect.push_back(p->data);			// process me last
	}
}








#endif  //_BINARY_SEARCH_TREE_H
