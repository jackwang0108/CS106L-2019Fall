#include <set>
#include <map>
#include <deque>
#include <array>
#include <vector>
#include <string>
#include <iomanip>
#include <iterator>
#include <iostream>

using std::array;
using std::cout;
using std::endl;
using std::map;
using std::set;
using std::string;
using std::vector;

// * Agenda
//  1. Motiving Example
//  2. Computations on Types
//  3. Meta-functions and implementing identity
//  4. Template deduction and implementing is_same
//  5. Wrpping everything up with constexpr

// * Disclamier
// Will I ever write TMP code?
//      - Maybe. And definitely if you are implementing libraries
//      - But you will probably see them when debugging template error message

// Here's the motivating example, we want to write a function which returns the distance between two iterators
template <typename It>
size_t myDistance(It first, It last)
{
    // * Since deque::iterator is random access iterator
    // * we don't have to use ++, we can directly return last - first, thus the complexity is O(1)
    // * but for other iterator, we have to do this, thus the complxity is O(N)
    size_t result = 0;
    while (*first != *last)
    {
        first++, result++;
    }

    // * We'd like something, thus came to the problem:
    // =            running codes according to the type
    // = More generally, sometimes, we'd like calculate on types. That is exactlly what template meta programming does.
    // = Template Meta Programming wasn't invented by indention, but was discovered accidentally and found useful
    // if (It is random access iterator)
    //     return last - first;
    // else
    // {
    //     size_t result = 0;
    //     while (*first != *last)
    //     {
    //         first++, result++;
    //     }
    //     return result;
    // }

    return result;
}

void useMyDistance()
{
    vector<string> names{"Anna", "Ethan", "Nikhil", "Avery"};

    auto anna_iter = std::find(names.begin(), names.end(), "Anna");
    auto avery_iter = std::find(names.begin(), names.end(), "Avery");

    cout << "Distance between " << *anna_iter << " and " << *avery_iter << " is " << myDistance(anna_iter, avery_iter) << endl;
}

int foo(int i)
{
    return i;
}

// = Computation on Values v.s. Computation on Types
// declaring variables
int s = 3;
using S = int;

// calculating
int triple = s * 3;
using cl_ref = const S &;

// * What about functions?
// * We can pass values to meta functions, and get the return value
// * here the name of the meta function is remove_reference, and parameter are in <>, return values are in ::type
int value_result = foo(s);
using type_result = std::remove_reference<cl_ref>::type;

// * for Evaluating Expression
// * we use constexpr
bool value_equals = (value_result == 0);
constexpr bool type_equals = std::is_same<type_result, const int>::value;

// * So, we can do things like
// if (value_equals)
//     exit(1);

// if constexpr (type_equals)
//     exit(1);

// = New stuff for template meta programming
//      1. meta functions: std::is_same<type1, type2>::value
//      2. constexpr
//      3. static member values

// Now, let us finish a meta function

// = First, recap template types and values first.
// When we call:
// int main()
// {
//     vector<int> vec{1, 2, 3};
//     array<int, 3> arr{1, 2, 3};
// }
//
// In vector.h and array.h, the prototypes are
// template <typename T>
// class vector {
//      void push_back(const T& val);
// };
// template <typename T, size_t N>
// class array {
// };

// * and the compiler will generate the code for us like:
// class vector_int{
//     void push_back(const int& val);
// }
// class vector_double{
//     void push_back(const double& val);
// }
// * for values, like array<int, 3>, the size_t N will be replaced by 3

// = Abstractly, a meta-function is a "function" that operates on some types/values ("parameter"), and outputs some types/values ("return values")
// = Concretely, a meta-function is a struct that has public member types/fields which depends on what the template types/values are instantiated with

// * a simple example of meta-function which returns a type
template <typename T>
struct typeIdentity
{
    using type = T;
};
using K = typeIdentity<int>::type;

// * a simple example of meta-function which returns a value
template <int V>
struct valueIdentity
{
    static const int value = V;
};
int val = valueIdentity<3>::value;

// = so, meta-funcions are structs that treats its template types/values as the parameters and places the return values as public members
// = we never need to create an instance of the struct

// = Template deduction
// * we can have a generic template as well as specialized templates for particular types, this is called template specialization
// a famous example of template specialization is vector, since bool values only need a digit to store, so specialize bool vector
// can save the memory

// template <typename T>
// class vector
// {
//      ...
// };
//
// template <>
// class vector<bool> {
//      ...
// }

