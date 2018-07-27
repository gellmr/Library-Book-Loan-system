/**
\file		SimpleBinaryTree.h
\brief		SimpleBinaryTree class definition and implementation
\n
Author:		Michael Gell  (Student Number: 30276096)
\n
Modified:	Thurs 19th May 2011.
\n
*/



#if !defined(_SIMPLE_BINARY_TREE_H)
#define _SIMPLE_BINARY_TREE_H


using namespace std;



		/**	\brief
		A node struct, containing the data (T) and left / right subtrees as nodeType<T> pointers. \n*/
template <class T>
struct nodeType
{
	T data;
	nodeType<T> * left;
	nodeType<T> * right;
};




		/**
		\class SimpleBinaryTree.
		\brief A templated binary tree.

		Abstract class providing virtual methods for searchByKey(), search(), insert(), deleteNode() ...and the Destructor.
		*/
template <class T>
class SimpleBinaryTree
{


public:


			/**	\brief
			Default Constructor. \n*/
	SimpleBinaryTree();

			/**	\brief
			Copy Constructor. \n*/
	SimpleBinaryTree(const SimpleBinaryTree<T> & otherTree);

			/**	\brief
			Virtual Destructor. \n*/
	virtual ~SimpleBinaryTree();

			/**	\brief
			Assignment Operator override. \n*/
	const SimpleBinaryTree& operator=(const SimpleBinaryTree<T> & otherTree);





	// Binary Tree methods
	/////////////////////////////////////////////////////////////////////



			/**	\brief
			Returns true if the binary tree is empty. \n*/
	bool isEmpty() const;


			/**	\brief
			Nodes are printed in inorder sequence. \n*/
	void inOrderTraversal() const;


			/**	\brief
			Nodes are printed in preorder sequence. \n*/
	void preOrderTraversal() const;


			/**	\brief
			Nodes are printed in postorder sequence. \n*/
	void postOrderTraversal() const;




			/**	\brief
			Returns the height of the binary tree. \n*/
	int treeHeight() const;



			/**	\brief
			Returns the number of nodes in the tree. \n*/
	int treeNodeCount() const;



			/**	\brief
			Returns the number of leaves in the tree. \n*/
	int treeLeavesCount() const;



			/**	\brief
			Deallocate each node, set root = null. \n*/
	void destroyTree();



			/**	\brief
			Return true if item with the given key is found in the tree. \n*/
	virtual bool searchByKey(const long & searchKey) const = 0;



			/**	\brief
			Return true if item found in tree. \n*/
	virtual bool search(const T & searchItem) const = 0;



			/**	\brief
			Creates a node and inserts in tree, if not causing duplicate. \n*/
	virtual void insert(const T & insertItem) = 0;



			/**	\brief
			Delete first node found with same data as deleteItem. If tree is empty or item is not found, print a message. \n*/
	virtual void deleteNode(const T & deleteItem) = 0;



protected:


			/**	\brief
			The root node of this tree. \n*/
	nodeType<T> * root;


private:

			/**	\brief
			Make a copy of the binary tree to which otherTreeRoot points. \n*/
	void copyTree(
					nodeType<T> * & copiedTreeRoot,
					nodeType<T> * otherTreeRoot
				 );



			/**	\brief
			Destroy the binary tree to which p points. \n

			Deallocates each node. \n
			Sets p = NULL. \n
			*/
	void destroy(nodeType<T> * & p);


			/**	\brief
			Do an in order traversal of the binary tree to which p points, printing each node. \n */
	void inOrder(nodeType<T> * p) const;


			/**	\brief
			Do a pre-order traversal of the binary tree to which p points, printing each node. \n */
	void preOrder(nodeType<T> * p) const;


			/**	\brief
			Do a post-order traversal of the binary tree to which p points, printing each node. \n */
	void postOrder(nodeType<T> * p) const;


			/**	\brief
			Find the height of the tree. \n*/
	int height(nodeType<T> * p) const;


			/**	\brief
			Returns the larger of x and y parameters. \n */
	int max(const int & x, const int & y) const;


			/**	\brief
			Returns the number of nodes in the binary tree to which p points. \n */
	int nodeCount(nodeType<T> * p) const;


