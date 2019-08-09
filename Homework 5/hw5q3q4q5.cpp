#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include<iostream>
#include<vector>

using namespace std;
/*
Mohammed Touhid Chowdhury 
mtc405
N14108583
hw5 q3q4q5
*/


template <class Itr>
void mergeSort(Itr tmpStart, Itr start, Itr end) {
	if (start + 1 == end) return;
	Itr mid = start + ((end - start) / 2);
	mergeSort(tmpStart, start, mid);
	mergeSort(tmpStart, mid, end);
	merge(start, mid, mid, end, tmpStart);
	while (start != end) {
		*start = *tmpStart;
		++start;
		++tmpStart;
	}
}


template<class RandItr>
void mergeSort(RandItr start, RandItr end) {
	int  sz = end - start;  // or use auto sz = end-start;
	//typedef typename iterator_traits< RandItr >::value_type Object; //Xcode
	typedef  iterator_traits< RandItr >::value_type Object; //Other compilers
																	// Don’t worry about this line of code
	vector<Object> tmp(sz);
	mergeSort(tmp.begin(), start, end);
}

SCENARIO("TESTING MERGESORT") {
	GIVEN("An unsorted vector of integers") {
		vector<int> randomVec = { 9,0,2,1,0,1,2,3,4,5,6,7,8,9 };
		WHEN("Mergsort is used to sort the vector from least to greatest") {
			size_t numElements = randomVec.size();
			mergeSort(randomVec.begin(), randomVec.end());
			THEN("The number of elements should remain the same") {
				REQUIRE(numElements == randomVec.size());
			}
			THEN("The vector is sorted") {
				for (int x = 1; x < randomVec.size(); ++x) {
					REQUIRE(randomVec[x - 1] <= randomVec[x]);
				}
			}
		}
	}
}

class student {
private:
	string name;
	double gpa;
public:
	student(const string& name, double gpa) :name(name), gpa(gpa) {}
	string get_name() const { return name; }
	double get_gpa() const { return gpa; }
};

class meFirst {
public:
	meFirst(const string& me) : me(me) {}
	bool operator()(const student& student1, const student& student2) {
		if (student1.get_name() == student2.get_name()) { return false; }
		else if (student1.get_name() == me) { return true; }
		else if (student2.get_name() == me) { return false; }
		return (student1.get_name() < student2.get_name());
	
	}
private:
	string me;
};

SCENARIO("TESTING MEFIRST") {
	GIVEN("A functor meFirst") {
		string priority = "Saitama";
		meFirst m(priority);
		WHEN("students are created") {
			student Saitama_Sensei(priority, 2.0);
			student Genos("Genos", 4.0);
			student Bang("Bang", 3.8);
			THEN("When the me matches, priority student goes first") {
				REQUIRE(m(Saitama_Sensei, Genos));
			}
			THEN("When two students who do not match, alphabetically first goes first") {
				REQUIRE(m(Genos, Bang) == false);
				REQUIRE(m(Bang, Genos) == true);
			}
		}
	}
}


void sortByFalse(vector<bool>& boolVec) {
	int begin = 0;
	for (size_t i = 0; i < boolVec.size(); i++) {
		if (boolVec[i] == false) { 
			swap(boolVec[i], boolVec[begin]);//make all the false in the first half 
			++begin;
		}
	}
}

SCENARIO("Order the Trues and Falses") {
	GIVEN("A vector of boolean values (true/false)") {
		vector<bool> vecBool = { false, true, false, true, true, true, false, false };
		WHEN("Sorted") {
			sortByFalse(vecBool);
			THEN("All falses should come before true") {
				bool lastSeen = false;
				for (int x = 0; x < vecBool.size(); ++x) {
					if (lastSeen == true) {
						REQUIRE(vecBool[x] == true);
					}
					lastSeen = vecBool[x];
				}
			}
		}
	}
}


