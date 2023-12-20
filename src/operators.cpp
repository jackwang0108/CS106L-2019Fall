#include <vector>
#include <string>
#include <iostream>

#include "stringvector.h"

using namespace std;

void useOperator()
{
    StringVector v;
    v.push_back("Hello");
    v.push_back("World");

    for (auto i : v)
        cout << i << endl;

    // STL is not a part of the C++ itself, they are external libraries
    // So they are not builtin the C++
    // So, when we call cout << v[0]. How does the compiler know what to do with v[0]?
    // More specific, v[0] is a string, how does compiler know "oh, I need to print the string to cout".
    // While codes like: 1<<2 means shift 1 left by two digits to it turn to 0b100, 4
    // = i.e. how does C++ know hot to apply operators to user-defined classes?

    // * This is bucause C++ is trying to call these functions
    // cout.operator<<(v.operator[](0)).operator<<(endl);
    // v.operator[](1).operator+=("!");
    // * We usually write the short-hand code, and during compiling time, the compiler is calling these function

    // There is actually another form of these ones
    // operator<<(cout, v.operator[](0));
    // operator+=(operator[](v, 1), "!");

    // Indeed, the people who worte the STL also wrote tese functions
    // ostream &operator<<(ostream &s, const string &val)
    // {
    //     ...
    // }
    // must be member, technically it’s prob a template
    // string &vector<string>::operator[](size_t index) const {
    //     ...
    // }
    // string & operator+=(string &lhs, const string &rhs)
    // {
    //     ...
    // }
}

void useOperatorOverload()
{
    StringVector v1;
    v1.push_back("Hello");
    v1.push_back("World");

    // We are going to do
    // v1 += “World”; // we’re adding an element
    // vector<string> v2{“Hi”, “Ito”, “En”, “Green”, “Tea”};
    // v2 += v1; // we’re adding a vector

    // The function signature look like
    // append one element
    // [some return value] vector<string>::operator+=([some type] element) {
    //     push_back(element);
    //     return [something?];
    // }
    // append another vector
    // [some return value] vector<string>::operator+=([some type] other) {
    //     for (string val : other) push_back(val);
    //     return [something?];
    // }

    v1 += "Ito-En";
    // * this is equal to
    v1.operator+=("Green Tea");

    StringVector v2;
    v2.push_back("");

    for (const string &s : v1)
    {
        cout << s << endl;
    }
}

// * The rule for operator overloading is that
// *        1. Some operator must be implemented as member function
// *            e.g., [], (), ->, =
// *        2. Some must be implemented as non-member function
// *            e.g. <<
// *        3. For unary operator, implement as member function
// *            e.g. ++, --
// *        4. If the binary operator treats both operands equally (e.g. both unchanged)
// *           implement them as non-member (maybe friend is need to access private data),
// *            e.g. +, <
// *        5. If binary operator not treat both operands equally (change lhs)
// *           implement as member function (allow easy access to lhs private members)
// *            e.g. +=, -=

// * Plus, there is a design philosophy, POLA: Principle of Least Astionishment
// *    - If a neceesary feature has a high astonishment factor,
// *    - you need to redesign the feature

// * So, under POLA, here is some recommendations for designing the rule:
// *        1. Design operators primarily to mimic conventional usage.
// *        2. Use non-member functions for symmetric operators.
// *            e.g, if `a + 1` and `1 + a` have same result,
// *                implement is as non-memnber function, or `1 + a` will fail.
// *        3. Always provide all out of a set of related operators.
// *            e.g. if you are going to provide operator==, you should also provide !=, <=, >=, <, >,

// * For class methods, there is const version and non-const version
// * For example,
// *        int Fractional::operator[];
// *        const int Fractional::operator[] const;
// * The difference is
// *    Fractional v1;
// *    const Fractional v2;
// * v2 can only cal const member-function
void constMember()
{
    vector<string> v1{"Green", "Black", "Oo-long"};
    const vector<string> v2{"16.9", "fluid", "ouncese"};

    // This is ok
    v1[1] = "boba";
    // = but this doesn't
    // = this is because the vector has both const and non-const version of operator[]
    // int a = v2[1];
    // v2[1] = "solid";
}

// In C++, there is two types of copy operator (=)
// * First is copy construction, Second is Copy assignment
// * First:     string v = string("hello");
// * Second:
// *            string v1 = string("Hello");
// *            string v2 = string("World");
// *            v1 = v2
// * First is used when creating a new object
// * Second is used when the object already exists,
// * we just wipe out the object and putting new things into it

// For example
//      1. vec0 calls copy constructor
//      2. vec1 calls default constructor
//      3. vec2 calls regular constructor
//      3. vec3 calls regular constructor
//      4. vec4 is a function, not a vector (Yeah, wired)
//      5. vec5 calls copy construcor
//      6. vec6 calls default constructor
//      7. vec7 calls copy constructor
//      8. vec8 calls copy constructor
//      9. vec8 = vec2 calls assign operator
//      10. return vec8 calls copy constructor
// The difference of copy constructor and assign operator is
// whether it creates a new object
// vector<int> function(vector<int> vec0) {
//   vector<int> vec1;
//   vector<int> vec2(3);
//   vector<int> vec3{3};
//   vector<int> vec4();
//   vector<int> vec5(vec2);
//   vector<int> vec6{};
//   vector<int> vec7{vec3 + vec4};
//   vector<int> vec8 = vec4;
//   vec8 = vec2;
//   return vec8;
// }

int main(int argc, char *argv[])
{
    // useOperator();
    useOperatorOverload();

    return 0;
}