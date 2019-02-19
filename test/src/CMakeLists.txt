set(CMAKE_BUILD_TYPE Debug)
add_executable(dks_test
    main.cpp
    test_case.cpp
    ${CMAKE_SOURCE_DIR}/src/test_case.cpp
    msa.cpp
    ${CMAKE_SOURCE_DIR}/src/msa.cpp
    model.cpp
    ${CMAKE_SOURCE_DIR}/src/model.cpp
    tree.cpp
    ${CMAKE_SOURCE_DIR}/src/tree.cpp
    partition.cpp
    ${CMAKE_SOURCE_DIR}/src/partition.cpp
)
target_include_directories(dks_test PRIVATE ${CMAKE_SOURCE_DIR}/lib/libpll/src/)
target_include_directories(dks_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(dks_test Catch2::Catch2)
target_link_libraries(dks_test pll_static)
target_compile_options(dks_test PRIVATE -Wall -Wextra -pedantic)
