#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <concepts>
#include <iterator>
#include <typeinfo>
#include <iostream>

using namespace std;

pair<int, int> myMinMax(const int a, const int b)
{
    if (a < b)
        return {a, b};
    return {b, a};
}

pair<string, string> myMinMax(const string &a, const string &b)
{
    if (a < b)
        return {a, b};
    return {b, a};
}

pair<double, double> myMinMax(const double a, const double &b)
{
    if (a < b)
        return {a, b};
    return {b, a};
}

template <typename T>
pair<T, T> myMinMax(const T a, const T b)
{
    if (a < b)
        return {a, b};
    return {b, a};
}

void printMinAndMax(int min, int max)
{
    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;
    cout << endl;
}

template <typename T>
void printMinAndMax(T min, T max)
{
    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;
    cout << endl;
}

void minMaxTestBasic()
{
    // This is good
    auto [min1, max1] = myMinMax(3, -2);
    printMinAndMax(min1, max1);

    // This is also good
    auto [min2, max2] = myMinMax(6, 6);
    printMinAndMax(min2, max2);

    // * This will cause the compiler to complain
    // * it may complie and run, but the values are changed
    auto [min3, max3] = myMinMax(8.3, 7.4);
    printMinAndMax(min3, max3);

    // * This may also compile and run, but the print isn'r as we desired
    auto [min4, max4] = myMinMax('l', 'b');
    printMinAndMax(min4, max4);

    // * But this won't compile at all
    // auto [min5, max5] = myMinMax("Jack", "Wang");
    // to solve this problem, we may want to write a function for string
    auto [min5, max5] = myMinMax("Jack", "Wang");
    // printMinAndMax(min5, max5);
    min5 = max5;

    // * We may also write a function for double
    auto [min6, max6] = myMinMax(8.3, 7.4);
    min6 = max6;
    // printMinAndMax(min3, max3);

    // = But, all three functions for int, double and string are the same
    // = The only difference is the types
    // = What if we change the type to T?
    // = Then we have a generic function
    // pair<T, T> myMinMax(T a, T b)
    // {
    //     if (a < b)
    //         return {a, b};
    //     return {b, a};
    // }
    // = And we have to inform the C++ compiler that T is a typename
    // = so we got template
    // template <typename T>
    // pair<T, T> myMinMax(T a, T b)
    // {
    //     if (a < b)
    //         return {a, b};
    //     return {b, a};
    // }
    // = so, we got the final function now. And we also rewrite the printMinAndMax
    // = finally, we got
    auto [min1_T, max1_T] = myMinMax(3, -2);
    printMinAndMax(min1_T, max1_T);
    auto [min2_T, max2_T] = myMinMax(6, 6);
    printMinAndMax(min2_T, max2_T);
    auto [min3_T, max3_T] = myMinMax(8.3, 7.4);
    printMinAndMax(min3_T, max3_T);
    auto [min4_T, max4_T] = myMinMax('l', 'b');
    printMinAndMax(min4_T, max4_T);
    auto [min5_T, max5_T] = myMinMax("Jack", "Wang");
    printMinAndMax(min5_T, max5_T);
    auto [min6_T, max6_T] = myMinMax(8.3, 7.4);
    printMinAndMax(min6_T, max6_T);

    // * The declaration `template` actually inform the compiler
    // * That the following function follows the template here
    // * so we can also use template as an alias of other type
    // * for example, template<size_t T>, the in the function, T is the alias for size_t

    // * When compiling, the compiler may deduce the type T for us
    // * But we can also use explicit initialization for the type T.
    // * Which means, set the type T to a specified type
    auto [minExplicit, maxExplicit] = myMinMax<double>(7.8, 9.2);
    minExplicit = maxExplicit;
    // * this also works for vectors
    auto [min, maxVecEx] = myMinMax({1, 2}, {2, 3});
    auto [minVec, maxVec] = myMinMax<vector<int>>({1, 2}, {2, 3});
    // printMinAndMax(minVec, maxVec);

    // * Some times, we have to use explicit initialization
    // * for example, passing mixed type. Without explicit initialization, this may cause a compile error
    // auto [minWrong, maxWrong] = myMinMax(2, 2.3);
    // * Since there is two types of arguments, so the compiler is confused.
    // * we have to use explicit initialization
    auto [minWrong, maxWrong] = myMinMax<double>(2, 2.3);
    minWrong = maxWrong;
}

