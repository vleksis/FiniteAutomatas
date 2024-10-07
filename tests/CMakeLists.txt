find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include(GoogleTest)

add_executable(IsoTest IsomorphicTests.cpp IsomorphicTests.h)

target_link_libraries(IsoTest AutomatasLib ${GTEST_LIBRARIES} pthread)

gtest_discover_tests(IsoTest)
