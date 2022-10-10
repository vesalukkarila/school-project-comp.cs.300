#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v a sortable vector
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortMod3(std::vector<int>& v)

{
    sort(v.begin(), v.end());
    auto result = [](int a, int b){return a%3 < b%3;} ;
    sort(v.begin(), v.end(), result);
    for (auto a : v)
        cout << a << endl;

  return EXIT_FAILURE;
}
