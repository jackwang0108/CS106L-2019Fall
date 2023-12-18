#include <map>
#include <set>
#include <list>
#include <ctime>
#include <vector>
#include <string>
#include <cstdlib>
#include <iterator>
#include <iostream>
#include <algorithm>

using namespace std;

// * iterator allow iteration over ANY container, whether it is ordered or not
// * for example, we have a set `std::set<int> mySet`
// * inside mySet, it is non-linear, but using the iterator, it will let us view mySet as if it was linear
//
// * How is iterator possible to achieve that? We don't care (The use binary search tree)
// * We just use them, iterator hides all handy works and show a unified interface to us

// * To create a iterator, we can just use `mySet.begin()`, which returns a iterator
// * But what is the type of the iterator? It is actually type iterator `std::set<int>::iterator`
// * Note that the type of the iterator depends on the the of the container, like int set has int iterator type
// * So, to declare an iterator would like this: `set<int>::iterator begin = mySet.begin()`

// * To use the iterator, we can dereference the iterator like *begin, it will return the value of the iterator
// * And we can also use ++/-- to move the iterator to the next element in the container
// * When the iterator points to the end, return: `if (begin == mySet.end()) return`

// * Summary of Iterator
// *    1. Create an iterator
// *    2. Dereference iterator to read value currently the iterator points to
// *    3. Advance the iterator
// *    4. Compare against another iterator (especially .end() iterator)

// * Why is iterator powerful? Or, why would we use iterator?
// * This is because the iterator gives a way to write generic functions
int numOccurences(vector<int> &cont, int elemToCount)
{
    int counter = 0;
    for (vector<int>::iterator iter = cont.begin(); iter != cont.end(); iter++)
        if (*iter == elemToCount)
            counter++;
    return counter;
}
// * What if we just want to change to another data structure like std::list?
// * Yeah, just change the type without change the logic of the code
int numOccurences(list<int> &cont, int elemToCount)
{
    int counter = 0;
    for (list<int>::iterator iter = cont.begin(); iter != cont.end(); iter++)
        if (*iter == elemToCount)
            counter++;
    return counter;
}
// * Later, we may use template to replace specific types, so with the help of iterator
// * We could write a generic code with fits all container to count the ocurrence of an element
template <typename Container, typename T>
int numOccurences(Container &cont, T elemToCount)
{
    int counter = 0;
    for (auto iter = cont.begin(); iter != cont.end(); iter++)
        if (*iter == elemToCount)
            counter++;
    return counter;
}
// * This function fits all types of container and type of element

int getRandomNumber();
void basicUsage();
// * For map iterators, the iterator will points to pair
void mapIterator();
void classCode();
void useErease();
void ereaseAll();

int main(int argc, char *argv[])
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // basicUsage();
    // mapIterator();
    // classCode();
    // useErease();
    ereaseAll();
    return 0;
}

int getRandomNumber()
{
    return std::rand();
}

void basicUsage()
{
    set<int> mySet;
    int i;
    cout << "genrate random number: ";
    while (i++ < 10)
    {
        int r = getRandomNumber();
        cout << r << " ";
        mySet.insert(r);
    }
    cout << endl;

    set<int>::iterator iter = mySet.begin();
    while (iter != mySet.end())
    {
        cout << *iter << " ";
        iter++;
    }
    cout << endl;

    for (set<int>::iterator iter = mySet.begin(); iter != mySet.end(); iter++)
        cout << *iter << " ";
    cout << endl;
}

void mapIterator()
{
    map<string, int> m;
    m.insert({"Jack", 2});
    m.insert({"Wang", 1});

    map<string, int>::iterator iter = m.begin();
    while (iter != m.end())
    {
        cout << (*iter).first << ": " << (*iter).second << endl;
        iter++;
    }
}

void removeFirstA(vector<string> &vec)
{
    for (auto iter = vec.begin(); iter != vec.end(); ++iter)
    {
        if (!(*iter).empty() && (*iter)[0] == 'A')
        {
            vec.erase(iter);
            return;
        }
    }
}

void useErease()
{
    vector<string> vec{"Apple", "Banana", "Cash", "Dragon"};
    removeFirstA(vec);
    for (auto i : vec)
        cout << i << endl;
}

// * Note, if use removeFirstA to remove all A by delete return
// * is actually problematic.
// * because the iterator knows how to get from one element to the next through the entire range
// * When an element is erased, the container may reorganize the layout of the elements
// * But The iterator still thinks it should follow previous arrows to find the next element.
// * So after erase, some iterators will be invalid.
// * Not all iterator will be invaild, for example, std::array::iterator
// * will not be invaild because the elements are in a piece of memory
// * That's why std::list and std::array are stable in cppreference

// = the good news is erase will returns a new valid iterator
// = so we can use that for the next iteration to remove all A
void removeAllA(vector<string> &vec)
{
    for (auto iter = vec.begin(); iter != vec.end();)
    {
        if (!(*iter).empty() && (*iter)[0] == 'A')
        {
            vec.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

// = Summary of Iterator Invalidation
// = Some operations on some containers invalidate iterators. Read the documentation!
// = These operations usually will return a valid iterate that you should use instead.
// * Different container has different invalidate rules:
// *        1. iterators to erase point is always invalidated
// *        2. vactor: all iterators after erasure point is invalidated due to all element after erasure point shifting ahead
// *        3. deque: all iterators ivalidated unless the erasure point is front of the deck
// *        4. list/set/map: all other iterators are still validated
// * Plus: Always read the documentations

void ereaseAll()
{
    vector<string> vec{"Apple", "Banana", "Appalachian", "Cash", "Abandon", "Dragon"};
    removeAllA(vec);
    for (auto i : vec)
        cout << i << endl;
}

void printVec(const vector<int> &vec)
{
    cout << "{ ";
    for (auto i : vec)
        cout << i << " ";
    cout << " }" << endl;
}

void classCode()
{
    vector<int> vec{3, 1, 4, 1, 5, 9, 2, 6};
    printVec(vec);
    std::sort(vec.begin(), vec.begin() + 4);
    printVec(vec);

    set<int> elems{3, 1, 4, 1, 5, 9, 2, 6};
    cout << elems.size() << endl;

    auto testit = std::find(elems.begin(), elems.end(), 5);
    if (testit == elems.end())
        cout << "Not found!" << endl;
    else
        cout << "Found: " << *testit << endl;

    // lower_bound find smallest element >= key
    // upper_bound find smallest element > key
    set<int>::iterator l_bound = elems.lower_bound(4);
    set<int>::iterator u_bound = elems.upper_bound(6);
    cout << "lower bound: " << *l_bound << endl;
    cout << "upper bound: " << *u_bound << endl;
}

// * Iterator actually has types, there are five types of iterator:
// *    1. input
// *    2. output
// *    3. forward
// *    4. bidirectional
// *    5. random access

// * All iteratos sharea few coment traits:
// *    1. Can be created from existing iterator
// *    2. Can be advanced using ++
// *    3. Can be compared with == and !=
void iteratorTypes()
{
    ostream_iterator<int> o_iter(cout);
    istream_iterator<int> i_iterator(cin);
    // forward_iterator
    // bidirectional_iterator
    // random_access_iterator
}