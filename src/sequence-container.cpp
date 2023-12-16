#include <list>
#include <deque>
#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <forward_list>

using namespace std;

// = There is five types of sequence coantainer
// *    1. vector
// *    2. deque
// *    3. list
// *    4. forward_list
// *    5. array
//
// * Vector is efficient at push_back and pop_back, but lack of push_front and pop_front
// * Deque supports push_front and pop_front, but is low efficiency compared to vector at push_back and pop_back
// * List is double linked list, which is efficient at inserting and deleting compared to vector
// * Forward_list is single list, similar to list but can only access next element
// * Array is fixed size arrary, just like c array, whose size is fixed during compiling and is efficient at random access
//
// = The reason why they are called sequence container is that all of them support traversing
//
// And here's the usage cheat sheet
// Trade-offs    /      usage notes
// std::vector	        Fast access but mostly inefficient insertions/deletions
// std::array	        Fast access but fixed number of elements
// std::list            Efficient insertion/deletion in the middle of the sequence
// std::forward_list	Efficient insertion/deletion in the middle of the sequence
// std::deque	        Efficient insertion/deletion at the beginning and at the end of the sequence

void printVec(const vector<string> &v);

// = Key takeaway from vector and deque is
// = deque is faster when most insertions and deletions take place at the beginning or at the end of the sequence but is slow for random accessing
// = so, just use devtor as default
void useVector();
void useDeque();
void useList();
void useForwardList();
void useArrary();

int main(int argc, char *argv[])
{
    // useVector();
    // useDeque();
    // useList();
    // useForwardList();
    useArrary();
    return 0;
}

void printVec(const vector<string> &v)
{
    cout << "{ ";
    for (auto i : v)
        cout << i << " ";
    cout << "}" << endl;
}

void useVector()
{
    vector<int> vec{1, 2, 3};
    for (auto i : vec)
        cout << i << " ";
    cout << endl;
    vec.pop_back();
    vec.push_back(5);
    for (auto i : vec)
        cout << i << " ";
    cout << endl;
}

void useDeque()
{
    deque<int> d{1, 2, 3, 4, 5};
    for (auto i : d)
        cout << i << " ";
    cout << endl;

    d.push_front(0);
    d.push_front(-1);
    for (auto i : d)
        cout << i << " ";
    cout << endl;
}

void useList()
{
    list<int> l{1, 2, 3};
    for (auto i : l)
        cout << i << " ";
    cout << endl;

    l.reverse();
    for (auto i : l)
        cout << i << " ";
    cout << endl;
}

void useForwardList()
{
    forward_list<int> fL{1, 2, 3};
    for (const auto l : fL)
        cout << l << " ";
    cout << endl;
}

void useArrary()
{
    array<int, 3> A{1, 2, 3};
    for (const auto a : A)
        cout << a << " ";
    cout << endl;
}