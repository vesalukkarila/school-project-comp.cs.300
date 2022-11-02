#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Remove from vector v all elements with value less than the limit
 * @param v a vector whose values are to be erased if less than limit
 * @param limit a threshold whose lower values are removed
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int removeLessThan(std::vector<int>& v, int limit)
{
    auto remove = [&limit](int a){return a<limit;};
    auto iteraattori = remove_if(v.begin(), v.end(), remove);
    v.erase(iteraattori, v.end());
   
    if (v.size() == 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

