//
//  Modified from Weiss' linked list class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <algorithm>
#include <string>
/*Mohammed Touhid Chowdhury 
hw7 q1
*/
using namespace std;

template <typename Object>
class List
{
private:

	struct Node
	{
		Object  data;
		Node   *next;

		Node(const Object & d = Object{}, Node * n = nullptr)
			: data{ d }, next{ n } { }

		Node(Object && d, Node * n = nullptr)
			: data{ std::move(d) }, next{ n } { }
	};

public:
	class iterator
	{
	public:

		iterator() : current(nullptr)
		{ }

		Object & operator* ()
		{
			return current->data;
		}

		const Object & operator* () const
		{
			return  current->data;
		}

		iterator & operator++ ()
		{
			this->current = this->current->next;
			return *this;
		}

		iterator operator++ (int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}

		bool operator== (const iterator & rhs) const
		{
			return current == rhs.current;
		}

		bool operator!= (const iterator & rhs) const
		{
			return !(*this == rhs);
		}

	private:
		Node * current;

		iterator(Node *p) : current{ p }
		{ }

		friend class List<Object>;
	};

public:
	List()
	{
		header = new Node();
	}

	List(const List & rhs) :header(new Node) {
		Node* rhsHeader = rhs.header;
		Node* thisHeader = header;
		rhsHeader = rhsHeader->next;
		while (rhsHeader != nullptr) {
			thisHeader->next = new Node(rhsHeader->data);
			thisHeader = thisHeader->next;
			rhsHeader = rhsHeader->next;
		}
	}

	~List() {
		clear();
		delete header;

	}

