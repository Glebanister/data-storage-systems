#include "zstd.h"

#include "zstd_wrapper.hpp"

namespace compression_bench {
std::size_t check_zstd_no_error(const std::string &algo_name, std::size_t code) {
    if (ZSTD_isError(code)) {
        throw compression_exception("'" + algo_name + "': " + ZSTD_getErrorName(code));
    }
    return code;
}

zstd_wrapper::zstd_wrapper(const std::size_t compression_level)
    : compression_algorithm(std::string{"zstd (lvl "} + std::to_string(compression_level) + ")"),
      compression_level_(compression_level) {}

std::size_t zstd_wrapper::compress(const std::uint8_t *src,
                                   std::size_t src_size,
                                   std::uint8_t *output,
                                   std::size_t output_capacity) {
    return check_zstd_no_error(
        get_name(),
        ZSTD_compress(output, output_capacity, src, src_size, compression_level_));
}

std::size_t zstd_wrapper::decompress(const std::uint8_t *src,
                                     std::size_t src_size,
                                     std::uint8_t *output,
                                     std::size_t output_capacity) {
    return check_zstd_no_error(
        get_name(),
        ZSTD_decompress(output, output_capacity, src, src_size));
}
}  // namespace compression_bench