			/**	\brief
			Returns the number of leaves in the binary tree to which p points. \n */
	int leavesCount(nodeType<T> * p) const;

};


// There is no .cpp file, because this is a template.




#include <iostream>



using namespace std;






		/**
		Virtual Destructor.  Arguments: none
		\n
		Destroys the root of this tree.
		*/
template <class T>
SimpleBinaryTree<T>::~SimpleBinaryTree()
{
	destroy(root);
}






		/**
		Default Constructor.  Arguments: none
		\n
		Initialises the root of this tree to NULL.
		*/
template <class T>
SimpleBinaryTree<T>::SimpleBinaryTree()
{
	root = 0;
}





		/**
		Copy Constructor.  Arguments: SimpleBinaryTree<T>
		\n
		@param	otherTree	(SimpleBinaryTree<T>) The tree we are copying from.
		\n
		Copies the given tree into this tree, overwriting all data.
		*/
template <class T>
SimpleBinaryTree<T>::SimpleBinaryTree(const SimpleBinaryTree<T> & otherTree)
{
	if (otherTree.root == 0)
		root = 0;
	else
		copyTree(root, otherTree.root);
}









		/**
		Assignment Operator override.  Arguments: SimpleBinaryTree<T>
		\n
		@param	otherTree	(SimpleBinaryTree<T>) The tree we are copying from.
		\n
		Copies the given tree into this tree, overwriting all data.
		Returns the value of the current object (*this)
		*/
template <class T>
const SimpleBinaryTree<T> & SimpleBinaryTree<T>::operator=(const SimpleBinaryTree<T> & otherTree)
{
	// Avoid self-assignment
	if (this != &otherTree)
	{
		if (root != 0)
			destroy(root);

		if (otherTree.root == 0)
			root = 0;
		else
			copyTree(root, otherTree.root);
	}
	return *this; // The value of the object that was just assigned.
}









		/**
		Find if the tree is empty.  Arguments: none
		\n
		@return	(bool) true if the root node is null.
		\n
		*/
template <class T>
bool SimpleBinaryTree<T>::isEmpty() const
{
	return (root == 0);
}






		/**
		Find the height of the tree.  Arguments: none
		\n
		@return	(int) the height of the tree.
		\n
		*/
template <class T>
int SimpleBinaryTree<T>::treeHeight() const
{
	return height(root);
}





		/**
		Find the number of nodes in the tree.  Arguments: none
		\n
		@return	(int) the number of nodes.
		\n
		*/
template <class T>
int SimpleBinaryTree<T>::treeNodeCount() const
{
	return nodeCount(root);
}







		/**
		Find the number of leaves in the tree.  Arguments: none
		\n
		@return	(int) the number of leaves.
		\n
		*/
template <class T>
int SimpleBinaryTree<T>::treeLeavesCount() const
{
	return leavesCount(root);
}








		/**
		Find the height of the tree pointed to by p.  Arguments: nodeType<T> *
		\n
		@param	p	(nodeType<T> *) the root node of the current sub-tree.
		\n
		@return	(int) the height of the tree.
		\n
		*/
template <class T>
int SimpleBinaryTree<T>::height(nodeType<T> * p) const
{
	if (p == 0)
		return 0;
	else
		return 1 + max(height(p->left), height(p->right));
}





		/**
		Find the greater of x and y.  Arguments: int, int
		\n
		@param	x	(int) An int value.
		\n
		@param	y	(int) An int value.
		\n
		@return	(int) the greater of ( x , y )
		\n
		Used to find the height of a tree.
		\n
		*/
template <class T>
int SimpleBinaryTree<T>::max(const int & x, const int & y) const
{
	if (x >= y)
	{
		return x;
	}
	else
	{
		return y;
	}
}




		/**
		Returns the number of nodes in the binary tree to which p points.  Arguments: nodeType<T> *
		\n
		@param	p	(nodeType<T> *)  The root node of the current sub-tree
		\n
		@return	(int) the number of (NON-NULL) nodes in the tree.
		*/
template <class T>
int SimpleBinaryTree<T>::nodeCount(nodeType<T> * p) const
{
	if (p != 0)
	{
		return(
					  1
					+ nodeCount(p->left)
					+ nodeCount(p->right)
			   );
	}
	return 0;
}




		/**
		Returns the number of leaves in the binary tree to which p points.  Arguments: nodeType<T> *
		\n
		@param	p	(nodeType<T> *) The root node of the current sub-tree
		\n
		@return	(int) the number of leaves in the tree.
		\n
		*/
