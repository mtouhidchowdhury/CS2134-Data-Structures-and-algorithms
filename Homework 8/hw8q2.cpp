#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
/*
Mohammed TOuhid CHowdhury 
mtc405
hw8 q2 
*/

// Get point values from the file and store them in the vector
void initValues(vector<int>& pointValues) {
	int pointValue;
	char letter;
	ifstream pointValFile("Letter_point_value.txt");
	if (!pointValFile) { cerr << "couldnt open the file" << endl; }
	while (pointValFile >> pointValue) {
		pointValFile >> letter;
		pointValues[letter - 65] = pointValue;
	}
	pointValFile.close();
}

// Compute point value of a word
int wordValue(const vector<int>& pointValues, const string& word) {
	int sum = 0;
	for (unsigned i = 0; i < word.size(); i++) {
		sum += pointValues[toupper(word[i]) - 65];
		
	}
	return sum;
}

// Store all words and their point values in the map
void initWords(const vector<int>& pointValues, map<string, int>& wordValues) {
	string word;
	ifstream wordFile("ENABLE.txt");
	if (!wordFile) { cerr << "couldnt find file" << endl; }
	while (wordFile >> word) {
		int sum = wordValue(pointValues, word);
		wordValues[word] = sum;
	}
	wordFile.close();
}

SCENARIO("Testing words with friends") {
	GIVEN("Given a map and vector") {
		vector<int> pointValues(26, 0);
		map<string, int> wordValues;
		WHEN("The map is initialized with this vector with word values") {
			initValues(pointValues);
			initWords(pointValues, wordValues);
			THEN("abacterial should be valued 17") {
				string test = "abacterial";
				map<string, int>::iterator itr = wordValues.find(test);
				REQUIRE(itr->second == 17);
			}
			THEN("zyzzyva should be valued 42") {
				string test = "zyzzyva";
				map<string, int>::iterator itr = wordValues.find(test);
				REQUIRE(itr->second == 42);
			}
			THEN("fuzees should be valued 19") {
				string test = "fuzees";
				map<string, int>::iterator itr = wordValues.find(test);
				REQUIRE(itr->second == 19);
			}
			THEN("poly should be valued 10") {
				string test = "poly";
				map<string, int>::iterator itr = wordValues.find(test);
				REQUIRE(itr->second == 10);
			}
		}
	}
}

