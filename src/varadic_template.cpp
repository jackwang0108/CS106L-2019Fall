#include <string>
#include <vector>
#include <stdarg.h>
#include <iostream>
#include <initializer_list>

using namespace std;

// C++ offered three methods to let a function receive
// arbitrary number of parameters:
// The first is traditional C method, use va_list, va_start and va_end
// The Second is traditional C++ method, initializer_list
// The Third way is C++ mordern way, introduced in C++11, Variadic Template

// * The first way isn't safe, what about code run failed before reaching va_end?
int sumValist(int count, ...)
{
    va_list ap;
    va_start(ap, count);
    int sum = 0;
    for (int i = 0; i < count; i++)
        sum += va_arg(ap, int);
    va_end(ap);
    return sum;
}

// * The second way is much easier to write, but still need to use uniform initialization
// * to create a initializer_list object to pass all parameters
int sumInitializerList(initializer_list<int> nums)
{
    int sum = 0;
    for (auto iter = nums.begin(); iter != nums.end(); iter++)
        sum += *iter;
    return sum;
}

// * The third way is a little bit complex, let us start from a simpler example before implementing sum

// First, let us achieve a recursive version of the function which accept a vector to find minimum value
template <typename T>
T my_min(vector<T> &nums)
{
    T elem = nums[0];
    if (nums.size() == 1)
        return elem;
    vector<T> subList(nums.begin() + 1, nums.end());
    auto min = my_min(subList);
    if (elem < min)
        min = elem;
    return min;
}

// my_min is runtime recursion, use varadic template, we can achieve compile time recursion
// ...Ts is called parameter pack, it means that type Ts is a template type parameter pack
// i.e., Ts is a package of series parameters (parameter pack)
// args... is pack expansion. and during compiling, it will expand to real paramters
// for example:
//      1. f(args...) expands to f(E1, E2, E3)
//      2. f(&args...) expands to f(&E1, &E2, &E3)
//      3. f(n, ++args...) expands to f(n, ++E1, ++E2, ++E3)
//      4. f(++args..., n) expands to f(++E1, ++E2, ++E3, n)
// So, if we call my_minVaradic int main like this:
//      auto min = my_minVaradic(3.2, -7.9, 8.223, 0.0);
//      T = int
//      Ts = int, int, int
//      num = 3.2
//      args... = -7.9, 8.223, 0.0
// * since we call my_minVaradic in my_minVaradic, the compiler does the recursion for us
// So, calling my_minVaradic in my_minVaradic, it will become:
//      T = int
//      Ts = int, int
//      num = -7.9
//      args... = 8.223, 0.0
// * similarly, calling my_minVaradic in the third time of recursion will become:
//      T = int
//      Ts = int
//      num = 8.223
//      args... = 0.0
// * if we have the forth recursion, calling my_minVaradic will become like:
//      T = int
//      Ts = NULL
//      num = 0.0
//      args = NULL
// so there will be only one parameter num, Ts and args are empty now
// * So, we have to write a base case for my_minVaradic to stop the recursion
template <typename T>
auto my_minVaradic(T num)
{
    return num;
}

template <typename T, typename... Ts>
auto my_minVaradic(T num, Ts... args)
{
    auto min = my_minVaradic(args...);
    if (num < min)
        min = num;
    return min;
}

void useMyMin()
{
    vector<int> nums{-1, 2, 3, -9, 10, 20};
    cout << "Minimum of numbers is: " << my_min<int>(nums) << endl;
    cout << "Minimum of numbers is " << my_minVaradic(-1, 2, 3, -9, 10, 20) << endl;
}

// * the best part of varadic template is that, the types do have to be homogenous
// a more realistic example is printf
// void printf(string format)
// {
//     cout << format;
// }
//
// template <typename T, typename... Ts>
// void printf(string format, T value, Ts... args)
// {
//     int pos = format.find('%');
//     if (pos == string::npos)
//         return;
//     cout << format.substr(0, pos) << value;
//     printf(format.substr(pos + 1), args...);
// }
//
// if we call like this:
//      printf(“Lecture %: % (Week %)”, 7, “Templates”s, 4);
//
// the compiler instantiates the templates as:
//      printf<int, string, int>
//      printf<string, int>
//      printf<int>
//      printf

// * now let us finish sum use varadic template
template <typename T>
T sumVaradicTempleate(T value)
{
    return value;
}

template <typename T, typename... Ts>
double sumVaradicTempleate(T value, Ts... values)
{
    return value + sumVaradicTempleate(values...);
}

void useSum()
{
    vector<int> nums{1, 2, 3, 4, 5};
    cout << "Sum of nums: " << sumValist(nums.size(), nums[0], nums[1], nums[2], nums[3], nums[4]) << endl;
    cout << "Sum of nums: " << sumInitializerList({1, 2, 3, 4, 5}) << endl;
    cout << "Sum of nums: " << sumVaradicTempleate((int)1, (float)2.0, (long)3, (double)4.2, 4, 5) << endl;
}

int main(int argc, char *argv[])
{
    // useMyMin();
    useSum();
    return 0;
}