template <class T>
int SimpleBinaryTree<T>::leavesCount(nodeType<T> *p) const
{
	if (p == 0)
	{
		// This is a leaf node
		return 1;
	}

	// This is NOT a leaf node.
	return( leavesCount(p->left) + leavesCount(p->right) );
}





		/**
		Copy from otherTreeRoot into copiedTreeRoot.  Arguments: Reference to a nodeType<T> *, nodeType<T> *
		\n
		@param	copiedTreeRoot	(nodeType<T> *&)	The current node of the tree we are building.
		\n
		@param	otherTreeRoot	(nodeType<T> *)		The current node of the tree we are copying from.
		\n
		Allocates new nodeTypes on the heap.
		*/
template <class T>
void SimpleBinaryTree<T>::copyTree(
								nodeType<T> * & copiedTreeRoot,
								nodeType<T> * otherTreeRoot
							)
{
	if (otherTreeRoot == 0)
		copiedTreeRoot = 0;
	else
	{
		copiedTreeRoot = new nodeType<T>;
		copiedTreeRoot->data = otherTreeRoot->data;
		copyTree(copiedTreeRoot->left, otherTreeRoot->left);
		copyTree(copiedTreeRoot->right, otherTreeRoot->right);
	}
}





		/**
		Destroy the given node and its children.  Arguments: Reference to a nodeType<T>*
		\n
		@param	p	(nodeType<T> *) The root node of the current sub-tree.
		\n
		To destroy a binary tree,
		for each node
		we destroy its left subtree,
		then its right subtree.
		Then deallocate the node itself.
		*/
template <class T>
void SimpleBinaryTree<T>::destroy(nodeType<T> * & p)
{
	if (p != 0)
	{
		destroy(p->left);
		destroy(p->right);
		delete p;
		p = 0;
	}
}




		/**
		Destroy the binary tree.
		*/
template <class T>
void SimpleBinaryTree<T>::destroyTree()
{
	destroy(root);
}





		/**
		Perform an in-order traversal, printing each node.  Arguments: none \n
		*/
template <class T>
void SimpleBinaryTree<T>::inOrderTraversal() const
{
	inOrder(root);
}



		/**
		Perform a pre-order traversal, printing each node.  Arguments: none \n
		*/
template <class T>
void SimpleBinaryTree<T>::preOrderTraversal() const
{
	preOrder(root);
}




		/**
		Perform a post-order traversal, printing each node.  Arguments: none \n
		*/
template <class T>
void SimpleBinaryTree<T>::postOrderTraversal() const
{
	postOrder(root);
}









		/**
		Perform an in-order traversal, printing each node (nodeType<T>).  Arguments: nodeType<T> *
		\n
		@param	p	(nodeType<T> *) the root of the current sub-tree being traversed.
		\n
		*/
template <class T>
void SimpleBinaryTree<T>::inOrder(nodeType<T> * p) const
{
	if (p != 0)
	{
		inOrder(p->left);
		cout << p->data << " ";  // process me in the middle.
		inOrder(p->right);
	}
}



		/**
		Perform a pre-order traversal, printing each node (nodeType<T>).  Arguments: nodeType<T> *
		\n
		@param	p	(nodeType<T> *) the root of the current sub-tree being traversed.
		\n
		*/
template <class T>
void SimpleBinaryTree<T>::preOrder(nodeType<T> * p) const
{
	if (p != NULL)
	{
		cout << p->data << " ";  // process me first
		preOrder(p->left);
		preOrder(p->right);
	}
}




		/**
		Perform a post-order traversal, printing each node (nodeType<T>).  Arguments: nodeType<T> *
		\n
		@param	p	(nodeType<T> *) the root of the current sub-tree being traversed.
		\n
		*/
template <class T>
void SimpleBinaryTree<T>::postOrder(nodeType<T> * p) const
{
	if (p != NULL)
	{
		postOrder(p->left);
		postOrder(p->right);
		cout << p->data << " "; // process me last
	}
}



#endif  //_SIMPLE_BINARY_TREE_H
