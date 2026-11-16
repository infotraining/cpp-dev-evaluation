add_executable(task_06_lambdas_callbacks_test
    task_06_test.cpp
    $<$<NOT:$<BOOL:${BUILD_SOLUTIONS}>>:task_06_starter.cpp>
    $<$<BOOL:${BUILD_SOLUTIONS}>:task_06_solution.cpp>
)

target_include_directories(task_06_lambdas_callbacks_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_SOLUTIONS)
    target_compile_definitions(task_06_lambdas_callbacks_test PRIVATE USE_SOLUTION)
endif()

target_link_libraries(task_06_lambdas_callbacks_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(task_06_lambdas_callbacks_test)
