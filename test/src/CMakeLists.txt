set(CMAKE_BUILD_TYPE Debug)
add_executable(dks_test
    main.cpp
    benchmark.cpp
    test_case.cpp
)
target_include_directories(dks_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/libpll/src/)
target_include_directories(dks_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(dks_test Catch2::Catch2)
