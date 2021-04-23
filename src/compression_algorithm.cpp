#include "compression_algorithm.hpp"

#include <algorithm>
#include <cstring>
#include <memory>

#include "utility.hpp"

namespace compression_bench {
compression_exception::compression_exception(std::string message)
    : message_(std::move(message)) {}

const char *compression_exception::what() const noexcept {
    return message_.c_str();
}

std::unique_ptr<std::uint8_t[]> get_memory(std::size_t length) {
    return std::make_unique<std::uint8_t[]>(length);
}

compression_algorithm::compression_algorithm(std::string name)
    : name_(std::move(name)) {}

const std::string &compression_algorithm::get_name() const noexcept {
    return name_;
}

void assert_algorithm_is_correct(compression_algorithm &algorithm,
                                 const std::uint8_t *data,
                                 std::size_t length,
                                 std::size_t max_output_length) {
    const std::size_t output_length = max_output_length;
    std::unique_ptr<std::uint8_t[]> output_memory = get_memory(output_length);
    std::size_t result_length = algorithm.compress(data,
                                                   length,
                                                   output_memory.get(),
                                                   output_length);
    std::unique_ptr<std::uint8_t[]> decompressed = get_memory(output_length);
    std::size_t decompressed_size = algorithm.decompress(output_memory.get(),
                                                         result_length,
                                                         decompressed.get(),
                                                         output_length);
    if (length != decompressed_size) {
        throw compression_exception(std::string{"Error while checking '"} +
                                    algorithm.get_name() +
                                    "': Invalid decompressed data length");
    }
    if (std::memcmp(decompressed.get(), data, length) != 0) {
        throw compression_exception(std::string{"Error while checking '"} +
                                    algorithm.get_name() +
                                    "': Invalid compression result");
    }
}

compression_stats test_compression_algorithm(compression_algorithm &algorithm,
                                             const std::uint8_t *data,
                                             std::size_t length,
                                             std::size_t max_output_length) {
    std::unique_ptr<std::uint8_t[]> output_memory = std::make_unique<std::uint8_t[]>(max_output_length);
    std::uint64_t start_ticks = utility::get_cycles();
    std::size_t output_length = algorithm.compress(data, length, output_memory.get(), max_output_length);
    std::uint64_t end_ticks = utility::get_cycles();

    return compression_stats{
        static_cast<double>(length) / static_cast<double>(output_length),
        end_ticks - start_ticks};
}
}  // namespace compression_bench
