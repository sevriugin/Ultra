#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file

#include <sstream>
#include <iostream>
#include <utility>

#include <boost/test/unit_test.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "boost/filesystem.hpp"

#include "utils.h"

#include "../add.h"
#include "../find-largest-sum.h"

namespace fs = boost::filesystem;
namespace bdata = boost::unit_test::data;

const auto Underflow = "Underflow";
const auto Overflow = "Overflow";

/**
 * Get Bitwise add challenge test data from the test.txt file and convert it to string vector for `BOOST_DATA_TEST_CASE`
 * @return vector of test strings
 */
std::vector<std::string> getAddChallengeTestData() {
    using namespace std;
    using namespace boost;
    using namespace fs;

    string data;
    path p {"../../unit-test/test.txt"};
    load_string_file(p, data);

    return splitString(data,  (char[]) {"\n"});
}
/**
 * get Find largest sum challenge test data from the file and convert it to the string vector for `BOOST_DATA_TEST_CASE`
 * @return vector of test strings
 */
std::vector<std::string> getFindLargestSumChallengeTestData() {
    using namespace std;
    using namespace boost;
    using namespace fs;

    string data;
    path p {"../../unit-test/find-largest-sum-test.txt"};
    load_string_file(p, data);

    vector<string> lines = splitString(data,  (char[]) {"\n"});
    vector<string> result {};

    int count {0}; string test {};
    for (const string& line : lines) {
        if (!line.empty()) {
            test += line;
            count++;

            if (count == 3) {
                result.push_back(test);
                count = 0;
                test = "";
            } else {
                test += " ";
            }
        }
    }
    return result;
}

/**
 * Get vector of test arguments from test string
 * @param test_string
 * @return vector of test arguments
 */
std::vector<std::string> getTestArguments(std::string test_string) {
    return splitString(test_string,  (char[]) {" "});
}

/**
 * Check if exception has `Underflow` message
 * @param ex exception to check
 * @return `true` if exception what method returns `Underflow` message
 */
bool correctUnderflowMessage(const std::runtime_error& ex)
{
    BOOST_CHECK_EQUAL(ex.what(), std::string(Underflow));
    return true;
}
/**
 * Check if exception has `Overflow` message
 * @param ex exception to check
 * @return `true` if exception what method returns `Overflow` message
 */
bool correctOverflowMessage(const std::runtime_error& ex)
{
    BOOST_CHECK_EQUAL(ex.what(), std::string(Overflow));
    return true;
}

/**
 * Boost tests for Bitwise Add challenge
 */
BOOST_DATA_TEST_CASE(
        bitwise_add_test,
        bdata::make(getAddChallengeTestData()),
        test_string)
{
    using namespace std;

    vector<string> testArguments = getTestArguments(test_string);
    int64_t a { getNumber(testArguments[0]) }, b { getNumber(testArguments[1]) };
    string stringResult { isNumber(testArguments[2]) ? "" : testArguments[2] };

    cout << "-- bitwise add challenge -- " << endl;
    cout << "   " << a << " + " << b << " --> " << stringResult << testArguments[2] << endl;

    if (stringResult == Overflow) {
        BOOST_CHECK_EXCEPTION(add(a, b), std::runtime_error, correctOverflowMessage);
    } else if (stringResult == Underflow) {
        BOOST_CHECK_EXCEPTION(add(a, b), std::runtime_error, correctUnderflowMessage);
    } else if (stringResult.empty()) {
        int64_t c { getNumber(testArguments[2]) };
        BOOST_TEST(add(a,b) == c);
    }
}

/**
 * Boost tests for the find largest sum challenge
 */
BOOST_DATA_TEST_CASE(
        find_largest_sum_test,
        bdata::make(getFindLargestSumChallengeTestData()),
        test_string)
{
    using namespace std;

    cout << "-- find largest sum challenge -- " << endl;

    vector<string> testArguments = getTestArguments(test_string);

    uint64_t T { (uint64_t) getNumber(*testArguments.begin()) };
    vector<uint64_t> I = {};
    vector<uint64_t> M {};
    uint64_t S { 0 };
    uint64_t expectedS { (uint64_t) getNumber(*(testArguments.end()-1)) };

    for (int i = 1; i < testArguments.size() - 1; i++) {
        I.push_back( (uint64_t) getNumber(testArguments[i]));
    }

    find_largest_sum(T, I, M, S);

    cout << "   T: " << T << "  M: ";

    for_each(M.begin(), M.end(), [](uint64_t n) { cout << n << " "; });

    cout << " S: " << S << endl;

    BOOST_TEST(S == expectedS);
}

