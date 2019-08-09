#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include<iostream>
#include<vector>
#include<list>
/*
Mohammed Touhid Chowdhury 
mtc405 
N14108585
hw#3 coding part:
Professor Linda Sellie 
*/

using namespace std;

template<class Itr, class UnaryPred> //signature of function template 
void print_if(Itr start, Itr end, UnaryPred pred) {
	Itr itrObject;
	for (itrObject = start; itrObject != end; itrObject++) { // iter through object from begin to end 
		if (pred(*itrObject)) { //if returns true it prints 
			cout << *itrObject << endl;
		}
	}

}



// functor foo that requires obj's '<' operator to be defined
template<class obj>
class foo {
public:
	foo(obj someObj) :myObj(someObj) {}
	bool operator()(obj aObj) {
		return myObj < aObj;
	}
private:
	obj myObj;

};

// toVec reads a stringstream and parses into a vector of tp
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

SCENARIO("Testing Print_If") {
	stringstream buffer;
	//Locally defined cout_redirect used to redirect stdout into a buffer
	struct cout_redirect {
		cout_redirect(streambuf * new_buffer) : old(cout.rdbuf(new_buffer)) {}
		~cout_redirect() {
			cout.rdbuf(old);
		}
	private:
		streambuf * old;
	};
	GIVEN("A functor that takes integers") {
		class isDivisible {  //Locally defined functor isDivisible
		public:
			isDivisible(int div) : divisor(div) {}
			bool operator()(int num) {
				return num%divisor == 0;
			}
		private:
			int divisor;
		};
		WHEN("Functor isDivisible is used for print_if") {
			vector<int> vec = { 1,2,3,4,7,8,9,13,15,12,14 };
			THEN("When divisor is 2") {
				int divisor = 2;
				cout_redirect redirect(buffer.rdbuf()); //Used to redirect stdout into a stringstream for parsing
				isDivisible p(divisor); //initializing the functor with divisor
				print_if(vec.begin(), vec.end(), p); //Calling print_if
				vector<int> resultVector = toVec<int>(buffer); //converting the buffer into a vector
				REQUIRE(resultVector.size() != 0); //ensure that the size of the vector is non-zero
				for (int& each : resultVector) {
					REQUIRE(each%divisor == 0); //ensure that the functor's statement is true
				}
			}
			THEN("When divisor is 3") {
				int divisor = 3;
				cout_redirect redirect(buffer.rdbuf());
				isDivisible p(divisor);
				print_if(vec.begin(), vec.end(), p);
				vector<int> resultVector = toVec<int>(buffer);
				REQUIRE(resultVector.size() != 0);
				for (int& each : resultVector) {
					REQUIRE(each%divisor == 0);
				}
			}
		}
	}
	GIVEN("A functor that takes characters") {
		class isCharacter {
		public:
			isCharacter(char toFind) : cToFind(toFind) {}
			bool operator()(char curr) {
				return cToFind == curr;
			}
		private:
			char cToFind;
		};
		WHEN("Functor isCharacter is used for print_if") {
			vector<char> vec = { 'D','o','n','\'','t',' ','P','a','n','i','c' };
			THEN("When the char to find is n") {
				char toFind = 'n';
				cout_redirect redirect(buffer.rdbuf());
				isCharacter iC(toFind);
				print_if(vec.begin(), vec.end(), iC);
				vector<char> resultVector = toVec<char>(buffer);
				REQUIRE(resultVector.size() != 0);
				for (char each : resultVector) {
					REQUIRE(each == toFind);
				}
			}
		}
	}
	GIVEN("A functor that takes anything!") {
		WHEN("Functor foo is used for print_if") {
			list<long> l;
			for (long x = 8950; x < 10000; ++x) {
				l.push_front(x);
			}
			THEN("When the value to look for is greater than 9000") {
				long powerLevel = 9000;
				cout_redirect redirect(buffer.rdbuf());
				foo<long> bar(powerLevel);
				print_if(l.begin(), l.end(), bar);
				vector<long> resultVector = toVec<long>(buffer);
				REQUIRE(resultVector.size() != 0);
				for (long& each : resultVector) {
					REQUIRE(each > 9000);
				}
			}
		}
	}
}
