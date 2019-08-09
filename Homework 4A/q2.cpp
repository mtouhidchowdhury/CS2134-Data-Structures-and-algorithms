#define CATCH_CONFIG_MAIN
#include "catch.hpp"
/*
Mohammed Touhid Chowdhury .
mtc405 
N14108583
Hw 4 programming part q2 
*/
int sumDigits(int x) {
	if (x < 0) { x = -x; } // allowing negative integers
	if (x < 10) { return x; } // base case: only one integer left 
	else {
		return x % 10 + sumDigits(x / 10); // remove the last digit and add it 
	}
}

SCENARIO("Testing Question 2") {
	GIVEN("A one digit positive integer ") {
		WHEN("sumDigits is called") {
			int sum = sumDigits(5);
			THEN("theSum should be ") {
				REQUIRE(sum == 5);
			}
		}
	}
	GIVEN("A one digit negative integer") {
		WHEN("sumDigits is called") {
			int sum = sumDigits(-5);
			THEN("theSum should be ") {
				REQUIRE(sum == 5);
			}
		}
	}
	GIVEN("A positive integer ") {
		WHEN("sumDigits is called") {
			int sum = sumDigits(363);
			THEN("theSum should be ") {
				REQUIRE(sum == 12);
			}
		}
	}
	GIVEN("A negative integer") {
		WHEN("sumDigits is called") {
			int sum = sumDigits(-363);
			THEN("theSum should be ") {
				REQUIRE(sum == 12);
			}
		}
	}
}