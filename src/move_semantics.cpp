#include <vector>
#include <string>
#include <iostream>

#include "stringvector.h"

using namespace std;

StringVector readNames(size_t size)
{
    StringVector names(size, "Ito");
    return names;
}

// * The code below has severe efficiency problem.
void copyAlot()
{
    // in readNames, default constructor is called once
    // and when readName returns, copy constructor is called
    // and assign the return value of readNames to name1 called copy constrctors
    StringVector name1 = readNames(543);
    // for name2, default constructor is called
    StringVector name2;
    // similarly, in readNames, default constructor is called once
    // when readNames returns, copy constructor is called
    // and assign return value of readNames to name2 called copy assign operator
    name2 = readNames(543);
    // So, in total, 6 objects of StringVector is created in copyAlot function
}

// = but in fact, we just need name1 and name2, the rest of them are useless
// = to reduce the useless copy during returning an object from function,
// = the C++ compiler has made a improvement. This is called copy elision
// = and is has been ensured in C++17
// = so, by using -std=c++17, copy elision is on. To disable it, use
// = -fno-elide-constructors
// = the hint here is, copy elision can only improve the return value copy

// * today what we are focusing on is to steal the returned object from a function to assign it to the variable
// * this is called move semantic, like:
// *        StringVector name2;
// *        name2 = readNames(543);
// * directly move the returned object of readNames to name2, instead of calling copy assign for name2

// * But we cannot do move to code like this:
// *        StringVector name2;
// *        StringVector name3 = readNames(1);
// *        name2 = name3;
// * name2 cannot steal everything from name3. But name3 can steal everything from returned object of readNames

// * The key is we can only steal a temporary object created by the compiler, instead of stealing from a named local variable

void lvalueAndRvalue()
{
    // before move semantics, we need to know rvalue and lvalue
    // * Intuitive definition of lvalue vs. rvalue
    // * An l-value is an expression that has a name (identity)
    // *    we can find address using address-of operator (&var)
    // * An r-value is an expression that does not have a name (identity)
    // *    r-value are mostly temporary values, like result of an expression, return value of a function
    // *    we cannot find address using address-of operator (&var)

    // * and the technical definitions are
    // * An l-value is an expression that can appear either left or right of an assignment.
    // * An r-value is an expression that can appear only on the right of an assignmen

    // int val = 2;                  // lvalue val = rvalue 2
    // int *ptr = 0x02248837;        // lvalue ptr = rvalue 0x02248837
    // vector<int> v1{1, 2, 3};      // lvalue v1 = rvalue {1, 2, 3}
    // auto v4 = v1 + v2;            // lvalue v4 = rvalue v1 + v2 (v1 and v2 are lvalue, but the result of v1 + v2 is rvalue)
    // size_t size = v.size();       // lvalue size = rvalue v.size() (v is lvalue, but the result of v.size() is rvalue)
    // val = static_cast<int>(size); // lvalue val = rvalue (size is lvalue, but the result of static_cast is rvalue)
    // v1[1] = 4 * i;                // v1[1] calls v1.operator[](), a function, so the return value should be rvalue,
    //                                  but this function returns a reference, so v1[1] is lvalue
    //                                  so, lvalue = rvalue
    // ptr = &val;                   // lvalue = rvalue
    // v1[2] = *ptr;                 // lvalue = lvalue
}

void rvalueReference()
{
    // int val = 2;
    // int *ptr = (int *)0x02248837;
    // vector<int> v1{1, 2, 3};

    // * before, we use reference to make it points to a variable
    // * this is actally called lvalue reference, which means
    // * the reference is bind to a lvalue
    // auto &ptr2 = ptr;
    // * we can also create a rvalue reference, use &&
    // * this means the reference is bind to a rvalue
    // * what the rvalue reference does is it actually elongate the life of rvalue
    // * the temporary result of v1 + v2 is kept v.s. freed immediately
    // auto &&v4 = v1 + v2;
    // = This is error, cannot bind a lvalue reference to rvalue
    // auto &ptr3 = &val;
    // = This is also error, cannot bind a rvalue reference to lvalue
    // auto &&val2 = val;
    // = but this is ok, you can bind a const lvalue reference to a rvalue
    // const auto &ptr3 = ptr + 5;
}

// * the idea of lvalue and rvalue is that
// * rvalues are temporary values, and they will die very soon
// * so we can steal values from rvalues

void useMove()
{
    StringVector v1;
    v1.push_back("Iteo-En");

    StringVector v2((size_t)2, "Green");

    StringVector v3;
    v3 = (v1 + v2);

    for (auto i : v3)
        cout << i << endl;
}

// move semantic requires rvalue reference, but result some problem
// considering a class below
struct Student
{
    string id;
    string name;
};

class Axess
{
private:
    vector<Student> students;

public:
    Axess() {}
    Axess(Axess &&other) : students(other.students) {}
    Axess &operator=(Axess &&rhs)
    {
        // = the code here is problematic
        // = because rhs.students is vector
        // = although rhs is a rvalur, but rhs.student is still lvalue
        // = so this still makes a copy
        // students = rhs.students;

        // to solve this problem, we need to change rhs.student
        // to a rvalue.
        // How to achieve that?
        // C++ provide us a function which unconditional cast anything to a r-value.
        // so, we can use to change the destination instead this->student of copying rhs.students to this->students
        students = std::move(rhs.students);
        return *this;
    }
};

// use move semantics, we can use create a perfect generic swap function
template <typename T>
void swap(T a, T b)
{
    T temp = std::move(a);
    a = std::move(b);
    b = temp;
}

void useSwap()
{
    vector<int> a{1, 2, 3};
    vector<int> b{-1, -2, -3};
    swap(a, b);
    for (auto i : a)
        cout << i << " ";
    cout << endl;

    for (auto i : b)
        cout << i << " ";
    cout << endl;
}

int main(int argc, char *argv[])
{
    // useMove();
    useSwap();
    return 0;
}