template <typename T>
T getTypeValue()
{
    while (true)
    {
        cout << "Enter a " << typeid(T).name() << ": ";
        string line;
        T result;
        char extra;
        if (!getline(cin, line))
            throw domain_error("Unable to get line from cin.");
        istringstream iss(line);
        if (iss >> result && !(iss >> extra))
            return result;
        cout << "Invalid format." << endl;
    }
}

void getTypeValueTest()
{
    int val0 = getTypeValue<int>();
    int val1 = getTypeValue<int>();
    double val2 = getTypeValue<double>();
    cout << "int is: " << val0 << endl;
    cout << "int is: " << val1 << endl;
    cout << "double is: " << val2 << endl;
}

// * Last time, we talked about iterator, and here we will explain why they are helpful for generic programing
// The following code is actually problematic.
// = becuase not all containers can be random accessed
// = for example, map and set
// template <typename Collections, typename DataType>
// int countOccurence(const Collections<DataType> &list, DataType val)
// {
//     int count = 0;
//     for (size_t i = 0; i < list.size(); i++)
//         if (list[i] == val)
//             count++;
//     return count;
// }

// * But with the help of iterator, the problem is solved
// = however, the code still has some problems, where we actually have some assumption for the function
// = the assumption is, the function by defualt loops over the whole container
// = but to write a generic function, we need to give all control for the programmer
// template <typename Collection, typename DataType>
// int countOccurence(const Collection<DataType> &list, DataType val)
// {
//     int count = 0;
//     for (auto iter = list.begin(); iter != list.end(); iter++)
//     {
//         if (*iter == val)
//             count++;
//     }
//     return count;
// }

// * So we should write a code like
// = Although we didn't make any assumptions before writing the code
// = But the code still has some assumptions to work correctly
// =    1. begin need to be copyable, i.e. InputIterator should be copyable
// =    2. iter should be comparable, i.e. InputIterator should be comparable
// =    3. iter should be incrementable, i.e. InputIterator should be incrementable
// =    4. iter should be dereferencable, i.e. InputIterator should be dereferencable
// =    5. iter and val shoule be comparable
// So, to make the function runs correctly, we have to make sure the template parameters have the operations the function needs
// i.e.:
// For InputIterator, it should support:
//      1. copy assign (iter = begin)
//      2. prefix/postfix operator (++iter/iter++)
//      3. comparable to end (begin != end)
//      4. dereference operator (*iter)
// For DataType, it should support:
//      1. comparable to *iter
template <typename InputIterator, typename DataType>
int countOccurence(InputIterator begin, InputIterator end, DataType val)
{
    int count = 0;
    for (auto iter = begin; iter != end; iter++)
    {
        if (*iter == val)
            count++;
    }
    return count;
}

// * In C++20, concept is introduced to explicitely name the requirement on template argument
// In detail, std::iterator_traits is a class in C++ standard library, which provides information about iterator
// First, we need to include <iterator>, and std::iterator_traits provide us with the following member which details information about iterator:
//      1. iterator_traits::iterator_category：the type of iterator, includes:
//             A. std::input_iterator_tag
//             B. std::output_iterator_tag
//             C. std::forward_iterator_tag
//             D. std::bidirectional_iterator_tag
//             E. std::random_access_iterator_tag
//      2. iterator_traits::value_type：the type of the value that the iterator points to
//      3. iterator_traits::difference_type：the type of different between two iterators
//      4. iterator_traits::pointer：the type of point pointing to the value
//      5. iterator_traits::reference：the type of iterator after dereferencing
template <typename It, typename Type>
    requires std::input_iterator<It> &&
             std::equality_comparable_with<typename std::iterator_traits<It>::value_type, Type>
