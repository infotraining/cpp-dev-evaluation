add_executable(task_09_stl_algorithms_test
    test.cpp
    $<$<NOT:$<BOOL:${BUILD_SOLUTIONS}>>:starter.cpp>
    $<$<BOOL:${BUILD_SOLUTIONS}>:solution.cpp>
)

target_include_directories(task_09_stl_algorithms_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_SOLUTIONS)
    target_compile_definitions(task_09_stl_algorithms_test PRIVATE USE_SOLUTION)
endif()

target_link_libraries(task_09_stl_algorithms_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(task_09_stl_algorithms_test)
