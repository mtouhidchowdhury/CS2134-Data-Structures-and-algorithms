#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>

using namespace std;

template<typename HashedObj>
class HashTable
{
    public:
        enum EntryType { ACTIVE, EMPTY, DELETED };
    private:
        struct HashEntry {
            HashedObj element;
            EntryType info;
            HashEntry( const HashedObj & e = HashedObj(), EntryType i = EMPTY )
                : element( e ), info( i ) {}
        };
    public:
        typedef typename vector<HashEntry>::const_iterator iterator;
        explicit HashTable(int size = 101):currentSize(0) {
            array.resize(size);
        }

        iterator find( const HashedObj & );
        bool remove( const HashedObj & );
        void makeEmpty();
        bool insert( const HashedObj & );
        iterator end() const;
        int capacity() const;

    private:
        std::hash<HashedObj> hf;

        vector<HashEntry> array;
        int currentSize;
        void rehash();
};

template< typename HashedObj >
bool HashTable<HashedObj>::insert( const HashedObj & x ) {
    /**
     * Your code here
     */
    return false;
}

template< class HashedObj >
typename HashTable<HashedObj>::iterator HashTable<HashedObj>::find( const HashedObj & x ) {
    /**
     * Your code here
     */
    return array.end();
}

template< typename HashedObj >
bool HashTable<HashedObj>::remove( const HashedObj & x ) {
    int index =  hf(x) % array.size() ;
    for( int i = index; i < array.size(); ++i ) {
        if ( array[i].info == EMPTY )
            return false;
        if ( array[i].info == ACTIVE && array[i].element == x ) {
            array[i].info = DELETED;
            --currentSize;
            return true;
        }
    }
    for( int i = 0; i < index; ++i ) {
        if ( array[i].info == EMPTY )
            return false;
        if ( array[i].info == ACTIVE && array[i].element == x ) {
            array[i].info = DELETED;
            --currentSize;
            return true;
        }
    }
    /**
     * There's a clever but convoluted way to merge the above two loops into one
     * if you would like to give it a shot.
     */
    return false;
}

template< typename HashedObj >
void HashTable<HashedObj>::rehash() {
    /**
     * Your code here
     */
    return;
}

template< typename HashedObj >
void HashTable<HashedObj>::makeEmpty() {
    for( auto i : array )
        i.info = EMPTY;
}

template<typename HashedObj>
typename HashTable<HashedObj>::iterator HashTable<HashedObj>::end() const {
    return array.end();
}

template<typename HashedObj>
int HashTable<HashedObj>::capacity() const {
    return array.size();
}

SCENARIO("Testing the hash table with linear probing") {
    HashTable<int> hst;
    int n = 10; //adjust to make it less than 10 when rehash isn't implemented;
    int capacity = hst.capacity();

	GIVEN("A hash table has been created but not filled") {
        WHEN("Method insert is called") {
            THEN("All insertions of original elements should succeed") {
                for( int i = 0; i < n; ++i )
                    REQUIRE( hst.insert(i*capacity) == true );
            }
            THEN("All insertions of duplicate elements should fail") {
                for( int i = 0; i < n; ++i) {
                    REQUIRE( hst.insert(i * capacity) == true );
                    REQUIRE( hst.insert(i * capacity) == false );
                }
            }
        }
    }

    GIVEN("A hash table has been created and filled ") {
        for( int i = 0; i < n; ++i )
            hst.insert( i * capacity);
        capacity = hst.capacity();

        WHEN("Method insert is called") {
            THEN("It should fail on all duplicate elements") {
                for( int i = 0; i < n; ++i) {
                    REQUIRE( hst.insert(i*capacity) == false );
                }
            }
            THEN("It should pass on all original elements") {
                for( int i = 0; i < n; ++i ) {
                    hst.remove(i * capacity);
                    REQUIRE( hst.insert( i*capacity ) == true );
                }
                for( int i = n; i < 2*n; ++i ) {
                    REQUIRE( hst.insert( i*capacity ) == true );
                }
            }
        }

        WHEN("Method remove is called") {
            THEN("It should return true for any item in the table.") {
                for( int i = 0; i < n; ++i )
                    REQUIRE( hst.remove(i * capacity) == true );
            }
        }

        WHEN("Method remove is called") {
            THEN("It should return false for any item not in the table.") {
                for( int i = n; i < 2*n; ++i )
                    REQUIRE( hst.remove(i * capacity) == false );
            }
        }

        WHEN("Method find is used") {
            for( int i = 0; i < n; ++i )
                hst.insert(i * capacity);
            THEN("All inserted elements should be found") {
                for( int i = 0; i < n; ++i )
                    REQUIRE( hst.find(i * capacity)->element ==  i * capacity );
                }
            THEN("Any non-inserted element should not be found") {
                for( int i = n; i < 2*n; ++i )
                    REQUIRE( hst.find(i*capacity) == hst.end() );
                }
            THEN("Any element that is deleted should not be found.") {
                for( int i = 0; i < n; ++i ) {
                    hst.remove(i * capacity);
                    REQUIRE( hst.find(i * capacity) == hst.end() );
                }
            }
        }

        WHEN("The load factor is greater than 0.5") {
            const int * temp = &(hst.find(5 * capacity)->element);
            for( int i = 1; i < 100; ++i )
                hst.insert( i );
            THEN("rehash() should be called.") {
                REQUIRE( hst.capacity() != capacity  );
            }
        }
    }
}    