int countOccurrence(It begin, It end, Type val)
{
    int count = 0;
    for (auto iter = begin; iter != end; iter++)
        if (*iter == val)
            ++count;
    return count;
}

// * To make the function more generic, we use function for the if condition
// * a predicate is a function that takes a few argument, and return boolean
// * here is two examples of predicate
// Unary Predicate (take one argument)
bool isEqualTo3(int val)
{
    return val == 3;
}

// Binary Predicate (take two argument)
bool isDivisableBy(int divided, int divisor)
{
    return divided % divisor == 0;
}

// * Use predicate, we can make a function more generic
template <typename It, typename UniaryPredicate>
    requires std::input_iterator<It>
int countOccurenceMoreGeneric(It begin, It end, UniaryPredicate predicate)
{
    int count = 0;
    for (auto iter = begin; iter != end; iter++)
        if (predicate(*iter))
            count++;
    return count;
}

// = However, using functions as predicate do has severe problems.
// = One is, what if the function need more information, like the limit here.
// template <typename DataType>
// bool greaterThan(DataType val)
// {
//     return val >= limit;
// }
// = We may write a funtion like this
// = But this actually doesn't work. Since in the caller funtion of predicate, them have do this:
// predicate(*iter, limit);
// = So the limit still has to become the parameter of the generic funtion, which isn't elegant enough.
template <typename DataType>
bool greaterThan(DataType val, DataType limit)
{
    return val >= limit;
}

// The key problem here is that, we need to add extra information for the predicate.
// And what's more important is providing extra information and calling predicate is two different phase.
// So, in pre-C++11, the solution is using class (function objects), that is, the extra information is offer when initiating.
// and the, call the overload method for operator().
// * These classes are called functor
class GreaterThan
{
public:
    GreaterThan(int limit) : limit(limit){};
    bool operator()(int val) { return val >= limit; }

private:
    int limit;
};

// * When using, we can write codes like
// int main()
// {
//     int limit = getInteger("Minimum of A?");
//     vector<int> grades = readStudentGrades();
//     GreaterThan func(limit);
//     countOccurence(grades.begin(), grades.end(), func);
// }

// * C++11 offer us a lighter way to do this, that is lambda function
// * using lambda, we may write a code like this
// int main()
// {
//     int limit = getInteger("Minimum of A?");
//     vector<int> grades = readStudentGrades();
//     auto func = [limit](auto val){return val >= limit;};
//     countOccurence(grades.begin(), grades.end(), func);
// }

void useLambda()
{
    // * the syntax for lambda function is like
    // [capture](parameters) -> return_type {
    //      function body
    // }
    // * capture is used to pass variables in to the lambda function
    // * and return_type can be ommited since C++ type deduction does it really good.
    // * so a lambda function will be:
    // [capture](parameters) {
    //      function body
    // }
    // * and under the hood, during compilation, the C++ compiler will autmatically
    // * transfer the lambda function to a class (functor) to us.
    // * so, the type of greaterThan5 is actually a class.
    // * But we still cannot know the type of the class, cause the compiler does the transformation for us
    // * and the name of the class is random generated, and to be frank, we don't really need the name of the class
    // * That's the reason why we use an auto for greaterThan5
    int limit = 5;
    auto greaterThan5 = [limit](int val) -> bool
    { return val >= limit; };

    // * For the lambda function, when capturing variables, it actually makes a copy
    // * But we can still pass by reference
    set<string> teas{"black", "green", "oolong"};
    string banned = "boba";
    auto likedByAvery = [&teas, &banned](auto teaType)
    {
        return teas.count(teaType) && teaType != banned;
    };
    likedByAvery("black");

    // * and these are lazy ways to capture variables
    // = capture all by value, except teas is by reference
    auto func1 = [=, &teas](auto teaTypes)
    {
        return teas.count(teaTypes) && teaTypes != banned;
    };
    // = similary, capture all by reference, except banned
    auto func2 = [&, banned](auto teaTypes)
    {
        return teas.count(teaTypes) && teaTypes != banned;
    };

    int num = 10;
    cout << "greater than 5? " << std::boolalpha << greaterThan5(num) << endl;
}

