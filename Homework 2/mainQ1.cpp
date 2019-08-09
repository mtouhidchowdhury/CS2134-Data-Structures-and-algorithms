#define CATCH_CONFIG_MAIN
#include<math.h>
#include "Header.h"
#include<iostream>
/*
Mohammed Touhid Chowdhury 
mtc405
N14108583
hw 2 coding part, q1
*/
using namespace std;
class IntArray {
public:
	IntArray(int n = 0) : size(n), array(new int[n]) {}
	void put(int  i, int value);
	int get(int i);
	int* getArray();

	// deep copy constructor 
	IntArray(const IntArray& rhs) {
		array = new int[rhs.size]; //build new array 
		size = rhs.size;
		for (size_t i = 0; i < rhs.size; ++i) { //copy over all the data
			array[i] = rhs.array[i];
		}
	}

	// destructor 
	~IntArray() { delete[] array; } //delete resources

	// copy assignment operator 
	IntArray& operator=(const IntArray& rhs) {
		if (this != &rhs) { //self assignment check 
			delete[] array; //delete old resources
			array = new int[rhs.size];   //copy over the rhs data
			size = rhs.size;
			for (size_t i = 0; i < rhs.size; i++) {
				array[i] = rhs.array[i];
			}
		}
		return *this;
	}
	//move constructor 
	IntArray(IntArray&& rhs) :size(rhs.size) {
		array = rhs.array; //copy right hand side data and set rhs to null 
		rhs.size = 0;
		rhs.array = nullptr;
	}
	//move assignment operator 
	IntArray& operator=(IntArray&& rhs){
		if (this != &rhs) {
			swap(size, rhs.size); //swap the resources and set rhs to null
			swap(array, rhs.array);
			//IF THE SWAP WASNT USE THE CODE WOULD BE :
			//int* tempSize = size;
			//size = rhs.size;
			//rhs.size = tempSize;
			//int* tempArray = array;
			//array = rhs.array;
			//rhs.array = tempArray;
			rhs.array = nullptr;
		}
		return *this;
	}


private:
	int * array;
	int size;
};




void IntArray::put(int i, int value) {
	if (0 <= i && i < size) {
		*(array + i) = value;
	}
}

int IntArray::get(int i) {
	if (0 <= i && i < size) {
		return *(array + i);
	}
	return 0;
}

int* IntArray::getArray() {
	return array;
}

// Tests everything but the destructor
SCENARIO("Testing the IntArray Class") {
	GIVEN("An instance of IntArray") {
		int size = 12;
		IntArray arr(size);
		WHEN("Values are inserted") {
			int TheAnswer = 42;
			int NotTheAnswer = 83;
			arr.put(0, TheAnswer);
			arr.put(1, TheAnswer);
			arr.put(11, TheAnswer);
			arr.put(10, NotTheAnswer);
			THEN("The values should be retrievable from the array") {
				REQUIRE(arr.get(0) == TheAnswer);
				REQUIRE(arr.get(1) == TheAnswer);
				REQUIRE(arr.get(11) == TheAnswer);
				REQUIRE(arr.get(10) == NotTheAnswer);
			}
			THEN("A value that is out of bounds is attempted to be accessed should return zero") {
				int OutOfBounds = 100;
				REQUIRE(arr.get(OutOfBounds) == 0);
			}
		}
		WHEN("The Copy Constructor is invoked") {
			IntArray copyArray(arr);
			THEN("Changing the value of index 0 in one array should NOT impact the other") {
				int randomValue = 32;
				int ind1 = 0;
				copyArray.put(ind1, randomValue);
				REQUIRE(copyArray.get(ind1) == randomValue);
				REQUIRE(arr.get(ind1) != randomValue);
			}
			THEN("Changing the value of any random index in one array should NOT impact the other") {
				int otherRandomValue = rand() % size;
				int ind2 = 5;
				copyArray.put(ind2, otherRandomValue);
				REQUIRE(copyArray.get(ind2) == otherRandomValue);
				REQUIRE(arr.get(ind2) != otherRandomValue);
			}
		}
		WHEN("The Copy Assignment Constructor is invoked") {
			IntArray copyArray(15);
			int val1 = 12;
			int val2 = 14;
			int val3 = 28;
			copyArray.put(0, val1);
			copyArray.put(1, val2);
			copyArray.put(2, val3);
			copyArray = arr;
			THEN("The values of copyArray should be the values of arr") {
				REQUIRE(copyArray.get(0) == arr.get(0));
				REQUIRE(copyArray.get(1) == arr.get(1));
				REQUIRE(copyArray.get(2) == arr.get(2));
			}
			THEN("The values though should be at different locations in memory") {
				REQUIRE(copyArray.getArray() != arr.getArray());
			}
		}
		WHEN("The Move Constructor is invoked") {
			IntArray moveArray(move(arr));

			THEN("the old array should point to nullptr") {
				bool isGood = false;
				if (arr.getArray() == nullptr) {
					isGood = true;
				}
				REQUIRE(isGood);
			}
			THEN("The new array should not be pointing to a nullptr") {
				bool isGood = false;
				if (moveArray.getArray() != nullptr) {
					isGood = true;
				}
				REQUIRE(isGood);
			}
		}
		WHEN("The Move Assignment Operator is invoked") {
			IntArray oneArray(15);
			int* arr1Loc = oneArray.getArray();
			int* arrLoc = arr.getArray();
			oneArray = move(arr);
			THEN("The new array should not be pointing to old, but to arr's") {
				REQUIRE(oneArray.getArray() != arr1Loc);
				REQUIRE(oneArray.getArray() == arrLoc);
			}

			THEN("The array of the original should be nullptr") {
				bool isGood = false;
				if (arr.getArray() == nullptr) {
					isGood = true;
				}
				REQUIRE(isGood);
			}
		}
	}
}
