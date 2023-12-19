#include <random>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

struct Course
{
    string name;
    double rating;
};

// overload << for cout to print Course
std::ostream &operator<<(std::ostream &os, const Course &c)
{
    os << std::setw(15) << std::setfill(' ') << c.name << "  " << c.rating << endl;
    return os;
}

template <typename DataType>
std::ostream &operator<<(std::ostream &os, const vector<DataType> &v)
{
    for (auto i : v)
        cout << i << " ";
    return os;
}

vector<Course> readCourses()
{
    vector<Course> v = {
        {"CS 106A", 4.4337}, {"CS 106B", 4.4025}, {"CS 107", 4.6912}, {"CS 103", 4.0532}, {"CS 109", 4.6062}, {"CS 110", 4.343}, {"Math 51", 3.6119}, {"Math 52", 4.325}, {"Math 53", 4.3111}, {"Econ 1", 4.2552}, {"Anthro 3", 3.71}, {"Educ 342", 4.55}, {"Chem 33", 3.50}, {"German 132", 4.83}, {"Econ 137", 4.84}, {"CS 251", 4.24}, {"TAPS 103", 4.79}, {"Music 21", 4.37}, {"English 10A", 4.41}};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);
    return v;
}

vector<double> readNumbers()
{
    vector<double> numbers;
    std::generate_n(std::back_inserter(numbers), 10, std::rand);
    return numbers;
}

// * The STL (Standard Template Libarary) provide us with generic containers
// * which abstract the primitive types so that we can use the abstract without
// * considering the underlying data types

// * In the STL, they also proide algorithms that we can use
// * They are optimized so their speed is really fast

void useSort()
{
    auto courses = readCourses();
    auto numbers = readNumbers();

    // Sort takes begin iterator and end iterator
    // and this works fine
    std::sort(numbers.begin(), numbers.end());
    cout << numbers << endl;
    // = but this will cause the compiler throw towns of error
    // = this is because the template. The compiler will try all
    // = possible viable functions and none of them can compile, thus huge error message
    // std::sort(courses.begin(), courses.end());

    // why it throw errors is because the compiler don't know how
    // to compare two courses, so we need to tell the sort how to comapre for courses
    auto compareCourseName = [](const Course &c1, const Course &c2)
    {
        return c1.name < c2.name;
    };
    std::sort(courses.begin(), courses.end(), compareCourseName);

    // We can also compare by rating
    auto compareCourseRating = [](const Course &c1, const Course &c2)
    {
        return c1.rating < c2.rating;
    };
    std::sort(courses.begin(), courses.end(), compareCourseRating);
    cout << courses << endl;

    // we can use it to find the median rating course
    cout << courses[courses.size() / 2] << endl;
}

void useNth_Element()
{
    // sort is O(NlogN), while knowing the size of the container
    // we can actually achieve a O(N) algorithm
    // in STL, that is nth_element
    auto courses = readCourses();
    auto compareCourseRating = [](const Course &c1, const Course &c2)
    {
        return c1.rating < c2.rating;
    };

    // nth_element(first, nth, last, compare)
    // will sort part of the container to n-th element
    // so after call the function, just access the n-th element
    vector<Course>::iterator median;
    std::nth_element(
        courses.begin(), courses.begin() + courses.size() / 2, courses.end(),
        compareCourseRating);
    cout << courses[courses.size() / 2] << endl;
}

void usePatition()
{
    // stable_partition will partition the container and keep the relative order of the element
    vector<Course> courses = readCourses();

    string department = "CS";
    auto isDepartment = [department](const Course &c)
    {
        return c.name.size() > department.size() && c.name.substr(0, department.size()) == department;
    };

    std::stable_partition(courses.begin(), courses.end(), isDepartment);
    cout << courses << endl;
}

void useCopy_If()
{
    // we can use copy_if to copy some element from a container to another
    vector<Course> courses = readCourses();

    string department = "CS";
    auto isDepartment = [department](const Course &c)
    {
        return c.name.size() > department.size() && c.name.substr(0, department.size()) == department;
    };

    vector<Course> csCourses;
    // Just pass start iterator, end iterator, the destination and the predicate to the copy_if
    // = unfortunately, this code is buggy
    // std::copy_if(courses.begin(), courses.end(), csCourses.begin(), isDepartment);
    // * The reason is the vector is initialized in the default size
    // * but copy_if will write to the csCourses
    // * the copy_if doesn't has the ability to change the size of the destination container
    // * so when running copy_if, unintialized memory may be written
    // = we need a special iterator which can expand the size of the container when running
    // = so we use back_inserter which change the default vector iterator to one can expand the size of the iterator
    std::copy_if(courses.begin(), courses.end(), std::back_inserter(csCourses), isDepartment);
    // = back_inserter will returns a output iterator which can expand the container
    // = also, the returned iterator of back_inserter is called iterator adpator
    cout << csCourses << endl;
}

void useIteratorAdpator()
{
    vector<Course> courses = readCourses();
    // except back_inserter, we have other functions returning iterator adpator
    // for example, ostream_iterator
    // with the help of os_iterator and copy, we can copy the courses to cout
    // instead of using << operation
    std::copy(courses.begin(), courses.end(), std::ostream_iterator<Course>(cout, "\n"));
}

void useRemoveIf()
{
    // we can use remove if to remove element
    vector<Course> courses = readCourses();
    auto coursesCopy = courses;
    string department = "CS";
    auto isDepartment = [department](const Course &c)
    {
        return c.name.size() > department.size() && c.name.substr(0, department.size()) == department;
    };

    cout << courses.size() << endl;
    std::remove_if(courses.begin(), courses.end(), isDepartment);
    cout << courses.size() << endl;

    // * You may find out that the size of the contaner doesn't change
    // This is because what remove_if really do is to put the true element at the front of the container
    // while false are at the end
    // Since remove_if is not a member of vector, so it cannot change the size of the vector
    // remove_if will return the iterator pointing to the end of the section
    // so we can use vector.erase to remove the false element
    // courses.erase(remove_if(courses.begin(), courses.end(), isDepartment), courses.end());
    coursesCopy.erase(remove_if(coursesCopy.begin(), coursesCopy.end(), isDepartment), coursesCopy.end());
    cout << coursesCopy << endl;
    cout << coursesCopy.size() << endl;
}

void useFind()
{
    // algorithms also provide us with find function
    vector<double> numbers = readNumbers();

    // find will return a iterator pointing to the element
    double valueToFind = numbers[0];
    std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine{});
    auto iter = std::find(numbers.begin(), numbers.end(), valueToFind);
    cout << valueToFind << " " << *iter;

    // * note, nearly all the container has a find member function
    // * compared to std::find in algorithm, which is faster?
    // * For set/map, the .find is faster for their binary search tree implementation
    // * For vector and array, they are the same
}

int main(int argc, char *argv[])
{
    // useSort();
    // useNth_Element();
    // usePatition();
    // useCopy_If();
    // useIteratorAdpator();
    // useRemoveIf();
    useFind();
    return 0;
}