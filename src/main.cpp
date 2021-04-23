#include <iostream>
#include <memory>

#include "lz4_wrapper.hpp"
#include "zstd_wrapper.hpp"

int main() {
    using namespace compression_bench;

    unsigned char string[] = "Hello";
    lz4_wrapper lz4{};
    zstd_wrapper zstd1{1};
    zstd_wrapper zstd7{7};

    assert_algorithm_is_correct(lz4, string, sizeof(string), 100);
    assert_algorithm_is_correct(zstd1, string, sizeof(string), 100);
    assert_algorithm_is_correct(zstd7, string, sizeof(string), 100);
}
