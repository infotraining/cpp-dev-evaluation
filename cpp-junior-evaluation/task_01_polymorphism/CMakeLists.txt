add_executable(task_01_polymorphism_test
    task_01_test.cpp
    $<$<NOT:$<BOOL:${BUILD_SOLUTIONS}>>:task_01_starter.cpp>
    $<$<BOOL:${BUILD_SOLUTIONS}>:task_01_solution.cpp>
)

target_include_directories(task_01_polymorphism_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_SOLUTIONS)
    target_compile_definitions(task_01_polymorphism_test PRIVATE USE_SOLUTION)
endif()

target_link_libraries(task_01_polymorphism_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(task_01_polymorphism_test)
