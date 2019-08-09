
//
//  Binary Search Tree Class
//
//  Modified code from Weiss
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

template<class Comparable>
struct BinaryNode
{
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;
    
    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
    : element{ theElement }, left{ lt }, right{ rt }{ }
    
    BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
    : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
};


// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// bool contains( x )     --> Return true if x is present
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************


template <typename Comparable>
class BinarySearchTree
{
public:
    typedef BinaryNode<Comparable> Node;
    
    BinarySearchTree( ) : root{ nullptr }
    {
    }
    
    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
    
    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }
    
    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }
    
    
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }
    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }
    
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
	//Only for testing purposes
	BinaryNode<Comparable>* get_root() {
		return root;
	}

	//Implement these
	void levelOrderTraversal() const;
	double average_node_depth() const;
	void rangedPrint(int low, int high) const;
	void stringy();

private:
    
    BinaryNode<Comparable> *root;
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, Node * & t )
    {
        if( t == nullptr )
            t = new Node{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, Node * & t )
    {
        if( t == nullptr )
            t = new Node{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing

    }
    
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( Node * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }
    
    
    /**
     * Internal method to clone subtree.
     */
    Node * clone( Node *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new Node{ t->element, clone( t->left ), clone( t->right ) };
    }
    
	//implement this
	bool contains(const Comparable& x, Node* t) const;
    
};

//For testing purposes
template<class tp>
vector<tp> toVec(stringstream& strm) {
	tp i;
	vector<tp> vec;
	while (strm >> i) {
		vec.push_back(i);
		if (strm.peek() == ' ' || strm.peek() == '\n' || strm.peek() == ',') {
			strm.ignore();
		}
	}
	return vec;
}

//For testing purposes
struct cout_redirect {
	cout_redirect(std::streambuf * new_buffer)
		: old(std::cout.rdbuf(new_buffer))
	{ }

	~cout_redirect() {
		std::cout.rdbuf(old);
	}

private:
	std::streambuf * old;
};

SCENARIO("Testing the BinarySearchTree class") {
	GIVEN("A Binary Search tree with values inserted") {
		BinarySearchTree<int> bst;
		bst.insert(31);
		bst.insert(12);
		bst.insert(53);
		bst.insert(4);
		bst.insert(25);
		bst.insert(46);
		bst.insert(67);
		WHEN("Method contains is used") {
			bool Con_31 = bst.contains(31);
			bool Con_25 = bst.contains(25);
			bool Con_1 = bst.contains(1);
			THEN("31 and 25 should be true, but 1 should be false") {
				REQUIRE(Con_31 == true);
				REQUIRE(Con_25 == true);
				REQUIRE(Con_1 == false);
			}
		}
		WHEN("Method rangedPrint is called") {
			stringstream buffer;
			cout_redirect redir(buffer.rdbuf());
			bst.rangedPrint(12, 53);
			vector<int> resVec = { 12,25,31,46,53 };
			vector<int> asVec = toVec<int>(buffer);
			THEN("It should print out all objects in the given range") {
				for (int x = 0; x < asVec.size(); ++x) {
					REQUIRE(resVec[x] == asVec[x]);
				}
			}
		}
		WHEN("Method average_node_depth is called") {
			double depth = bst.average_node_depth();
			REQUIRE(depth <= 1.429);
			REQUIRE(depth >= 1.427);
		}
		WHEN("Method levelOrderTraversal is called") {
			stringstream buffer;
			cout_redirect redir(buffer.rdbuf());
			bst.levelOrderTraversal();
			vector<int> resVec = { 31, 12, 53, 4, 25, 46, 67 };
			vector<int> asVec = toVec<int>(buffer);
			THEN("It should print out items in every level before the next level") {
				for (int x = 0; x < asVec.size(); ++x) {
					REQUIRE(resVec[x] == asVec[x]);
				}
			}
		}
	}
	GIVEN("A Binary Search Tree with values 'a' to 'f' inserted") {
		BinarySearchTree<char> bst2;
		bst2.insert('d');
		bst2.insert('b');
		bst2.insert('f');
		bst2.insert('a');
		bst2.insert('c');
		bst2.insert('e');
		WHEN("Method stringy is called") {
			bst2.stringy();
			THEN("All nodes should have nullptr in left member and tree height should be n-1") {
				int size = -1;
				BinaryNode<char>* root = bst2.get_root();
				vector<char> resVec = { 'a', 'b', 'c', 'd', 'e', 'f' };
				while (root != nullptr) {
					REQUIRE(root->left == nullptr);
					REQUIRE(resVec[size + 1] == root->element);
					size += 1;
					root = root->right;
				}
				REQUIRE(size == 5);
			}

		}
	}
}
