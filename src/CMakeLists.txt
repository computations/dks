add_executable(raxml-dks 
    main.cpp
)
set_target_properties(raxml-dks PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
)
set(${CMAKE_BUILD_TYPE} DEBUG)
