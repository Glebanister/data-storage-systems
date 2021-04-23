#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

namespace compression_bench {
class compression_exception : public std::exception {
   public:
    explicit compression_exception(std::string message);

    const char *what() const noexcept override;

   private:
    const std::string message_;
};

class compression_algorithm {
   public:
    explicit compression_algorithm(std::string name);

    virtual std::size_t compress(const std::uint8_t *src,
                                 std::size_t src_size,
                                 std::uint8_t *output,
                                 std::size_t output_capacity) = 0;

    virtual std::size_t decompress(const std::uint8_t *src,
                                   std::size_t src_size,
                                   std::uint8_t *output,
                                   std::size_t output_capacity) = 0;

    virtual ~compression_algorithm() = default;

    [[nodiscard]] const std::string &get_name() const noexcept;

   private:
    const std::string name_;
};

struct compression_stats {
    double total_ratio = 0.0;
    std::uint64_t total_ticks = 0;
    std::size_t runs = 0;

    [[nodiscard]] double get_ratio() const noexcept;
    [[nodiscard]] std::uint64_t get_ticks() const noexcept;
};

compression_stats &operator+=(compression_stats &, const compression_stats &);

void assert_algorithm_is_correct(compression_algorithm &,
                                 const std::uint8_t *data,
                                 std::size_t length,
                                 std::size_t max_output_length);

compression_stats test_compression_algorithm(compression_algorithm &,
                                             const std::uint8_t *data,
                                             std::size_t length,
                                             std::size_t max_output_length);
}  // namespace compression_bench
