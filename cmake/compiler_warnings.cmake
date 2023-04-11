function(set_project_warnings project_name)
    set(CLANG_WARNINGS
        -Wall
        -Wextra
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2)

    set(GCC_WARNINGS
        ${CLANG_WARNING}
        -Wmisleading-indentation
        -Wduplicated-cond
        -Wduplicated-branches
        -Wlogical-op
        -Wuseless-cast
        )

    if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        set(PROJECT_WARNINGS ${CLANG_WARNINGS})
        message("Set Clang compiler warnings")
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(PROJECT_WARNINGS ${GCC_WARNINGS})
        message("Set GNU compiler warnings")
    endif()
        
    target_compile_options(${project_name} INTERFACE ${PROJECT_WARNINGS})

endfunction()
