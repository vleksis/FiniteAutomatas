find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include(GoogleTest)

add_executable(IsoTest IsomorphicTests.cpp IsomorphicTests.h)
add_executable(Task2aTest Task2aTest.cpp Task2aTest.h)

target_link_libraries(IsoTest AutomatasLib ${GTEST_LIBRARIES} pthread)
target_link_libraries(Task2aTest AutomatasLib ${GTEST_LIBRARIES} pthread)

gtest_discover_tests(IsoTest)
gtest_discover_tests(Task2aTest)
