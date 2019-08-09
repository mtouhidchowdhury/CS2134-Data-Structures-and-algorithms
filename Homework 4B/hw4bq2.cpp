#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <string>
using namespace std;
/*
Mohammed Touhid Chowdhury 
mtc405
N14108583
hw4b q2

*/
template <class Object>
bool dupTestList(const vector<Object>& vec) {
	
	return false;
}

template <class Object>
bool dupTestSort(vector<Object>& vec) {  
	vector<Object>::iterator itrBegin = vec.begin(); 
	vector<Object>::iterator itrEnd = vec.end();
	std::sort(itrBegin, itrEnd);
	for (size_t i = 1; i < vec.size(); i++) {
		if (vec[i] == vec[i - 1]){
			return true;
		}
	}
	return false;
}

template <class Object>
bool dupTestSet(const vector<Object>& vec) {
	set<Object> duplicateSet;
	for(size_t i = 0 ; i != vec.size(); ++i){
		if (!duplicateSet.insert(vec[i]).second) { 
			return true; 
		}
	}
	return false;
}

template <class Object>
bool dupTestUnorderedSet(const vector<Object>& vec) {
	unordered_set<Object> duplicateSet;
	duplicateSet.insert(vec.begin(), vec.end());
	if (duplicateSet.size() != vec.size()) {
		return true;
	}
	return false;
	

}

SCENARIO("Testing check if there is duplicates") {
	GIVEN("A vector of int with no duplicates") {
		vector<int> intvec;
		intvec.push_back(1);
		intvec.push_back(2);
		intvec.push_back(3);
		WHEN("Checking duplicates with list") {
			bool isDup = dupTestList(intvec);
			THEN("It should return false") {
				REQUIRE(isDup == false);
			}
		}
		WHEN("Checking duplicates with sort+vec") {
			bool isDup = dupTestSort(intvec);
			THEN("It should return false") {
				REQUIRE(isDup == false);
			}
		}
		WHEN("Checking duplicates with set") {
			bool isDup = dupTestSet(intvec);
			THEN("It should return false") {
				REQUIRE(isDup == false);
			}
		}
		WHEN("Checking duplicates with unordered set") {
			bool isDup = dupTestUnorderedSet(intvec);
			THEN("It should return false") {
				REQUIRE(isDup == false);
			}
		}
	}
	GIVEN("A vector of char with duplicates") {
		vector<char> charvec;
		charvec.push_back('a');
		charvec.push_back('c');
		charvec.push_back('a');
		WHEN("Checking duplicates with list") {
			bool isDup = dupTestList(charvec);
			THEN("It should return true") {
				REQUIRE(isDup == true);
			}
		}
		WHEN("Checking duplicates with sort+vec") {
			bool isDup = dupTestSort(charvec);
			THEN("It should return true") {
				REQUIRE(isDup == true);
			}
		}
		WHEN("Checking duplicates with set") {
			bool isDup = dupTestSet(charvec);
			THEN("It should return true") {
				REQUIRE(isDup == true);
			}
		}
		WHEN("Checking duplicates with unordered set") {
			bool isDup = dupTestUnorderedSet(charvec);
			THEN("It should return true") {
				REQUIRE(isDup == true);
			}
		}
	}
	GIVEN("An empty vector of string") {
		vector<string> svec;
		WHEN("Checking duplicates with list") {
			bool isDup = dupTestList(svec);
			THEN("It should return false") {
				REQUIRE(isDup == false);
			}
		}
		WHEN("Checking duplicates with sort+vec") {
			bool isDup = dupTestSort(svec);
			THEN("It should return false") {
				REQUIRE(isDup == false);
			}
		}
		WHEN("Checking duplicates with set") {
			bool isDup = dupTestSet(svec);
			THEN("It should return false") {
				REQUIRE(isDup == false);
			}
		}
		WHEN("Checking duplicates with unordered set") {
			bool isDup = dupTestUnorderedSet(svec);
			THEN("It should return false") {
				REQUIRE(isDup == false);
			}
		}
	}
}