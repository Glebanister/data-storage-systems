#pragma once

#include "compression_algorithm.hpp"

namespace compression_bench {
class zstd_wrapper : public compression_algorithm {
   public:
    explicit zstd_wrapper(std::size_t compression_level);

    std::size_t compress(const std::uint8_t *src,
                         std::size_t src_size,
                         std::uint8_t *output,
                         std::size_t output_capacity) override;

    std::size_t decompress(const std::uint8_t *src,
                           std::size_t src_size,
                           std::uint8_t *output,
                           std::size_t output_capacity) override;

   private:
    const std::size_t compression_level_;
};
}  // namespace compression_bench
