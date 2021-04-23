#include <iostream>
#include <memory>

#include "compression_algorithm_benchmark.hpp"
#include "compression_algorithm_test.hpp"
#include "lz4_wrapper.hpp"
#include "zstd_wrapper.hpp"

int main() {
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
            {
                "sample_data.txt",
                "sample_data_2.txt",
            },
            {
                lz4,
                zstd1,
                zstd7,
            },
            20);

        benchmark.export_to_csv("speed.csv", [](compression_stats stats) { return stats.get_ticks(); });
        benchmark.export_to_csv("compression.csv", [](compression_stats stats) { return stats.get_ratio(); });

    } catch (const std::exception &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error has occurred" << std::endl;
        return 1;
    }

    return 0;
}
