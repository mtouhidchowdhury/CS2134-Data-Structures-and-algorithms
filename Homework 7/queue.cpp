#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

template<class Object>
class Node{
public:
    Object data;
    Node* next;
    Node( const Object & d = Object{}, Node* n = nullptr):data{d},next{n}{}
    Node(Object&& d, Node* n = nullptr): data{std::move(d)}, next{n}{}
};

template<class Object>
class Queue{
    public:
        // vv IMPLEMENT THESE vv
        Object & front();         
        const Object & front() const;
        Object & back();
        const Object & back() const;
        void enqueue(Object obj);
        void dequeue();
        // ^^ IMPLEMENT THESE ^^

        //Note this is NOT in the implementation for queue, but I am putting it here for easier testing.
        Node<Object>*& getHead() {
            return head; 
        }

        //Note this is NOT in the implementation for queue, but I am putting it here for easier testing.
        Node<Object>*& getTail() {
            return tail; 
        }
    private:
        Node<Object>* head;
        Node<Object>* tail;
};


SCENARIO("Testing Queue"){
    GIVEN("A Queue with elements in it"){
        Queue<int> q; 
        Node<int>* start = q.getHead();
        start = new Node<int>(1);
        start->next = new Node<int>(2);
        start->next->next = new Node<int>(3);
        q.getHead() = start;
        q.getTail() = start->next->next;
        WHEN("front() is called"){
            THEN("1 should be at the front"){
                REQUIRE(q.front() == 1); 
            } 
        }
        WHEN("back() is called"){
            THEN("3 should be at the back"){
                REQUIRE(q.back() == 3); 
            } 
        }
        WHEN("enqueue is called"){
            int value = 4;
            q.enqueue(value);
            THEN("There should be a new node in the back with the value"){
                Node<int>* curr = q.getHead();
                while(curr->next != nullptr){
                    curr = curr->next; 
                }
                REQUIRE(curr->data == value);
            } 
        }
        WHEN("dequeue is called"){
            q.dequeue();
            THEN("Then the first element should be changed"){
                REQUIRE(q.getHead()->data != 1) ;
                REQUIRE(q.getHead()->data == 2);
            }
        }
    }
}