	List & operator= (const List & rhs)
	{
		List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	List(List && rhs) :header{ new Node }
	{
		header->next = rhs.header->next;
		rhs.header->next = nullptr;
	}

	List & operator= (List && rhs)
	{
		std::swap(header, rhs.header);
		return *this;
	}

	iterator begin() const
	{
		return iterator(header->next);
	}

	iterator end() const
	{
		return iterator(nullptr);
	}

	iterator before_begin() const
	{
		return iterator(header);
	}

	bool empty() const
	{
		return header->next == nullptr;
	}

	void clear()
	{
		while (!empty())
			pop_front();
	}

	void push_front(Object data) {
		header->data = data;
		Node* oldHeader = header;
		header = new Node;
		header->next = oldHeader;
	}

	void pop_front()
	{
		erase_after(before_begin());
	}

	iterator insert_after(iterator itr, const Object & x)
	{
		Node *p = itr.current;
		p->next = new Node{ x, p->next };

		return iterator(p->next);
	}

	iterator erase_after(iterator itr)
	{
		Node *p = itr.current;
		Node *oldNode = p->next;

		p->next = oldNode->next;
		delete oldNode;

		return iterator(p->next);
	}

	Object & front() { return *begin(); }

	const Object & front() const { return *begin(); }

	void merge(List & alist) {
		List tmpList;
		Node* thisHeader = begin().current;
		Node* rhsHeader = alist.begin().current;
		while (thisHeader != nullptr && rhsHeader != nullptr) {
			if (thisHeader->data <= rhsHeader->data) {
				tmpList.push_front(thisHeader->data);
				thisHeader = thisHeader->next;
			}
			else if (thisHeader->data > rhsHeader->data) {
				tmpList.push_front(rhsHeader->data);
				rhsHeader = rhsHeader->next;
			}
		}
		while (thisHeader != nullptr) {
			tmpList.push_front(thisHeader->data);
			thisHeader = thisHeader->next;
		}
		while (rhsHeader != nullptr) {
			tmpList.push_front(rhsHeader->data);
			rhsHeader = rhsHeader->next;
		}
		this->clear();
		Node* tmpTraverse = tmpList.begin().current;
		while (tmpTraverse != nullptr) {
			this->push_front(tmpTraverse->data);
			tmpTraverse = tmpTraverse->next;
		}
		alist.clear();

	}

	void remove_adjacent_duplicates() {
		Node* trailHeader = begin().current;
		while (trailHeader != nullptr && trailHeader->next != nullptr) {
			while (trailHeader->next != nullptr && trailHeader->data == trailHeader->next->data) {
				erase_after(iterator(trailHeader));
			}
			trailHeader = trailHeader->next;
		}
	}

	template<class Predicate>
	void remove_if(Predicate pred) {
		iterator prev = before_begin();
		for ( iterator curr = begin(); curr != end();) {
			if (pred(*curr)) {
				curr = erase_after(prev);
			}
			else
			{
				++prev;
				++curr;
			}
		}
	}
private:
	Node *header;
};

SCENARIO("Testing Copy Constructor") {
	GIVEN("An instance of the list class") {
		List<int> l;
		l.push_front(3);
		l.push_front(2);
		l.push_front(1);
		WHEN("The copy constructor is invoked") {
			List<int> l2(l);
			THEN("A deep copy should have been made") {
				List<int>::iterator itr1 = l.begin();
				List<int>::iterator itr2 = l2.begin();
				while (itr2 != l2.end() && itr1 != l.end()) {
					REQUIRE(*itr2 == *itr1);
					++itr2;
					++itr1;
				}
				REQUIRE(itr1 == l.end());
				REQUIRE(itr2 == l2.end());
				l.clear();
				REQUIRE(l.empty());
				REQUIRE(!l2.empty());
			}
		}
	}
}


SCENARIO("Testing the method front()") {
	GIVEN("An instance of the list class with elements inserted") {
		List<int> l;
		l.push_front(3);
		l.push_front(2);
		l.push_front(1);
		WHEN("front() is called") {
			REQUIRE(l.front() == 1);
		}
	}
}



SCENARIO("Testing the method merge()") {
	GIVEN("Two Instances of the list class with elements in relative sorted order for each") {
		List<int> l1;
		l1.push_front(6);
		l1.push_front(4);
		l1.push_front(2);
		List<int> l2;
		l2.push_front(5);
		l2.push_front(3);
		l2.push_front(1);
		WHEN("Merge is called") {
			l1.merge(l2);
			THEN("The elements should be in sorted order") {
				List<int>::iterator lead = l1.begin();
				List<int>::iterator tail = lead;
				++lead;
				for (; lead != l1.end(); ++lead) {
					REQUIRE(*tail < *lead);
				}
			}
			THEN("l2 should be empty") {
				REQUIRE(l2.empty());
			}
		}
	}
}

SCENARIO("Testing remove_adjacent_duplicates()") {
	GIVEN("A list with a ton of adjacent duplicates") {
		List<char> l;
		for (int x = 0; x < 5; ++x) {
			l.push_front('c');
		}
		for (int x = 0; x < 3; ++x) {
			l.push_front('b');
		}
		for (int x = 0; x < 5; ++x) {
			l.push_front('c');
		}
		for (int x = 0; x < 2; ++x) {
			l.push_front('a');
		}
		WHEN("remove_adjacent_duplicates() is called") {
			l.remove_adjacent_duplicates();
			THEN("The resulting list should be a->c->b->c") {
				List<char>::iterator iter = l.begin();
				REQUIRE(*iter == 'a');
				++iter;
				REQUIRE(*iter == 'c');
				++iter;
				REQUIRE(*iter == 'b');
				++iter;
				REQUIRE(*iter == 'c');
			}
		}
	}
}

// Ignore this pred used for testing
template<class Foo>
class aPred {
public:
	aPred(Foo bar) :myFoo(bar) {}
	bool operator()(Foo otherBar) {
		return myFoo != otherBar;
	}
private:
	Foo myFoo;
};

SCENARIO("testing remove_if") {
	GIVEN("A list with things to remove and a pred") {
		List<string> l;
		l.push_front("Scott");
		l.push_front("Maliat");
		l.push_front("Nico");
		l.push_front("Anam");
		l.push_front("Xinran");
		l.push_front("Lolaly");
		aPred<string> myPred("Nico");
		WHEN("remove_if is used") {
			l.remove_if(myPred);
			THEN("Only Nico should be left.") {
				REQUIRE(l.front() == "Nico");
			}
		}
	}
}
