#include <algorithm>
#include <vector>

#include "find-largest-sum.h"

/**
 * Find the nearest positive number to T (<=) in I sorted vector and return index to it
 * @param T value to find
 * @param I vector to scan
 * @return the index of the biggest number <= T in I or -1
 */
int find_nearest_positive(uint64_t T, std::vector<uint64_t> &I) {
    if (I[0] > T) return -1;
    int index {0};
    /**
     * I[index] <= T
     */
    for (int i = 0; i < I.size(); i++) {
        if (I[i] == T) return i;
        if (I[i] > T) return index;
        index = i;
    }
    return index;
}

/**
 * Remove elements from ascending ordered uint64_t vector starting from value T
 * @param T value to find and start removing
 * @param I vector to change
 */
void remove_all_bigger_or_equal(uint64_t T, std::vector<uint64_t> &I) {
    int index = find_nearest_positive(T, I);

    if (index != -1) {
        I.erase(I.begin() + index, I.end());
    }
}

/**
 * Find one solution for problem: find subset `M` of vector `I` with sum of elements `M` nearest target `T`
 * @param T target to find
 * @param I array of elements
 * @param M resulting subset
 * @param S resulting sum
 */
void find_solution(uint64_t T, const std::vector<uint64_t> &I, std::vector<uint64_t> &M, uint64_t &S) {
    using namespace std;

    std::vector<uint64_t> sorted { I };

    S = 0; M = vector<uint64_t> {};

    uint64_t target { T };

    while(!sorted.empty()) {
        int index = find_nearest_positive(target, sorted);

        if (index == -1) {
            break;
        } else {
            uint64_t element = sorted[index];
            target-= element;
            S+= element;
            M.push_back(element);
            sorted.erase(sorted.begin() + index);

            if (target == 0) {
                break;
            }
        }
    }
    sort(M.begin(), M.end());
}

/**
 * Find best solution of the problem: find subset `M` of vector `I` with sum of elements `M` nearest target `T`
 * @param T target to find
 * @param I array of elements
 * @param M resulting subset
 * @param S resulting sum
 */
void find_largest_sum(uint64_t T, const std::vector<uint64_t> &I, std::vector<uint64_t> &M, uint64_t &S) {
    using namespace std;

    std::vector<uint64_t> sorted { I };

    sort(sorted.begin(), sorted.end());

    S = 0; M = vector<uint64_t> {};

    uint64_t solutionS { 0 }; std::vector<uint64_t> solutionM {};

    while(!sorted.empty()) {
        find_solution(T, sorted, solutionM, solutionS);

        if (solutionS == T) {
            M = solutionM;
            S = solutionS;

            break;
        } else if (solutionS > S) {
            M = solutionM;
            S = solutionS;

            uint64_t last = M.back();
            remove_all_bigger_or_equal(last, sorted);
        }
    }
}