// = we can also partially specialize a template
// template <typename K, typename V>                // generic
// struct HashMap {};

// template <typename K, typename V>                // partially specialized
// struct HashMap<K*, V> {};                        // first type is a pointer

// template <typename V>                            // partially specialized
// struct HashMap<int, V> {};                       // first type is int

// template <>                                      // partially specialized
// struct HashMap<int, int> {};                     // both types are int

// = Give we have a lot of specialized templates, what the compiler will trying to do is to find and instantiate the best matched template

// = There are a bunch of template instantiate rules, summarized as:
// =        1. Compiler will rank all the templates, try each util it finds the one that works
// =            it will try the most specialized first, and to the generic last
// =        2. Error only if none work or if there is a tie

// So, we could do is_same
// * what we assume is that the compiler will match the second one first, and if fail, try the first one
template <typename T, typename U>
struct is_same
{
    static const bool value = false;
};

template <typename T>
struct is_same<T, T>
{
    static const bool value = true;
};

void useIsSame()
{
    cout << std::boolalpha << is_same<int, int>::value << endl;
    cout << std::boolalpha << is_same<int, double>::value << endl;
}

// = similarly, we can also do this
template <typename T>
struct is_pointer
{
    static const bool value = false;
};

template <typename T>
struct is_pointer<T *>
{
    static const bool value = true;
};

void useIsPointer()
{
    bool no = is_pointer<int>::value;
    bool yes = is_pointer<int *>::value;
    cout << std::boolalpha << no << endl;
    cout << std::boolalpha << yes << endl;
}

// = We can also achieve
template <typename T>
struct remove_const
{
    using type = T;
};

template <typename T>
struct remove_const<const T>
{
    using type = T;
};

void useRemoveConst()
{
    remove_const<int>::type a = 1;
    remove_const<const int>::type b = 2;
    b = a;
    cout << b << endl;
    cout << std::boolalpha << is_same<remove_const<int>::type, remove_const<const int>::type>::value << endl;
}

// = Template Meta Programming is a "hack"
// = we are exploiting the compiler's template matching rules to implement an if/else statement for types

// * So, back to the distance function, let us finish the distance function
template <typename It>
size_t myDistanceAdvanced(It first, It last)
{
    // determine the type of the iterator
    // typename here is just to inform the compiler that this is type
    // if we don't do that, the compiler may think this is static member
    using category = typename std::iterator_traits<It>::iterator_category;

    if (std::is_same<category, std::random_access_iterator_tag>::value)
    {
        return last - first;
    }
    else
    {
        size_t result = 0;
        while (*first != *last)
            result++, first++;
        return result;
    }

    // * when compile, the code above will become
    // if (false)
    // {
    //     return last - first;
    // }
    // else
    // {
    //     size_t result = 0;
    //     while (*first != *last)
    //         result++, first++;
    //     return result;
    // }
    // * but return last - first still exists in the program, which will waster the memory.
    // * we don't even want extra codes in compile
}

// = to remove the extra code, in Pre-C++17, there is a meta-function called std::enable_if, but it is a little bit complicated
// = so, in C++17, constexpr is boosted
// = in C++11, constexpr is used to calculate the expressiono at compile time, just a stronger form of const
// = but in C++ 17, constexpr can be used to calculate the expression at compile time and replace the entire if/else with the code that will actually run

template <typename It>
size_t myDistanceConstexpr(It first, It last)
{
    using category = typename std::iterator_traits<It>::iterator_category;

    if constexpr (std::is_same<category, std::random_access_iterator_tag>::value)
    {
        return last - first;
    }
    else
    {
        size_t result = 0;
        while (*first != *last)
            result++, first++;
        return result;
    }
}

void summary()
{
    cout << "Summary" << endl;
    cout << "Use template techniques to modify the actual source code of the program" << endl;
    cout << "That's the reason why they are called meta-programming, we are programing on the code itself" << endl;
    cout << "constexpr if can be used to turn of pieces of the code which wouln't compile for certian types" << endl;
    cout << "Key takeaways" << endl;
    cout << "Template allow you to treat types as \"variables\"" << endl;
    cout << "Meta-functions lets you modify these types, or to query information about these template types." << endl;
    cout << "constexpre (if) gives you the flexibility to modify the source code based on the template type." << endl;
    cout << "This allows you to optimize code based on type!" << endl;
}

int main(int argc, char *argv[])
{
    // useMyDistance();
    // useIsSame();
    // useIsPointer();
    // useRemoveConst();
    summary();
    return 0;
}