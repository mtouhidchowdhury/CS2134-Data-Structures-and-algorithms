#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <functional>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
using namespace std;
/*
Mohammed Touhid Chowdhury 
mtc405
N14108583
hw5 q 1, 2 
*/

class trainStopData {
public:
	trainStopData(const string& id, const string& name, double lat, double lon)
		: stop_id(id), stop_name(name), stop_lat(lat), stop_lon(lon) {}

	string get_id()         const { return stop_id; }
	string get_stop_name()  const { return stop_name; }
	double get_latitude()   const { return stop_lat; }
	double get_longitude()  const { return stop_lon; }
private:
	string stop_id;
	string stop_name;
	double stop_lat;
	double stop_lon;
};

double degrad(double d) {
	return d * M_PI / 180;
}


// Code below is adapted from http://www.movable-type.co.uk/scripts/latlong.html
// FYI: That website has an applet that computes the haversine distance. 
// It also has a link that will show the locations on a map,
// with a line between them.
double haverdist(double lat1, double longit1, double lat2, double longit2)
{
	double r = 6371;
	double dlat = degrad(lat2 - lat1);
	double dlongit = degrad(longit2 - longit1);
	double a = sin(dlat / 2)*sin(dlat / 2) +
		cos(degrad(lat1))*cos(degrad(lat2))*sin(dlongit / 2)*sin(dlongit / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	return r*c;
}


/*using the solution's 4b*/
void parseTrainData(vector<trainStopData>& trainStops) {
    ifstream stopFile("MTA_train_stop_data.txt");
    if (!stopFile) {
        cerr << "The file for train stop data cannot be found.\n";
        exit(1);
    }
    string line;
    getline(stopFile, line);
    while (getline(stopFile, line)) {
        string element;
        stringstream eachLine(line);
        vector<string> allElements;
        while (getline(eachLine, element, ',')) { allElements.push_back(element); }
        double lat = atof(allElements[4].c_str());
        double lon = atof(allElements[5].c_str());
        
        string IDtoCut = allElements[0].substr(0,3);
        allElements[0] = IDtoCut;
 
        bool testIfExist = false;
        for (size_t i = 0; i < trainStops.size() ; i++){
            if (allElements[0]==trainStops[i].get_id()){
                testIfExist = true;
            }
        }
		if (testIfExist == false) {
			trainStops.push_back(trainStopData(allElements[0], allElements[2], lat, lon));
		}
    }
        stopFile.close();
}

template <class Iterator, class Pred, class Op>
int perform_if(Iterator& itrStart, Iterator& itrEnd, Pred pred, Op op) {
    int count = 0;
    for (Iterator i = itrStart; i != itrEnd; ++i) {
        if (pred(*i)) {
            op(*i);
            count++;
        }
    }
    return count;
}

class isStopOnRoute {
public:
    isStopOnRoute(char letter) : route(letter) {}
    bool operator()(trainStopData& stop){
        string id = stop.get_id();
        if (id[0] == route) {
            return true;
        }
        return false;
    }
private:
    char route;
};


class isSubwayStop {
public:
    isSubwayStop(string idNum) : stopId(idNum) {}
    bool operator()(trainStopData stop) {
        if (stop.get_id() == stopId) {
            return true;
        }
        return false;
    }
private:
    string stopId;
};

class isSubwayStopNearX {
public:
    isSubwayStopNearX(double lat, double lon, double d) : latitude(lat), longitude(lon), d(d) {}
    bool operator()(trainStopData stop){
        if (haverdist(latitude, longitude, stop.get_latitude(), stop.get_longitude()) < d) {
            return true;
        }
        return false;
    }
private:
    double latitude;
    double longitude;
    double d;
};


class printTrainStopInfo {
public:
    void operator()(const trainStopData& stop) {
        cout << "Stop ID: " << stop.get_id() << endl <<
			" Stop Name: " << endl <<
			stop.get_stop_name() << endl<<
			" Location: " << stop.get_latitude() << endl << 
			stop.get_longitude() << endl;
    }
};

void trainStopMenu(vector<trainStopData>& stops) {
	cout << "Welcome User!" << endl;
	cout << " Enter 1 to print out the information about all the train stops on a specific route." << endl <<
		"enter 2 to print out the information about a specific train stop by entering the id." << endl <<
		"enter 3 to print out all the train stops within a certain distance." << endl <<
		"enter 4 to leave the program." << endl;
	string user;
	cin >> user;
	while (user != "4") {
		if (user == "1") {
			cout << "enter the route you want to know about: " << endl;
			char userRoute;
			cin >> userRoute;
			perform_if(stops.begin(), stops.end(), isStopOnRoute(userRoute), printTrainStopInfo());
		}
		else if (user == "2") {
			cout << "enter the stop id you want to know about: " << endl;
			string userStop;
			cin >> userStop;
			perform_if(stops.begin(), stops.end(), isSubwayStop(userStop), printTrainStopInfo());
		}
		else if (user == "3") {
			double latitude;
			double longitude;
			double distance;
			cout << "enter the latitude: " << endl;
			cin >> latitude;
			cout << "enter the longitude: " << endl;
			cin >> longitude;
			cout << "enter the max distance: " << endl;
			cin >> distance;
			isSubwayStopNearX nearStop(latitude, longitude, distance);
			perform_if(stops.begin(), stops.end(), nearStop, printTrainStopInfo());
		}
		else if (user == "4") {
			return;
		}
		else {
			cout << "couldnt understand please re enter: " << endl;
		}
		cout << "enter another command or enter 4 to quit" << endl;
		cin >> user;
	}
	
}

int main() {
	vector<trainStopData> dataHolder;
	parseTrainData(dataHolder);
	trainStopMenu(dataHolder);
}