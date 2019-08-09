#define CATCH_CONFIG_MAIN
#include<istream>
#include "Tokenizer.cpp"
#include "catch.hpp"

using namespace std;

// Code from Weiss
// Symbol is the class that will be placed on the Stack.
struct Symbol
{
    char token;
    int  theLine;

};


class Balance
{
public:
    Balance( istream & is ):tok( is ),errors( 0 ){}
    int checkBalance(); // returns the number of mismatched parenthesis
private:
    Tokenizer tok;
    int errors;
    void checkMatch( const Symbol & oParen, const Symbol & cParen );   
};

int Balance::checkBalance(){
}

void Balance::checkMatch(const Symbol & oParen, const Symbol & cParen ){
}

SCENARIO("Checking your Balancer"){
    GIVEN("a test file test.cc with 2 known issues taken in as a ifstream"){
        ifstream ifs("test_cases/test.cc");
        if (!ifs) cerr << "Failure to open file" << endl;
        cerr << "test.cc" << endl;
        WHEN("Given a balancer"){
            Balance b(ifs); 
            THEN("CheckBalance should return 1"){
                REQUIRE(b.checkBalance() == 1);
            }
        }
        ifs.close();
    } 
    GIVEN("a test file test2.cc with 3 known issues taken in as a ifstream"){
        ifstream ifs("test_cases/test2.cc");
        if(!ifs) cerr << "Failure to open file" << endl;
        cerr << "test2.cc" << endl;
        WHEN("Given a balancer"){
            Balance b(ifs);
            THEN("Check balance should return 2"){
                REQUIRE(b.checkBalance() == 2); 
            }
        }
    }
    GIVEN("a test file test3.cc with 0 known issues taken in as a ifstream"){
        ifstream ifs("test_cases/test3.cc");
        if(!ifs) cerr << "Failure to open file" << endl;
        cerr << "test3.cc" << endl;
        WHEN("Given a balancer"){
            Balance b(ifs);
            THEN("Check balance should return 0"){
                REQUIRE(b.checkBalance() == 0); 
            }
        }
    }
}