// = Using template may be scary, because template is unconstriained
// = A template is unconstrained: the compiler will let you
// = instantiate the types with whatever you ask it to.
// = The actual error comes from the exact line there is a type error.
// = This is why template errors are extra scary.

// overload and template resolution
// C++ allow us to have functions in same name but different parameter
// When compiling, the compiler will find the best function for our call
// For example, considering functions below:
void func(int) {}    // 1
void func(double) {} // 2
void func(long) {}   // 3
// int useFunc() {
//     func(42);
// }

// During compilation, the compiler will follow rules to resolve these overload funtions
// and determine the best function to use, this is called overload resolution
// Here are the steps of overload resolution
//      1. Name Lookup, the compiler finds same name function in
//         current scope (e.g. class scope, global scope)
//      2. Generate Candidate Function Set. According to the number of the
//         parameters we passed in, the compiler finds the function which accepts
//         same number of paramters, called candidate function
//      3. Generate Viable Function Set. And then the compiler will check
//         if the type of paramters of candidate function matches arguments we passed in
//         Those functions who matches both paramter number and parameter types
//         are called viable function.
// =       This step also checks implicit interface of the parameter.
// =       i.e. the requirement of the paramter
//      4. Choose the Best Match. The compiler will finds the closest function
//         to our calls from viable function set. By closest, it means
//         the compiler will do the least type convertions.
//
// And example of overload resolution is:
void process(int) {}            // 1
void process(double) {}         // 2
void process(int, int) {}       // 3
void process(int, double) {}    // 4
void process(double, double) {} // 5
void notProcess(int, double) {} // 6

// When calling `process(42, 3.14)` in `useProcess`, during compilation, the compiler does:
//      1. Finds all same name function. Hereby it's five
//              A. process(int)
//              B. process(double)
//              C. process(int, int)
//              D. process(int, double)
//              E. process(double, double)
//      2. check number of parameters. So three functions are left as candidate functions:
//              A. process(int, int)
//              B. process(int, double)
//              C. process(double, double)
//      3. check the type of paramters. Since int can be counverted to double versus not.
//         We got two left here
//              A. process(int, double)
//              B. process(double, double)
//      4. find the least convertion funcion. So we got `process(int, double)`
// The whole process is finished during compilation, so there won't be any extra overheads.
// * For step 1/23, the overload resolution may failed, but once it enters step 4, it will never fail.
// * If any convertion is do needed, the compiler will throw an warning.
void useProcess()
{
    process(42, 3.14);
}

//  Things are a little bit complex when functions having template.
//  Since the compiler has to deduce the type of template. For example:
void process1(int) { std::cout << "process(int)\n"; }       // 1
void process1(double) { std::cout << "process(double)\n"; } // 2
template <typename T>
void process1(T) { std::cout << "process(T)\n"; } // 3

// For step 1, finding the same name function, and step 2, check parameter numbers
// are same. The only difference is step 3.
// The compiler will deduce the template type first and the find viable functions
// by deducing, it simply means subsitution the template name to the type when we do explicit initiation
// An detailed overload resolution of the above example will be
//      1. Name Lookup. Finds all funtion with name of process，hereby three
//              A. process1(int)
//              B. process1(double)
//              C. process1(T)
//      2. Generate Candidate Function Set. Find the function matches parameters number.
//         Hereby all of them
//              A. process1(int)
//              B. process1(double)
//              C. process1(T)
//      3. Generate Viable Function Set. The compiler first do template substitution
//         So we got
//              A. process1(int)
//              B. process1(double)
// =       Then find the function satifying all implicit interface.
//      4. Choose the Best Match. We got A, B, A respectively
void useProcess1()
{
    process1(42);     // A
    process1(3.14);   // B
    process1<int>(3); // A
}

