cmake_minimum_required(VERSION 3.12)
project(hash-bench)

set(CMAKE_CXX_STANDARD 17)
set(EXE hash-bench)
add_executable(
        ${EXE}
        src/main.cpp
        extern/smhasher/src/MurmurHash3.cpp
        src/hash_functions_benchmark.cpp
        src/hash_algorithms.cpp)
target_compile_options(${EXE} PRIVATE -Wall -Wextra -pedantic)
target_include_directories(${EXE} PUBLIC include)
target_link_libraries(${EXE} stdc++)
target_link_libraries(${EXE} m)

# Add MurmurHash3
target_include_directories(${EXE} PUBLIC extern/smhasher/src)

# Add xxHash
target_include_directories(${EXE} PUBLIC extern/xxHash/)
add_subdirectory(extern/xxHash/cmake_unofficial)
target_link_libraries(${EXE} xxhash)
