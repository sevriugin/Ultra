# see https://cmake.org/cmake/help/latest/module/FindBoost.html
set(Boost_USE_STATIC_LIBS OFF) #enable dynamic linking
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
find_package(Boost REQUIRED COMPONENTS unit_test_framework date_time filesystem system)

include_directories(${Boost_INCLUDE_DIR})
# Note: a target should be already defined using 'add_executable' or 'add_library'
add_executable(cmake_testapp_boost unit-test.cpp ../add.h ../add.cpp ../find-largest-sum.h ../find-largest-sum.cpp utils.h utils.cpp)
target_link_libraries(cmake_testapp_boost ${Boost_LIBRARIES})
