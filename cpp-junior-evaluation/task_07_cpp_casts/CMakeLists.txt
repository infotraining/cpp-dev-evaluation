add_executable(task_07_cpp_casts_test
    task_07_test.cpp
    $<$<NOT:$<BOOL:${BUILD_SOLUTIONS}>>:task_07_starter.cpp>
    $<$<BOOL:${BUILD_SOLUTIONS}>:task_07_solution.cpp>
)

target_include_directories(task_07_cpp_casts_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_SOLUTIONS)
    target_compile_definitions(task_07_cpp_casts_test PRIVATE USE_SOLUTION)
endif()

target_link_libraries(task_07_cpp_casts_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(task_07_cpp_casts_test)
