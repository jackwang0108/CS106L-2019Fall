#include <iostream>     // for cout, cin
#include <utility>      // for pair
#include <tuple>        // for tuple
#include <array>        // for array
#include <vector>       // for vector
#include <fstream>      // for ifstream
#include <sstream>      // for istringstream
#include <iomanip>      // for setprecision
#include <map>          // for map
#include <set>          // for set

template <typename T, typename ...Ts>
auto my_min(T num, Ts... args);

template <typename T>
auto my_min(T num);

int main() {
    int min = my_min(3, 4, 5, 6, 2);
    std::cout << min << std::endl;

}

template <typename T, typename ...Ts>
auto my_min(T num, Ts... args) {
  auto min = my_min(args...);
  if (num < min) min = num;
  return min;
}

template <typename T>
auto my_min(T num) {
    return num;
}



