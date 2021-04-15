#include "MurmurHash3.h"
#include "xxh3.h"

#include "hash_algorithms.hpp"

void mur_mur_hasher32::hash(const std::uint8_t *input_data, std::size_t len, std::int32_t seed, std::int32_t *output) {
    MurmurHash3_x86_32(input_data, static_cast<std::int32_t>(len), seed, output);
}

void xx_hasher32::hash(const std::uint8_t *input_data, std::size_t len, std::int32_t seed, std::int32_t *output) {
    *output = XXH32(input_data, len, seed);
}
