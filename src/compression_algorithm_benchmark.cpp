#include "compression_algorithm_benchmark.hpp"

#include <fstream>

namespace compression_bench {
compression_algorithm_benchmark::compression_algorithm_benchmark(
    const std::vector<std::string> &input_filenames,
    const std::vector<std::shared_ptr<compression_algorithm>> &algorithms,
    std::size_t benchmark_runs)
    : stats_(input_filenames.size(), std::vector<compression_stats>(algorithms.size())),
      input_filenames_(input_filenames) {
    for (std::size_t run_i = 0; run_i < benchmark_runs; ++run_i) {
        std::size_t input_file_i = 0;
        for (const std::string &input_filename : input_filenames) {
            std::ifstream input_file(input_filename);
            std::string contents((std::istreambuf_iterator<char>(input_file)),
                                 std::istreambuf_iterator<char>());
            std::size_t algorithm_i = 0;
            for (const auto &algorithm : algorithms) {
                stats_[input_file_i][algorithm_i] +=
                    test_compression_algorithm(*algorithm,
                                               reinterpret_cast<const std::uint8_t *>(contents.data()),
                                               contents.size(),
                                               std::max(200, static_cast<int>((contents.size() * 3 / 2))));
                ++algorithm_i;
            }
            ++input_file_i;
        }
    }
    algorithm_names_.reserve(algorithms.size());
    for (const auto &algo : algorithms) {
        algorithm_names_.push_back(algo->get_name());
    }
}
}  // namespace compression_bench
