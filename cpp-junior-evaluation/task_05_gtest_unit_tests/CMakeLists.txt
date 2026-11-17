if (BUILD_SOLUTIONS)
    file(GLOB SOLUTION_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*_solution*.cpp")
endif()

add_executable(task_05_gtest_unit_tests_test
    $<$<NOT:$<BOOL:${BUILD_SOLUTIONS}>>:task_05_test.cpp>
    $<$<NOT:$<BOOL:${BUILD_SOLUTIONS}>>:task_05.cpp>
    $<$<BOOL:${BUILD_SOLUTIONS}>:${SOLUTION_SOURCES}>
)

target_include_directories(task_05_gtest_unit_tests_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_SOLUTIONS)
    target_compile_definitions(task_05_gtest_unit_tests_test PRIVATE USE_SOLUTION)
endif()

target_link_libraries(task_05_gtest_unit_tests_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(task_05_gtest_unit_tests_test)
