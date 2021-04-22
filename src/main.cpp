#include <iostream>
#include <memory>

#include "lz4.h"
#include "zstd.h"

int main() {
    char string[] = "Hello";
    std::unique_ptr<char []> output = std::make_unique<char []>(10);
    LZ4_compress_default(string, output.get(), sizeof(string), 10);
}
