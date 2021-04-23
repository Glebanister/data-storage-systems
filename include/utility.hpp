#pragma once

#include <chrono>
#include <cstdint>

namespace compression_bench::utility {
static inline std::uint64_t get_cycles() {
    return std::chrono::steady_clock::now().time_since_epoch().count();
}
}  // namespace compression_bench::utility
