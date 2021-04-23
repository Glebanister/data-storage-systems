#include <filesystem>
#include <iostream>
#include <memory>

#include "compression_algorithm_benchmark.hpp"
#include "compression_algorithm_test.hpp"
#include "lz4_wrapper.hpp"
#include "zstd_wrapper.hpp"

int main(int argc, const char **argv) {
    if (argc < 3) {
        std::cout << argv[0] << " <input-dir> <output-dir>" << std::endl;
        return 0;
    }
    std::string input_directory = argv[1];
    std::vector<std::string> input_files;
    for (const auto &entry : std::filesystem::directory_iterator(input_directory)) {
        input_files.push_back(entry.path().string());
    }
    try {
        using namespace compression_bench;

        auto lz4 = std::make_shared<lz4_wrapper>();
        auto zstd1 = std::make_shared<zstd_wrapper>(1);
        auto zstd7 = std::make_shared<zstd_wrapper>(7);

        compression_algorithm_test(
            {
                lz4,
                zstd1,
                zstd7,
            },
            100,
            50,
            500);

        auto benchmark = compression_algorithm_benchmark(
            input_files,
            {
                lz4,
                zstd1,
                zstd7,
            },
            10);

        std::filesystem::path output_directory(argv[2]);
        std::filesystem::create_directories(output_directory);

        benchmark.export_to_csv(output_directory / "speed.csv", [](compression_stats stats) { return stats.get_ticks(); });
        benchmark.export_to_csv(output_directory / "compression.csv", [](compression_stats stats) { return stats.get_ratio(); });

    } catch (const std::exception &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error has occurred" << std::endl;
        return 1;
    }

    return 0;
}
