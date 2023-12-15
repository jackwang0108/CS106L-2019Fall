#include <cmath>
#include <tuple>
#include <array>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Report
{
    string date;
    size_t cases;
    size_t deaths;
};

void printReport(const Report &r);
void useStruct();
void usePair();
void useTuple();
void useArray();
void useVector();
void useAuto();
void useUnpack();

struct Solution
{
    double root1;
    double root2;
    bool has_solution;
};

int read_int(const std::string prompt);
std::pair<std::pair<double, double>, bool> quadratic(int a, int b, int c);
void solveQuadratic();

int main()
{
    // useStruct();
    // usePair();
    // useTuple();
    // useArray();
    // useVector();
    // useAuto();
    // useUnpack();
    solveQuadratic();
    return 0;
}

void printReport(const Report &r)
{
    cout << r.date << endl;
    cout << r.cases << endl;
    cout << r.deaths << endl;
}

void useStruct()
{
    Report current;
    current.date = "2023-12-15";
    current.cases = 715551;
    current.deaths = 33656;

    printReport(current);
}

void usePair()
{
    std::pair<bool, Report> query_result;
    query_result.first = true;
    query_result.second.date = "2023-12-16";
    query_result.second.cases = 100;
    query_result.second.deaths = 1000;

    cout << boolalpha << query_result.first << noboolalpha << endl;
    printReport(query_result.second);

    Report current = query_result.second;
    printReport(current);
}

void useTuple()
{
    std::tuple<string, size_t, size_t> myTuple;
    std::get<0>(myTuple) = "2023-12-17";
    std::get<1>(myTuple) = 200;
    std::get<2>(myTuple) = 2000;
    cout << std::get<0>(myTuple) << endl;
    cout << std::get<1>(myTuple) << endl;
    cout << std::get<2>(myTuple) << endl;
}

void useArray()
{
    std::array<int, 3> arr = {10, 2};
    arr[2] = 100;
    for (auto num : arr)
        cout << num << " ";
    cout << endl;
}

void useVector()
{
    std::vector<int> vec;
    vec.push_back(1);
    vec.resize(3);
    vec[2] = 3;
    for (auto num : vec)
        cout << num << " ";
    cout << endl;
}

void useAuto()
{
    auto a = 3;
    auto b = 4.3;
    auto c = 'X';
    auto d = "Hello";
    auto e = "Hello"s;
    auto f = std::make_pair(3, "Hello");
    auto g = {1, 2, 3};
    auto h = [](int i)
    { return 3 * i; };
}

void useUnpack()
{
    auto p = std::make_pair(true, 3);
    auto [found, num] = p;
    cout << found << " " << num << endl;

    auto arr = std::make_tuple('x', 'y', 'z', 'w');
    auto [a, b, c, d] = arr;
    cout << a << ' ' << b << ' ' << c << ' ' << d << endl;
}

int read_int(const std::string prompt)
{
    int val;
    std::cout << prompt;
    std::cin >> val;
    return val;
}

std::pair<std::pair<double, double>, bool> quadratic(int a, int b, int c)
{
    int D = b * b - 4 * a * c;
    if (D < 0)
        return {{0, 0}, false};
    else
    {
        double root1 = (-b + sqrt(D)) / (2 * a);
        double root2 = (-b - sqrt(D)) / (2 * a);
        return {{root1, root2}, true};
    }
}

void solveQuadratic()
{
    int a = read_int("Type in a: ");
    int b = read_int("Type in b: ");
    int c = read_int("Type in c: ");
    auto [roots, found] = quadratic(a, b, c);
    if (found)
    {
        auto [root1, root2] = roots;
        cout << "Roots are " << root1 << " " << root2 << endl;
    }
    else
        cout << "No roots found!" << endl;
}