#include <tuple>
#include <string>
#include <vector>
#include <iostream>

#define UNUSED __attribute__((unused))

using namespace std;

struct Time
{
    int hour, minute;
};

struct Course
{
    string code;
    pair<Time, Time> time;
    vector<string> instructors;
};

void useSize_t();
auto recapAuto(const vector<string> &v);
void recapPair();
void recapStruct();
void recapAll();
void uniformInitialization();
void shiftBuggy1(vector<Course> &courses);
void shiftBuggy2(vector<Course> &courses);
int doubleValue(int &x);
void useReference();
void constReference();
void constAutoReference();
void returnReference();
void shiftCorrect1(vector<Course> &courses);
void shiftCorrect2(vector<Course> &courses);
void referenceSummary();

int main(int argc, char *argv[])
{
    // recapAll();
    // uniformInitialization();

    // useReference();
    // constAutoReference();
    // returnReference();
    referenceSummary();
    return 0;
}

void useSize_t()
{
    string str = "Hello World!";
    for (size_t i; i < str.size(); i++)
        cout << str[i] << endl;
}

auto recapAuto(const vector<string> &v)
{
    auto multiplier = 2.4;
    auto name UNUSED = "Ito-En";
    auto betterName1 = string{"Ito-En"};
    const auto &betterName2 = string{"Ito-En"};
    auto copy = v;
    auto &refMult UNUSED = multiplier;
    auto func UNUSED = [](auto i)
    { return i * 2; };

    return betterName1;
}

void recapPair()
{
    auto prices = make_pair(3.4, 5);
    auto values = make_tuple(3, 4, "hi");

    prices.first = prices.second;
    get<0>(values) = get<1>(values);

    auto [a, b] = prices;
    cout << a << " " << b << endl;
}

void recapStruct()
{
    struct Discount
    {
        double discountFactor;
        int expirationDate;
        string nameOfDiscount;
    };
    auto coupon1 = Discount{0.9, 30, "New Years"};
    Discount coupon2{0.75, 7, "Valentine's Day"};

    coupon1.discountFactor = 0.8;
    coupon2.expirationDate = coupon1.expirationDate;

    auto [factor, date, name] = coupon1;
    cout << factor << " " << date << " " << name << endl;
}

std::pair<Course, bool> find(vector<Course> &courses, string &target)
{
    for (size_t i; i < courses.size(); i++)
    {
        auto [code, time, instructors] = courses[i];
        if (code == target)
            return {courses[i], true};
    }
    return {{}, false};
}

std::pair<Course, bool> findForEach(vector<Course> &courses, string &target)
{
    for (auto course : courses)
    {
        auto [code, time, instructors] = course;
        if (code == target)
            return {course, true};
    }
    return {{}, false};
}

std::pair<Course, bool> findForEachBetter(vector<Course> &courses, string &target)
{
    for (auto [code, time, instructors] : courses)
        if (code == target)
            return {{code, time, instructors}, true};
    return {{}, false};
}

void recapAll()
{
    vector<string> str_vec = {
        "This"s,
        "is"s,
        "my"s,
        "book"s};
    for (const auto &str : str_vec)
        cout << str << endl;
    cout << recapAuto(str_vec) << endl;
    recapPair();
    recapStruct();
}

void uniformInitialization()
{
    // Ways to initialize anything
    std::vector<string> default_init;
    std::vector<string> value_init{};
    std::vector<string> direct_init{3, "init"};
    std::vector<string> copy_init = {3, "init"};
    std::vector<string> list_init{"1", "2", "3"};
    std::vector<string> aggr_init = {"1", "2", "3"};

    // Most used initialization methods
    auto mostUsed_default UNUSED = default_init;
    // * set element number as well as set their values
    auto mostUsed_uniform UNUSED = direct_init;
    auto mostUsed_list UNUSED = list_init;

    // Careful for initialization
    std::vector<int> list_initialization{3, 2}; // * {3, 2}
    std::vector<int> fill_initialization(3, 2); // * {2, 2, 2}
    for (auto num : list_initialization)
        cout << num << " ";
    cout << endl;
    for (auto num : fill_initialization)
        cout << num << " ";
    cout << endl;

    // = Note, this will not return initializer_list, instead of vector
    // auto initializer_list{3, 2};

    // We may use the following to initialize a sturct
    Course now{"CS106L", {{13, 30}, {14, 30}}, {"Wang", "Zeng"}};

    cout << "Use uniform initialization as your default way to call any constructor." << endl;
    cout << "Be careful of ambiguities with initializer_list." << endl;
}

