#define CATCH_CONFIG_MAIN

#include <vector>
#include "catch.hpp"

using namespace std;
/*
Mohammed Touhid Chowdhury .
mtc405
N14108583
hw4 q3 programming part: 
*/
int recursionSum(vector<int>::iterator itrBegin, const vector<int>::iterator itrEnd) {
	//base cases 
	if (itrBegin == itrEnd) { return 0; } // both are a.end()
	if (itrBegin + 1 == itrEnd) { return *itrBegin; } // only one remaining 


	int center = (itrEnd - itrBegin) / 2;
	vector<int>::iterator middle = itrBegin + center;
	int leftSum = recursionSum(itrBegin, middle);
	int rightSum = recursionSum(middle, itrEnd);
	return leftSum + rightSum;


}
int sumVector(vector<int>& a) {
	//if the vector is empty just return 0 
	if (a.size() == 0) {
		return 0;
	}
	//if the vector has just one element just return that element
	else if (a.size() == 1) {
		return a[0];
	}
	//if more than one element, do recursion 
	else {
		int total = recursionSum(a.begin(), a.end());
		return total;
	}
}


SCENARIO("Testing sumVector") {
	GIVEN("A vector with just one element") {
		vector<int> singleElement = { 1 }; //Note that this is the STL vector, so we can initialize like this
		WHEN("The sumVector function is called") {
			int sum = sumVector(singleElement);
			THEN("The correct sume is returned") {
				REQUIRE(sum == 1); //testing base case
			}
		}
	}
	GIVEN("A vector with odd number of integers ") {
		vector<int> vOdd = { 1,2,3 };
		WHEN("sumVector function is called ") {
			int recSum = sumVector(vOdd);

			vector<int>::iterator itrStart = vOdd.begin();
			vector<int>::iterator itrEnd = vOdd.end();

			int sizeVector = vOdd.size();

			THEN("vector stays same after the function call") {
				REQUIRE(itrStart == vOdd.begin());
				REQUIRE(itrEnd == vOdd.end());
			}
			THEN("The size of the vector doesn't change") {
				REQUIRE(sizeVector == vOdd.size());
			}
			THEN("It sums up properly") {
				REQUIRE(recSum == 6);
			}
		}
		GIVEN("A vector with even number of integers ") {
			vector<int> vEven = { 1,2,3,10 };

			vector<int>::iterator itrStart = vEven.begin();
			vector<int>::iterator itrEnd = vEven.end();

			int sizeVector = vEven.size();

			WHEN("sumVector function is called ") {

				int recSum = sumVector(vEven);

				THEN("vector stays same after the function call") {
					REQUIRE(itrStart == vEven.begin());
					REQUIRE(itrEnd == vEven.end());
				}
				THEN("The size of the vector doesn't change") {
					REQUIRE(sizeVector == vEven.size());
				}
				THEN("It sums up properly") {
					REQUIRE(recSum == 16);
				}
			}
		}
	}
}