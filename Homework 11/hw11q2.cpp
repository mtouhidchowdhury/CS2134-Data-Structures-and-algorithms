
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
/*
Mohammed Touhid Chowdhury 
mtc405
hw11 q2 
*/
using namespace std;
const int DEFAULT_VAL = -1;

class trainStopData {
public:
	trainStopData(const string& id, const string& name, double latitude, double longitude)
		: stop_id(id), stop_name(name), stop_lat(latitude), stop_lon(longitude) {}
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


void addTrainStops(const string& fileName, unordered_map< string, list<string> >& adjacencyList) {
	string line;
	ifstream ifs(fileName);
	if (!ifs) {
		cerr << "File not found" << endl;
		exit(1);
	}
	getline(ifs, line);
	vector<string> allStops;
	while (getline(ifs, line)) {
		stringstream datastream(line);
		string ID;
		getline(datastream, ID, ',');
		if (ID[ID.size() - 1] != 'S' && ID[ID.size() - 1] != 'N') {
			allStops.push_back(ID);
		}
	}
	size_t i = 0;
	while (i < allStops.size() - 1) {
		if (allStops[i][0] == allStops[i + 1][0]) {
			adjacencyList[allStops[i]].push_back(allStops[i + 1]);
			adjacencyList[allStops[i + 1]].push_back(allStops[i]);
		}
		i++;
	}

	ifs.close();
}

void addAdjacentStops(const string& fileName, unordered_map< string, list<string> >& adjacencyList) {
	string line;
	ifstream ifs(fileName);
	if (!ifs) {
		cerr << "File not found" << endl;
		exit(1);
	}
	getline(ifs, line);
	while (getline(ifs, line)) {
		stringstream datastream(line);
		string startStop, endStop;
		getline(datastream, startStop, ',');
		getline(datastream, endStop, ',');
		if (startStop != endStop) {
			adjacencyList[startStop].push_front(endStop);
		}
	}
	ifs.close();
}
struct vertexInf {
	vertexInf(int val = DEFAULT_VAL, const string id = string()): dist(val), prev(id) {}
	int dist;
	string prev;
};
void printpath(const string& j, const unordered_map<string, vertexInf>& allData) {
	stack<string> stackPrint;
	string current = j;
	while (current != "") {
		stackPrint.push(current);
		current = allData.at(current).prev;
	}
	while (!stackPrint.empty()) {
		cout << stackPrint.top() << " ";
		stackPrint.pop();
	}
}
void shortestpaths(const unordered_map< string, list<string> >& adjList, const string& begin, const string& end) {
	queue<string> myQueue;
	unordered_map<string, vertexInf> allDistance;
	for (auto it = adjList.begin(); it != adjList.end(); ++it){
		vertexInf vertx;
		allDistance[(*it).first] = vertx;
	}
	allDistance[begin].dist = 0;
	myQueue.push(begin);
	while (!myQueue.empty()) {
		string vertex = myQueue.front();
		myQueue.pop();
		list<string>::const_iterator a = (adjList.find(vertex)->second).begin();
		while (a != (adjList.find(vertex)->second).end())
		{
			if (allDistance[*a].dist == DEFAULT_VAL) {
				allDistance[*a].dist = allDistance[vertex].dist + 1;
				allDistance[*a].prev = vertex;
				myQueue.push(*a);
			}
			a++;
		}
	}
	cout << "vertex " << begin << endl;
	cout << "distance: " << allDistance[end].dist << endl;
	cout << "shortest path: ";
	printpath(end, allDistance);
	cout << endl;

}

int main() {
	unordered_map < string, list<string> > adjacencyList;
	addTrainStops("MTA_train_stop_data.txt",adjacencyList);
	addAdjacentStops("transfers.txt", adjacencyList);
	//checking from M01 to M08
	shortestpaths(adjacencyList, "M01", "M08");
	//checking from 111 to 112 
	shortestpaths(adjacencyList, "111", "112");
}
