#include <iterator>
#include <vector>
#include <algorithm>

int sortAsc(std::vector<int>& v)
{

    sort(v.rbegin(), v.rend());


    if (is_sorted(v.rbegin(), v.rend()))
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}

