#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


// Get point values from the file and store them in the vector
void initValues (vector<int>& pointValues) {

}

// Compute point value of a word
int wordValue (const vector<int>& pointValues, const string& word) {

}

// Store all words and their point values in the map
void initWords (const vector<int>& pointValues, map<string, int>& wordValues) {

}

SCENARIO("Testing words with friends"){
    GIVEN("Given a map and vector"){
        vector<int> pointValues(26,0); 
        map<string, int> wordValues;
        WHEN("The map is initialized with this vector with word values"){
            initValues(pointValues);
            initWords(pointValues, wordValues);       
            THEN("abacterial should be valued 17"){
                string test = "abacterial";
                map<string, int>::iterator itr = wordValues.find(test);
                REQUIRE(itr->second == 17);
            }
            THEN("zyzzyva should be valued 42"){
                 string test = "zyzzyva";
                 map<string, int>::iterator itr = wordValues.find(test);
                 REQUIRE(itr->second == 42);
             }
             THEN("fuzees should be valued 19"){
                string test = "fuzees";
                map<string, int>::iterator itr = wordValues.find(test);
                REQUIRE(itr->second == 19);
             }
             THEN("poly should be valued 10"){
                string test = "poly";
                map<string, int>::iterator itr = wordValues.find(test);
                REQUIRE(itr->second == 10);
             }
        }
    }
}

