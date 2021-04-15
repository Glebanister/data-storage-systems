#include <stdexcept>
#include <iomanip>
#include <algorithm>

#include "hash_functions_benchmark.hpp"

hash_functions_benchmark::hash_functions_benchmark(std::size_t len_begin,
                                                   std::size_t len_end,
                                                   std::size_t len_step,
                                                   std::size_t tests_min,
                                                   std::size_t tests_max,
                                                   std::vector<std::pair<std::string, hasher_type>> hash_algorithms)
    : rows_(0),
      hash_algorithms_(std::move(hash_algorithms)),
      rand_(std::chrono::system_clock::now().time_since_epoch().count()) {
    if (tests_min > tests_max) {
        throw std::logic_error("times_min can not be greater than times_max");
    }
    for (std::size_t len = len_begin; len < len_end; len += len_step) {
        double progress = static_cast<double>(len) / static_cast<double>(len_end);
        auto tests_inc = static_cast<std::size_t>(static_cast<double>(tests_max - tests_min) * (1.0 - progress));
        test_on_data_len(len, std::max(1UL, tests_min + tests_inc));
    }
}

void hash_functions_benchmark::export_csv_to(std::ostream &os) {
    auto initial_precision = os.precision();
    os << std::fixed << std::setprecision(4);
    for (std::size_t hasher_i = 0; hasher_i < hash_algorithms_.size(); ++hasher_i) {
        os << hash_algorithms_[hasher_i].first << (hasher_i == hash_algorithms_.size() - 1 ? "" : ",");
    }
    os << '\n';
    for (const auto &row : rows_) {
        for (std::size_t i = 0; i < row.size(); ++i) {
            os << row[i] << (i == row.size() - 1 ? "" : ",");
        }
        os << '\n';
    }
    os << std::setprecision(static_cast<std::int32_t>(initial_precision));
}

void hash_functions_benchmark::test_on_data_len(std::size_t data_len, std::size_t tests) {
    std::vector<double> test_results(hash_algorithms_.size());
    for (std::size_t test_i = 0; test_i < tests; ++test_i) {
        std::vector<std::uint8_t> random_data(data_len);
        std::generate(random_data.begin(), random_data.end(), [this]() { return rand_(); });
        for (std::size_t hf_i = 0; hf_i < hash_algorithms_.size(); ++hf_i) {
            auto &hash_algorithm = hash_algorithms_[hf_i];
            std::int32_t output = 0;
            double ticks = static_cast<double>(
                get_evaluation_ticks(hash_algorithm.second,
                                     random_data.data(),
                                     data_len,
                                     rand_(),
                                     &output));
            test_results[hf_i] += ticks;
        }
    }
    std::for_each(test_results.begin(), test_results.end(), [tests](auto &res) { res /= tests; });
    rows_.push_back(std::move(test_results));
}
