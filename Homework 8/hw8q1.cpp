#define CATCH_CONFIG_MAIN
#include<istream>
#include "Tokenizer.cpp"
#include "catch.hpp"

using namespace std;
/*
Mohammed Touhid Chowdhury 
mtc405 
N14108583
hw8 q1
*/
// Code from Weiss
// Symbol is the class that will be placed on the Stack.
struct Symbol
{
	char token;
	int  theLine;

};


class Balance
{
public:
	Balance(istream & is) :tok(is), errors(0) {}
	int checkBalance(); // returns the number of mismatched parenthesis
private:
	Tokenizer tok;
	int errors;
	void checkMatch(const Symbol & oParen, const Symbol & cParen);
};

int Balance::checkBalance() {
	stack<Symbol> parans;
	Symbol holder;
	holder.token = tok.getNextOpenClose();
	holder.theLine = tok.getLineNumber();
	while (holder.token != '\0') {
		if (holder.token == '(') {
			parans.push(holder);
		}
		else if (holder.token == ')') {
			if (parans.empty()) {
				cout << "Extra closing bracket on line " << holder.theLine << endl;
				++errors;
			}
			else {
				checkMatch(parans.top(), holder);
				parans.pop();
			}
		}

		holder.token = tok.getNextOpenClose();
		holder.theLine = tok.getLineNumber();
	}
	while (!parans.empty()) {
		cout << "Extra bracket on line " << parans.top().theLine << endl;
		parans.pop();
		++errors;
	}
	return errors;
}

void Balance::checkMatch(const Symbol & oParen, const Symbol & cParen) {
	if (oParen.token == '(' && cParen.token != ')') {
		cout << "The opening bracket at " << oParen.theLine << " doesn't match the bracket at " << cParen.theLine << "." << endl;
		errors++;
	}
	
	
}

SCENARIO("Checking your Balancer") {
	GIVEN("a test file test.cc with 2 known issues taken in as a ifstream") {
		ifstream ifs("test_cases/test.cc");
		if (!ifs) cerr << "Failure to open file" << endl;
		cerr << "test.cc" << endl;
		WHEN("Given a balancer") {
			Balance b(ifs);
			THEN("CheckBalance should return 1") {
				REQUIRE(b.checkBalance() == 1);
			}
		}
		ifs.close();
	}
	GIVEN("a test file test2.cc with 3 known issues taken in as a ifstream") {
		ifstream ifs("test_cases/test2.cc");
		if (!ifs) cerr << "Failure to open file" << endl;
		cerr << "test2.cc" << endl;
		WHEN("Given a balancer") {
			Balance b(ifs);
			THEN("Check balance should return 2") {
				REQUIRE(b.checkBalance() == 2);
			}
		}
	}
	GIVEN("a test file test3.cc with 0 known issues taken in as a ifstream") {
		ifstream ifs("test_cases/test3.cc");
		if (!ifs) cerr << "Failure to open file" << endl;
		cerr << "test3.cc" << endl;
		WHEN("Given a balancer") {
			Balance b(ifs);
			THEN("Check balance should return 0") {
				REQUIRE(b.checkBalance() == 0);
			}
		}
	}
}


