#include "lz4.h"

#include "lz4_wrapper.hpp"

namespace compression_bench {
std::size_t check_lz4_return_code(const std::string &algo_name, std::size_t return_code) {
    if (return_code == 0) {
        throw compression_exception("'" + algo_name + "': some error has occured");
    }
    return return_code;
}

lz4_wrapper::lz4_wrapper()
    : compression_algorithm("lz4") {}

std::size_t lz4_wrapper::compress(const std::uint8_t *src,
                                  std::size_t src_size,
                                  std::uint8_t *output,
                                  std::size_t output_capacity) {
    return check_lz4_return_code(
        get_name(),
        LZ4_compress_default(reinterpret_cast<const char *>(src),
                             reinterpret_cast<char *>(output),
                             src_size,
                             output_capacity));
}

std::size_t lz4_wrapper::decompress(const std::uint8_t *src,
                                    std::size_t src_size,
                                    std::uint8_t *output,
                                    std::size_t output_capacity) {
    return check_lz4_return_code(
        get_name(),
        LZ4_decompress_safe(reinterpret_cast<const char *>(src),
                            reinterpret_cast<char *>(output),
                            src_size,
                            output_capacity));
}
}  // namespace compression_bench
