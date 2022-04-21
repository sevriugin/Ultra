#include <iostream>
#include "add.h"
#include "find-largest-sum.h"

using namespace std;

int main() {

    /**
     * Bitwise addition example
     */
    int a { 100 }, b { 1 };

    cout << a << " + " << b << " = " << add(a, b) << endl;

    /**
     * Find largest sum example
     */
    uint64_t T = 11;
    std::vector<uint64_t> I = { 5, 6, 10 };
    std::vector<uint64_t> M {};
    uint64_t S { 0 };
    find_largest_sum(T, I, M, S);

    cout << "T: " << T << " M: ";
    for( uint64_t m: M ) {
        cout << m << " ";
    }
    cout << "S: " << S << endl;
    return 0;
}
