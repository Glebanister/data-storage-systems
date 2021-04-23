#include "compression_algorithm_test.hpp"

#include <algorithm>
#include <chrono>
#include <random>

namespace compression_bench {
void compression_algorithm_test(
    const std::vector<std::shared_ptr<compression_algorithm>> &algorithms,
    std::size_t n_tests,
    std::size_t each_test_size,
    std::size_t each_test_max_size) {
    std::mt19937 random(std::chrono::steady_clock::now().time_since_epoch().count());

    for (std::size_t test_i = 0; test_i < n_tests; ++test_i) {
        std::vector<std::uint8_t> random_data(each_test_size);
        std::generate(random_data.begin(), random_data.end(), [&random]() { return random(); });
        for (const auto &algorithm : algorithms) {
            assert_algorithm_is_correct(*algorithm, random_data.data(), random_data.size(), each_test_max_size);
        }
    }
}
}  // namespace compression_bench
