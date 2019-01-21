set(CMAKE_BUILD_TYPE Debug)
add_executable(dks_test
    main.cpp
)
target_link_libraries(dks_test Catch2::Catch2)
