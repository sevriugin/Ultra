#include <iostream>
#include "add.h"
#include "find-largest-sum.h"

using namespace std;

int main() {

    cout << add(100, 1) << endl;

    uint64_t T = 11;
    std::vector<uint64_t> I = { 5, 6, 10 };
    std::vector<uint64_t> M {};
    uint64_t S { 0 };
    find_largest_sum(T, I, M, S);
    for( uint64_t m: M ) {
        cout << m << " ";
    }
    cout << endl << "Sum: " << S << endl;
    return 0;
}
