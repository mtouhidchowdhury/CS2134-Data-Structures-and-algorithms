#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

/*
Mohammed Touhid Chowdhury
mtc405
hw#1 Programming part
*/



class timer {
public:
	timer() : start(clock()) {}
	double elapsed() { return (clock() - start) / CLOCKS_PER_SEC; }
	void reset() { start = clock(); }
private:
	double start;
};

//Use the following code from Weiss’ book ”Data Structures and Algorithm Analysis in C++” (4th edition) http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/MaxSumTest.cpp


/**
* Cubic maximum contiguous subsequence sum algorithm.
*/
int maxSubSum1(const vector<int> & a)
{
	int maxSum = 0;

	for (size_t i = 0; i < a.size(); ++i)
		for (size_t j = i; j < a.size(); ++j)
		{
			int thisSum = 0;

			for (size_t k = i; k <= j; ++k)
				thisSum += a[k];

			if (thisSum > maxSum)
				maxSum = thisSum;
		}

	return maxSum;
}


/**
* Quadratic maximum contiguous subsequence sum algorithm.
*/
int maxSubSum2(const vector<int> & a)
{
	int maxSum = 0;

	for (size_t i = 0; i < a.size(); ++i)
	{
		int thisSum = 0;
		for (size_t j = i; j < a.size(); ++j)
		{
			thisSum += a[j];

			if (thisSum > maxSum)
				maxSum = thisSum;
		}
	}

	return maxSum;
}


/**
* Linear-time maximum contiguous subsequence sum algorithm.
*/
int maxSubSum4(const vector<int> & a)
{
	int maxSum = 0, thisSum = 0;

	for (size_t j = 0; j < a.size(); ++j)
	{
		thisSum += a[j];

		if (thisSum > maxSum)
			maxSum = thisSum;
		else if (thisSum < 0)
			thisSum = 0;
	}

	return maxSum;
}

void function2b(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		++sum;
	}
}

void function2c(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; ++j)
			++sum;
}

void function2d(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; ++j)
			++sum;
}

void function2e(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				++sum;
}








int main(){
	//checking the computer's clock system resolution
	cout << "Clock_PER_SEC is : " << CLOCKS_PER_SEC << endl;
	//making sure enough significant digits are printed
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(6);

	timer t;
	double numClicks;
	vector<int> randomNumbers;

	for (size_t i = 0; i < 128; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum1(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum1(128) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 256; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum1(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum1(256) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 512; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum1(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum1(512) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 1024; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum1(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum1(1024) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 2048; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum1(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum1(2048) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 4096; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum1(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum1(4096) is : " << numClicks << endl;
	randomNumbers.clear();

	//using the function maxSubSum2()

	for (size_t i = 0; i < 128; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum2(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum2(128) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 256; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum2(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum2(256) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 512; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum2(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum2(512) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 1024; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum2(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum2(1024) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 2048; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum2(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum2(2048) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 4096; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum2(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum2(4096) is : " << numClicks << endl;
	randomNumbers.clear();


	//using the function maxSubSum4()

	for (size_t i = 0; i < 128; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum4(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum4(128) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 256; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum4(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum4(256) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 512; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum4(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum4(512) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 1024; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum4(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum4(1024) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 2048; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum4(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum4(2048) is : " << numClicks << endl;
	randomNumbers.clear();

	for (size_t i = 0; i < 4096; i++) {
		int x = (rand() % 2001) - 1000;
		randomNumbers.push_back(x);
	}
	t.reset();
	maxSubSum4(randomNumbers);
	numClicks = t.elapsed();
	cout << "The time to run maxSubSum4(4096) is : " << numClicks << endl;
	randomNumbers.clear();

	cout << "PART 1 QUESTION 2: " << endl;

	t.reset();
	function2b(256);
	numClicks = t.elapsed();
	cout << "The time to run function 2b with n = 256 is: " << numClicks << endl;

	t.reset();
	function2b(512);
	numClicks = t.elapsed();
	cout << "The time to run function 2b with n = 512 is: " << numClicks << endl;

	t.reset();
	function2b(1024);
	numClicks = t.elapsed();
	cout << "The time to run function 2b with n = 1024 is: " << numClicks << endl;

	t.reset();
	function2b(2048);
	numClicks = t.elapsed();
	cout << "The time to run function 2b with n = 2048 is: " << numClicks << endl;

	t.reset();
	function2b(4096);
	numClicks = t.elapsed();
	cout << "The time to run function 2b with n = 4096 is: " << numClicks << endl;

	t.reset();
	function2c(256);
	numClicks = t.elapsed();
	cout << "The time to run function 2c with n = 256 is: " << numClicks << endl;

	t.reset();
	function2c(512);
	numClicks = t.elapsed();
	cout << "The time to run function 2c with n = 512 is: " << numClicks << endl;

	t.reset();
	function2c(1024);
	numClicks = t.elapsed();
	cout << "The time to run function 2c with n = 1024 is: " << numClicks << endl;

	t.reset();
	function2c(2048);
	numClicks = t.elapsed();
	cout << "The time to run function 2c with n = 2048 is: " << numClicks << endl;

	t.reset();
	function2c(4096);
	numClicks = t.elapsed();
	cout << "The time to run function 2c with n = 4096 is: " << numClicks << endl;

	t.reset();
	function2d(256);
	numClicks = t.elapsed();
	cout << "The time to run function 2d with n = 256 is: " << numClicks << endl;

	t.reset();
	function2d(512);
	numClicks = t.elapsed();
	cout << "The time to run function 2d with n = 512 is: " << numClicks << endl;

	t.reset();
	function2d(1024);
	numClicks = t.elapsed();
	cout << "The time to run function 2d with n = 1024 is: " << numClicks << endl;

	t.reset();
	function2d(2048);
	numClicks = t.elapsed();
	cout << "The time to run function 2d with n = 2048 is: " << numClicks << endl;

	t.reset();
	function2d(4096);
	numClicks = t.elapsed();
	cout << "The time to run function 2d with n = 4096 is: " << numClicks << endl;

	t.reset();
	function2e(256);
	numClicks = t.elapsed();
	cout << "The time to run function 2e with n = 256 is: " << numClicks << endl;

	t.reset();
	function2e(512);
	numClicks = t.elapsed();
	cout << "The time to run function 2e with n = 512 is: " << numClicks << endl;

	t.reset();
	function2e(1024);
	numClicks = t.elapsed();
	cout << "The time to run function 2e with n = 1024 is: " << numClicks << endl;

	t.reset();
	function2e(2048);
	numClicks = t.elapsed();
	cout << "The time to run function 2e with n = 2048 is: " << numClicks << endl;

	t.reset();
	function2e(4096);
	numClicks = t.elapsed();
	cout << "The time to run function 2e with n = 4096 is: " << numClicks << endl;


}
