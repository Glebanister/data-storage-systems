#pragma once

#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "compression_algorithm.hpp"

namespace compression_bench {
class compression_algorithm_benchmark {
   public:
    explicit compression_algorithm_benchmark(const std::vector<std::string> &input_filenames,
                                             const std::vector<std::shared_ptr<compression_algorithm>> &algorithms);

    template <typename ExecutorT>
    void export_to_csv(const std::string &filename, ExecutorT executor) {
        std::ofstream output_file(filename);
        output_file << std::fixed << std::setprecision(4);
        if (!output_file.good()) {
            throw compression_exception("Unable to write to file '" + filename + "'");
        }
        output_file << "filename";
        for (const auto &algo_name : algorithm_names_) {
            output_file << "," << algo_name;
        }
        output_file << '\n';
        for (std::size_t file_i = 0; file_i < input_filenames_.size(); ++file_i) {
            output_file << '"' << input_filenames_[file_i] << '"';
            for (std::size_t algo_i = 0; algo_i < algorithm_names_.size(); ++algo_i) {
                output_file << ',' << executor(stats_[file_i][algo_i]);
            }
            output_file << '\n';
        }
    }

   private:
    std::vector<std::vector<compression_stats>> stats_;
    std::vector<std::string> input_filenames_;
    std::vector<std::string> algorithm_names_;
};
}  // namespace compression_bench