void shiftBuggy1(vector<Course> &courses)
{
    for (size_t i; i < courses.size(); i++)
    {
        // = This is buggy, since unpack aggregated structures will make a copy
        auto [code, time, instructors] = courses[i];
        time.first.hour++;
        time.first.hour++;
    }
}

void shiftBuggy2(vector<Course> &courses)
{
    // = This is also buggy, unpack makes copy every time
    // = We need to use refrences if we want to change the unpacked values
    for (auto [code, time, instructors] : courses)
    {
        time.first.hour++;
        time.second.hour++;
    }
}

int doubleValue(int &x)
{
    x *= 2;
    return x;
}

void useReference()
{
    // use refrences
    int myValue = 5;
    int result = doubleValue(myValue);
    cout << myValue << endl;
    cout << result << endl;

    vector<int> original{1, 2};
    vector<int> copy = original;
    vector<int> &lref = original;

    original.push_back(3);
    copy.push_back(4);
    lref.push_back(5);

    for (auto i : original)
        cout << i << " ";
    cout << endl;

    for (auto i : copy)
        cout << i << " ";
    cout << endl;

    for (auto i : lref)
        cout << i << " ";
    cout << endl;

    // instead of change refrence, it will call the copy operator =
    lref = copy;
    copy.push_back(6);
    lref.push_back(7);

    for (auto i : original)
        cout << i << " ";
    cout << endl;

    for (auto i : copy)
        cout << i << " ";
    cout << endl;

    for (auto i : lref)
        cout << i << " ";
    cout << endl;
}

void constReference()
{
    // = a const variable cannot be modified after construction
    cout << "a const variable cannot be modified after construction" << endl;

    vector<int> vec{1, 2, 3};
    const vector<int> c_vec{7, 8};
    vector<int> &lref = vec;
    const vector<int> &c_lref UNUSED = c_vec;

    vec.push_back(3);
    lref.push_back(3);
    // = this cause errors when compiling, you cannot modify const
    // c_vec.push_back(3);
    // c_lref.push_back(3);
}

void constAutoReference()
{
    vector<int> vec{1, 2, 3};
    const vector<int> c_vec{7, 8};

    vector<int> &lref = vec;
    const vector<int> &c_lref = c_vec;

    // = auto drops const/reference unless explicitly specified
    cout << "auto drops const/reference unless explicitly specified" << endl;

    // auto defaultly creates a non-const vector which copies refrence
    auto copy = c_lref;
    // to make the copied vector const, use const
    const auto c_copy = c_lref;

    // use auto to create a refrence
    auto &alref = lref;
    // use auto to create a const reference
    const auto &c_alred = lref;

    for (auto i : alref)
        cout << i << ' ';
    cout << endl;

    for (auto i : c_alred)
        cout << i << ' ';
    cout << endl;
}

int &front(std::vector<int> &vec)
{
    return vec[0];
}

void returnReference()
{
    vector<int> numbers{1, 2, 3};
    for (auto i : numbers)
        cout << i << " ";
    cout << endl;

    //
    front(numbers) = 4;
    for (auto i : numbers)
        cout << i << " ";
    cout << endl;
}

void shiftCorrect1(vector<Course> &courses)
{
    for (size_t i = 0; i < courses.size(); i++)
    {
        // = create a reference when unpacking if we want to change it
        auto &[code, time, instructors] = courses[i];
        time.first.hour++;
        time.second.hour++;
    }
}

void shiftCorrect2(vector<Course> &courses)
{
    // = create a reference when unpacking if we want to change it
    for (auto &[code, time, instructors] : courses)
    {
        time.first.hour++;
        time.second.hour++;
    }
}

void referenceSummary()
{
    cout << "reference: an alias" << endl;
    cout << "const: can't modify " << endl;
    cout << "auto: drops const/reference" << endl;
    cout << "only return references to non-local vars" << endl;
}