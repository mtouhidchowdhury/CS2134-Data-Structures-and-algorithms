#include <iostream>
#include <string>
using namespace std;


/*
Mohammed Touhid Chowdhury
mtc405
N14108583
Programming part, q 2 and 3
*/

//part 3
template< class anObject>
class compareLength {
public:
	bool operator()(const anObject& firstObject, const anObject& secondObject) {
		return (firstObject.length() < secondObject.length());
	}
};

//PART 2
template <class object>
class checkEvenOdd {
public:
	string operator()(const object& anObject) {
		return (anObject % 2 == 0) ? "even" : "odd";
	}
};


int main()
{
    int x = 5;
    int y = 6;
    checkEvenOdd<int> anObj;
    cout <<"the number 6 is "<< anObj(y) << endl;
    cout <<"the number 5 is "<< anObj(x) << endl;
    compareLength<string> anotherObj;
    string wordCar = "car";
    string wordAnimal = "animal";
    cout <<"(for the following, 0 is false and 1 is true ):" << endl;
    cout << "the string 'car' is bigger than string 'animal' is " << anotherObj(wordAnimal,wordCar) << endl;
}
