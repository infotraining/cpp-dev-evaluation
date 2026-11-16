add_executable(task_08_stl_containers_test
    task_08_test.cpp
    $<$<NOT:$<BOOL:${BUILD_SOLUTIONS}>>:task_08_starter.cpp>
    $<$<BOOL:${BUILD_SOLUTIONS}>:task_08_solution.cpp>
)

target_include_directories(task_08_stl_containers_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_SOLUTIONS)
    target_compile_definitions(task_08_stl_containers_test PRIVATE USE_SOLUTION)
endif()

target_link_libraries(task_08_stl_containers_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(task_08_stl_containers_test)