// = The key takeaway here is during template deduction (substitution)
// = if the substitution fails, i.e., not satifying all the type and implicit interfaces
// = this wouldn't be treated as an error, this is called:
// * ==> Substitution Failure Is Not An Error (SFINAE)
// = that is When substituting the deduced types fails (in the immediate
// = context) because the type doesn’t satisfy implicit interfaces, this
// = does not result in a compile error.
// = Instead, this candidate function is not part of the viable set.
// = The other candidates will still be processed.

// So, here is a problem which examplify the power of SFINAE.
// This function by default require the template has .size() method
template <typename T>
size_t printSize(const T &a)
{
    cout << "Printing with size member function: " << a.size() << endl;
    return a.size();
}
// But if we call like this, it will cause an error for int has no .size method
// printSize<int>(1);

// * We can use decltype to achieve that.
// * decltype is the abbv. of declare type, the syntax is
// *            decltype(expression, type())
// * decltype will first try to compile the expression,
// * if the compile passed, then return the type
// * In detail, `expression, type` is a comma expression, which is treated as a whole expression
// * for comma expression, it returns right-most part, that is type()
// * but the whole comma expression will be compile.
template <typename T>
auto printSizeDecltype(const T &a) -> decltype((void)a.size(), size_t())
{
    cout << "Printing with size member function: " << a.size() << endl;
    return a.size();
}

void useDecltype()
{
    printSizeDecltype(vector<int>(10, {}));
}

// The other usage of decltype is as follow.
// Which declare b is the same type as a.
// But this kind of usage for decltype is tooo low
int a = 0;
decltype(a) b = 1;

// Now we can go on the power of snifae.
// we have three overload template function

// overloads works for container
template <typename T>
auto printSizeSfniae(const T &a) -> decltype((void)a.size(), size_t())
{
    cout << "printing with size member function: " << a.size() << endl;
    return a.size();
}

// overloads works for int/double
template <typename T>
auto printSizeSfniae(const T &a) -> decltype((void)-a, size_t())
{
    cout << "printing -a: " << -a << endl;
    return -a;
}

// overloads works for pointer
template <typename T>
auto printSizeSfniae(const T &a) -> decltype((void)a->size(), size_t())
{
    cout << "printing with size member function: " << a->size() << endl;
    return a->size();
}

// Alougth the three functions are the same, but during compilation
// due to SFINAE, the failed functions will be removed.
// So only one is left

void useSfinae()
{
    vector<int> vec{1, 2, 3};
    printSizeSfniae(vec);    // calls first overload
    printSizeSfniae(vec[1]); // calls second overload
    printSizeSfniae(&vec);   // calls third overload
    // printSizeSfniae(nullptr); // compiler error
}

// * Except functor and lambda function, std::bind provide another
// * solution to functions which need extra information
bool isLessThanLimit(int val, int limit)
{
    return val < limit;
}

#include <functional>
void useBind()
{
    vector<int> vec{1, 3, 5, 7, 9};
    int limit = 8;
    auto isLessThan = std::bind(isLessThanLimit, std::placeholders::_1, limit);
    cout << countOccurenceMoreGeneric(vec.begin(), vec.end(), isLessThan) << endl;
}

// * Summary
// decltype can be used to ensure the implicit interface

int main(int argc, char *agrv[])
{
    // minMaxTestBasic();
    // getTypeValueTest();
    // vector<int> vec{1, 2, 3, 4, 4, 3, 2, 1, 5};
    // cout << countOccurence(vec.begin(), vec.end(), 3) << endl;
    // useLambda();
    // useDecltype();
    useBind();
    return 0;
}