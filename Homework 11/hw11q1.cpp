#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include<iostream>
#include<vector>
#include<queue>
/*Mohammed touhid Chowdhury 
hw11 q1 
*/
using namespace std;


template <class Comparable>
void print_kth_largest(const vector<Comparable>& a, int k) {
	priority_queue<Comparable> aQueue(a.begin(), a.end());
	while (k != 0) {
		cout << aQueue.top() << endl;
		aQueue.pop();
		--k;
	}
}

//Done for the unit test
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



SCENARIO("Testing kth_largest") {
	stringstream buffer;
	struct cout_redirect {
		cout_redirect(streambuf * new_buffer) : old(cout.rdbuf(new_buffer)) {}
		~cout_redirect() {
			cout.rdbuf(old);
		}
	private:
		streambuf * old;
	};
	GIVEN("A vector of integers") {
		vector<int> testVec = { 5,1,2,4,3 };
		WHEN("print_kth_largest is called") {
			cout_redirect redirect(buffer.rdbuf());
			print_kth_largest(testVec, 2);
			vector<int> resVec = toVec<int>(buffer);
			THEN("5 and 4 should be printed") {
				REQUIRE(resVec.size() == 2);
				REQUIRE(resVec[0] == 5);
				REQUIRE(resVec[1] == 4);
			}
		}
	}
}