#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// * Associative container has no idea of sequence
// * which means we have to access the data using key instead of index
// * So, Associative container could be view as set of index-value pairs
// * and so, the keys need to be unique so that the value get by indexing is unique (except multimap/multiset)

// * In C++, there are six types of associative container
// *    1. map
// *    2. set
// *    3. unordered_map
// *    4. unordered_set
// *    5. multimap
// *    6. multiset

// * Under the hood, map and set do sorting by the key, to reach fast data accessing
// * while unordered_map and unordered_set will no do sorting
// * Hence, the key passed into map and set need to be comparable, which means, you have to inplement < operator

// * When to use map/set vs. unordered_map/unordered_set?
// * Since map/set are sorted according to the key, so use them when you have a range of element to access
// * Versus, use unordered_map/unordered_set to access individual element

// * for map, the underlying types store in a std::map<K, V> is std::pair<const K, V>

// * Each STL set/map comes with an unordered sibling. Their usage is the same, with two differences:
// *    ● Instead of a comparison operator, the element (set) or key (map) must have a hash function defined for it (you'll learn more in A2).
// *    ● The unordered_map/unordered_set is generally faster than map/set.

// * Each STL set/map (+ unordered_set/map) comes with an multi- cousin. Their usage is the same, with two differences:
// *    ● You can have multiple of the same element (set) or key (map).
// *    ● insert, erase, and retrieving behave differently (since they may potentially have to retrieve multiple elements/values)

void useMap();
void useSet();

string getLine();

int main(int argc, char *argv[])
{
    // useMap();
    useSet();
    return 0;
}

string getLine()
{
    string response;
    std::getline(cin, response);
    return response;
}

void useMap()
{
    map<string, int> frequencyMap;
    cout << "Enter words: ";
    while (true)
    {
        cout << "> ";
        string response = getLine();
        if (response.empty())
            break;
        std::istringstream iss(response);
        string words;
        while (iss >> words)
        {
            // .at(key) will search the key and make sure is exists are throw an error
            // frequencyMap.at(words);
            // [key] will search and create the entry if the key doesn't exist
            // when creating the entry, the default initializer of value is used to create
            // for int, the default initializer is make the int to 0
            // for our own classes, just use the default initializer
            frequencyMap[words]++;
            // to check if a key exists, use
            // frequencyMap.contains(words);
        }
    }

    cout << "Enter the word you want to look up." << endl;
    while (true)
    {
        cout << "> ";
        string response = getLine();
        if (response.empty())
            break;
        // .count(key) will return the number of the keys equal to key
        // except multimap/multiset, this will returen 0/1.
        if (frequencyMap.count(response))
        {
            cout << frequencyMap[response] << " entries found" << endl;
        }
        else
        {
            cout << "None." << endl;
        }
    }

    // Since element in map is ordered, so we can also loop over them
    cout << "All frequencies: " << endl;
    for (const auto &[key, value] : frequencyMap)
        cout << key << ": " << value << endl;
}

void useSet()
{
    set<string> wordSet;
    cout << "Enter words: ";
    while (true)
    {
        cout << "> ";
        string response = getLine();
        if (response.empty())
            break;
        string word;
        istringstream iss(response);
        while (iss >> word)
        {
            wordSet.insert(word);
        }
    }

    // since set is ordered, so we can loop over them
    cout << "After unify: ";
    for (const auto &w : wordSet)
        cout << w << " ";
    cout << endl;
}