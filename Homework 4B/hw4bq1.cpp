#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
/*
Mohammed Touhid Chowdhury 
mtc405 
N14108583
hw4b q1 
*/

class trainStopData {

public:
	//Constructor
	trainStopData(const string& id, const string& name, double latitude, double longitude)
		: stop_id(id), stop_name(name), stop_lat(latitude), stop_lon(longitude) {}

	//Methods to get the information
	string get_id() const { return stop_id; }
	string get_stop_name() const { return stop_name; }
	double get_latitude() const { return stop_lat; }
	double get_longitude() const { return stop_lon; }

private:
	string stop_id;
	string stop_name;
	double stop_lat;
	double stop_lon;
};


void parseTrainData(vector<trainStopData>& vecData) {
	string line;
	ifstream MTADataFile("MTA_train_stop_data.txt");
	getline(MTADataFile, line);
	while (getline(MTADataFile, line)) { //while stream isnt finished
		stringstream datastream(line);
		string ID;
		string name;
		string latitude; 
		string longitude;
		string empty;
		getline(datastream, ID, ',');
		getline(datastream, empty, ',');
		getline(datastream, name, ',');
		getline(datastream, empty, ',');
		getline(datastream, latitude, ',');
		getline(datastream, longitude, ',');
		trainStopData aTrainStop(ID, name, atof(latitude.c_str()), atof(longitude.c_str()));
		vecData.push_back(aTrainStop);
	}
	MTADataFile.close();

}


SCENARIO("Testing vector<trainStopData>") {
	GIVEN("A vector with trainStopData") {
		vector<trainStopData> test;
		parseTrainData(test);
		WHEN("Checking the size") {
			int size = test.size();
			THEN("The size should be 1482") {
				REQUIRE(size == 1482); //testing if the vector contains all the data
			}
		}
		WHEN("Getting stop_id") {
			string id = test[100].get_id(); //test a random data
			THEN("A valid id should be not nothing") {
				REQUIRE(id != "");
			}
		}
		WHEN("Getting stop_name") {
			string name = test[1000].get_stop_name(); //test a random data
			THEN("A valid name should be not nothing") {
				REQUIRE(name != "");
			}
		}
		WHEN("Getting latitude") {
			double lat = test[10].get_latitude(); //test a random data
			THEN("A valid latitude should be not nothing") {
				REQUIRE(lat != 0);
			}
		}
		WHEN("Getting longitude") {
			double lon = test[10].get_longitude(); //test a random data
			THEN("A valid longitude should be not nothing") {
				REQUIRE(lon != 0);
			}
		}
	}
}
