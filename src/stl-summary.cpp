#include <map>
#include <cmath>
#include <vector>
#include <cctype>
#include <sstream>
#include <fstream>
#include <numeric>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <filesystem>

// In the past six or so lectures, we talked about STL
// We talked about containers, iterators, adaptors, functors, lambdas, algorithms
// this is the map we look at the first lecture of STL
// Now you could understand this map pretty well
//
//      Algorithms    <-------   Functors/Lambdas
//          ^                           ^
//          |                           |
//      Iterators     <-------      Adaptors
//          ^                           ^
//          |                          /
//          |   ,---------------------'
//      Containers

// We actually have learned the most important concept of the STL, the remains are
// Useful libraries, like multi-threading, regex (regular expression) and so on...
// But the concepts still are the same

// STL provides us the abstration to solve the problem in a general setting
// instead of the particulars of the implementation

// * We stared off wih basic types: int/char/double/...
// * Each type is conceptually a "single value"

// * Container let us perform operations on the basic type, regardless of what the basic type is

// * Iterators allow us to abstract away from the container being used
// * Using iterators we can perform algorithm on the container

// * And finally, the algorithm provide us well-written algorithms so that
// * we can use various algorithms easily

// = Today what we are going to do is summary the STL by putting them together
// = to finish a stylometry problem: find who write the article of US constitution

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

const vector<string> FEATURE_VEC{"a", "about", "above", "after", "again", "against", "all", "am", "an", "and",
                                 "any", "are", "aren't", "as", "at", "be", "because", "been", "before", "being",
                                 "below", "between", "both", "but", "by", "can't", "cannot", "could", "couldn't",
                                 "did", "didn't", "do", "does", "doesn't", "doing", "don't", "down", "during",
                                 "each", "few", "for", "from", "further", "had", "hadn't", "has", "hasn't", "have",
                                 "haven't", "having", "he", "he'd", "he'll", "he's", "her", "here", "here's", "hers",
                                 "herself", "him", "himself", "his", "how", "how's", "i", "i'd", "i'll", "i'm",
                                 "i've", "if", "in", "into", "is", "isn't", "it", "it's", "its", "itself", "let's",
                                 "me", "more", "most", "mustn't", "my", "myself", "no", "nor", "not", "of", "off",
                                 "on", "once", "only", "or", "other", "ought", "our", "ours", "ourselves", "out",
                                 "over", "own", "same", "shan't", "she", "she'd", "she'll", "she's", "should",
                                 "shouldn't", "so", "some", "such", "than", "that", "that's", "the", "their",
                                 "theirs", "them", "themselves", "then", "there", "there's", "these", "they",
                                 "they'd", "they'll", "they're", "they've", "this", "those", "through", "to", "too",
                                 "under", "until", "up", "very", "was", "wasn't", "we", "we'd", "we'll", "we're",
                                 "we've", "were", "weren't", "what", "what's", "when", "when's", "where", "where's",
                                 "which", "while", "who", "who's", "whom", "why", "why's", "with", "won't", "would",
                                 "wouldn't", "you", "you'd", "you'll", "you're", "you've", "your", "yours",
                                 "yourself", "yourselves", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+",
                                 ",", "-", ".", "/", ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_",
                                 "`", "{", "|", "}", "~"};

string fileToString(ifstream &file)
{
    string ret = "";
    string line;

    while (getline(file, line))
    {
        std::transform(line.begin(), line.end(), line.begin(), tolower);
        ret += line + " ";
        // Or, but inserting a char each time is slower than inserting a line each time
        // std::transform(line.begin(), line.end(), std::back_inserter(ret), tolower);
    }

    return ret;
}

int countOccurence(const string &word, const string &text)
{
    string toFind = " " + word + " ";

    // the string::iterator is char,
    // so using std::count will count the occurrence of the characters
    // instead of words.
    // What we really need to use here is search
    auto curr = text.begin();
    auto end = text.end();
    int count = 0;
    while (curr != end)
    {
        auto found = std::search(curr, end, word.begin(), word.end());
        if (found == end)
            break;
        count += 1;
        curr = found + 1;
    }
    return count;
}

vector<int> createFreq(const string &text)
{
    vector<int> result;
    for (const auto &word : FEATURE_VEC)
    {
        result.push_back(countOccurence(word, text));
    }
    return result;
}

int dotProduct(const vector<int> &vec1, const vector<int> &vec2)
{
    // the STL has a inner_product in numeric
    // so just use them
    return std::inner_product(vec1.begin(), vec1.end(), vec2.end(), 0);
}

int mag(const vector<int> &vec)
{
    return std::sqrt(dotProduct(vec, vec));
}

double getSimilarity(const vector<int> &freqVec1, const vector<int> &freqVec2)
{
    int dotProd = dotProduct(freqVec1, freqVec2);

    return dotProd / (mag(freqVec1) * mag(freqVec2));
}

int main(int argc, char *argv[])
{
    ifstream hamilton_fs("/home/jack/projects/CS106L-2019Fall/src/res/hamilton.txt");
    ifstream jj_fs("/home/jack/projects/CS106L-2019Fall/src/res/jj.txt");
    ifstream madison_fs("/home/jack/projects/CS106L-2019Fall/src/res/madison.txt");
    ifstream unknown_fs("/home/jack/projects/CS106L-2019Fall/src/res/unknown.txt");

    string hamilton_txt = fileToString(hamilton_fs);
    string jj_txt = fileToString(jj_fs);
    string madison_txt = fileToString(madison_fs);
    string unknown_txt = fileToString(unknown_fs);

    // Create our feature vector
    vector<int> hamilton_vec = createFreq(hamilton_txt);
    vector<int> jj_vec = createFreq(jj_txt);
    vector<int> madison_vec = createFreq(madison_txt);
    vector<int> unknown_vec = createFreq(unknown_txt);

    // Compute the "angle" between feature vector of unknown and each of the three authors
    cout << "Similarity - hamilton <-> unknown: " << getSimilarity(hamilton_vec, unknown_vec) << endl;
    cout << "Similarity - jj <-> unknown: " << getSimilarity(jj_vec, unknown_vec) << endl;
    cout << "Similarity - madison <-> unknown: " << getSimilarity(madison_vec, unknown_vec) << endl;

    return 0;
}