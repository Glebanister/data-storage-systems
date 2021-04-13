#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <chrono>
#include <random>

template <typename FunctorT, typename... Args>
inline std::size_t get_evaluation_time(FunctorT functor, Args &&... args) {
    using namespace std::chrono;
    auto begin_time = steady_clock::now();
    functor(std::forward<Args>(args)...);
    auto end_time = steady_clock::now();
    return (end_time - begin_time).count();
}

struct hash_functions_benchmark {
    using hasher_type = void (*)(const std::uint8_t *, std::size_t, std::int32_t, std::int32_t *);

    explicit hash_functions_benchmark(std::size_t len_begin,
                                      std::size_t len_end,
                                      std::size_t len_step,
                                      std::size_t tests_min,
                                      std::size_t tests_max,
                                      std::vector<std::pair<std::string, hasher_type>> hashers);

    void export_csv_to(std::ostream &os);

  private:
    void test_on_data_len(std::size_t data_len, std::size_t tests);

    std::vector<std::vector<double>> rows;
    std::vector<std::pair<std::string, hasher_type>> hash_functions;
    std::mt19937 rand;
};
