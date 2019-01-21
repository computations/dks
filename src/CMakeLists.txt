add_executable(raxml-dks 
    main.cpp
    msa.cpp
    test_case.cpp
)
set_target_properties(raxml-dks PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
)
set(${CMAKE_BUILD_TYPE} DEBUG)
target_include_directories(raxml-dks PRIVATE ${CMAKE_SOURCE_DIR}/lib/libpll/src/)
