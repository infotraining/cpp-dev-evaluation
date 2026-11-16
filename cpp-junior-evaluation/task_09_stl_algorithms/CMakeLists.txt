if (BUILD_SOLUTIONS)
    file(GLOB SOLUTION_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*_solution*.cpp")
endif()

add_executable(task_09_stl_algorithms_test
    task_09_test.cpp
    $<$<NOT:$<BOOL:${BUILD_SOLUTIONS}>>:task_09.cpp>
    $<$<BOOL:${BUILD_SOLUTIONS}>:${SOLUTION_SOURCES}>
)

target_include_directories(task_09_stl_algorithms_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_SOLUTIONS)
    target_compile_definitions(task_09_stl_algorithms_test PRIVATE USE_SOLUTION)
endif()

target_link_libraries(task_09_stl_algorithms_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(task_09_stl_algorithms_test)
