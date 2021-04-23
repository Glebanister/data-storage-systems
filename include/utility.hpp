#pragma once

#include <cstdint>

namespace compression_bench::utility {
static inline std::uint64_t get_cycles() {
    uint64_t t;
    __asm volatile("rdtsc"
                   : "=A"(t));
    return t;
}
}  // namespace compression_bench::utility
