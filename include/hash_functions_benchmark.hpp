#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <chrono>
#include <random>

#include "Platform.h"

template <typename FunctorT, typename... Args>
inline std::uint64_t get_evaluation_ticks(FunctorT functor, Args &&... args) {
    volatile uint64_t begin, end;
    begin = rdtsc();
    functor(std::forward<Args>(args)...);
    end = rdtsc();
    return end - begin;
}

class hash_functions_benchmark {
  public:
    using hasher_type = void (*)(const std::uint8_t *, std::size_t, std::int32_t, std::int32_t *);

    explicit hash_functions_benchmark(std::size_t len_begin,
                                      std::size_t len_end,
                                      std::size_t len_step,
                                      std::size_t tests_min,
                                      std::size_t tests_max,
                                      std::vector<std::pair<std::string, hasher_type>> hash_algorithms);

    void export_csv_to(std::ostream &os);

  private:
    void test_on_data_len(std::size_t data_len, std::size_t tests);

    std::vector<std::vector<double>> rows_;
    std::vector<std::pair<std::string, hasher_type>> hash_algorithms_;
    std::mt19937 rand_;
};
