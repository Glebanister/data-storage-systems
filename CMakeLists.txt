cmake_minimum_required(VERSION 3.12)
project(compression-bench)

set(CMAKE_CXX_STANDARD 17)
set(EXE compresJsion-bench)
add_executable(
        ${EXE}
        src/main.cpp
        
        extern/lz4/lib/lz4.c)
    
target_compile_options(${EXE} PRIVATE -Wall -Werror -Wextra -pedantic)
target_include_directories(${EXE} PUBLIC include)
target_link_libraries(${EXE} stdc++)
target_link_libraries(${EXE} m)

# Add lz4
target_include_directories(${EXE} PUBLIC extern/lz4/lib)

# # Add MurmurHash3
# target_include_directories(${EXE} PUBLIC extern/smhasher/src)

# # Add xxHash
# target_include_directories(${EXE} PUBLIC extern/xxHash/)
# add_subdirectory(extern/xxHash/cmake_unofficial)
# target_link_libraries(${EXE} xxhash)
