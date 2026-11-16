add_executable(task_05_gtest_unit_tests_test
    task_05_test.cpp
    $<$<NOT:$<BOOL:${BUILD_SOLUTIONS}>>:task_05_starter.cpp>
    $<$<BOOL:${BUILD_SOLUTIONS}>:task_05_solution.cpp>
)

target_include_directories(task_05_gtest_unit_tests_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_SOLUTIONS)
    target_compile_definitions(task_05_gtest_unit_tests_test PRIVATE USE_SOLUTION)
endif()

target_link_libraries(task_05_gtest_unit_tests_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(task_05_gtest_unit_tests_test)
