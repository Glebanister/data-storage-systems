#pragma once

#include <memory>
#include <vector>

#include "compression_algorithm.hpp"

namespace compression_bench {

void compression_algorithm_test(const std::vector<std::shared_ptr<compression_algorithm>> &,
                                std::size_t n_tests,
                                std::size_t each_test_size,
                                std::size_t each_test_max_size);

}  // namespace compression_bench
