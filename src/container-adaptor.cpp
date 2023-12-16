#include <stack>
#include <queue>
#include <vector>
#include <deque>
#include <string>
#include <iostream>

using namespace std;

// * In C++, vector and deque actually give all the functionalites
// * while stack and queue just use a limited functionalities of vector and deque.
// * Stack just limit the functionality of a vector/deque to only allow `push_back` and `pop_back`
// * Queue just limit the functionality of a deque to only allow `push_back` and `pop_front`
// * That's the reason why the are called `Container Adaptors`, they just adapt the sequence container
// * Actually, we can even implement our own classes which support `push_back` and `pop_back` to build a stack based on our own classes
// * Similarly, we can use our own classes which has `push_back` and `pop_front` as the fundament for queue

void useStack();
void useQueue();

int main(int argc, char *argv[])
{
    return 0;
}