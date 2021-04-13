#include <fstream>
#include <iostream>

#include "MurmurHash3.h"
#include "xxh3.h"

#include "hash_functions_benchmark.hpp"

class mur_mur_hasher32 {
  public:
    static void hash(const std::uint8_t *input_data, std::size_t len, std::int32_t seed, std::int32_t *output) {
        MurmurHash3_x86_32(input_data, static_cast<std::int32_t>(len), seed, output);
    }
};

class xx_hasher32 {
  public:
    static void hash(const std::uint8_t *input_data, std::size_t len, std::int32_t seed, std::int32_t *output) {
        *output = XXH32(input_data, len, seed);
    }
};

template <std::int32_t Base, std::int32_t Module>
class poly_hasher32 {
  private:
    static constexpr std::int32_t multiply(std::int32_t a, std::int32_t b) {
        return static_cast<std::int32_t>(static_cast<std::int64_t>(a)
            * static_cast<std::int64_t>(b)
            % static_cast<std::int64_t>(Module));
    }

  public:
    static void hash(const std::uint8_t *input_data, std::size_t len, std::int32_t seed, std::int32_t *output) {
        std::size_t n_blocks = len / 4;
        std::size_t tail_len = len - n_blocks * 4;
        std::int32_t result = seed;
        std::int32_t xn = 1;
        for (std::size_t i = 0; i < n_blocks; ++i) {
            std::int32_t data_block = input_data[i];
            result += multiply(data_block, xn);
            result %= Module;
            xn = multiply(xn, Base);
        }
        std::uint8_t tail[4] = {0, 0, 0, 0};
        for (std::size_t i = 0; i < tail_len; ++i) {
            tail[i] = input_data[i + n_blocks * 4];
        }
        std::int32_t tail_repr = 0;
        for (std::size_t i = 0; i < 4; ++i) {
            tail_repr += 1 << (i * 4);
        }
        result += multiply(tail_repr, xn);
        *output = result % Module;
    }
};

int main(const int argc, const char **argv) {
    if (argc < 4) {
        std::cout
            << "Usage: "
            << argv[0] << " <len_begin> <len_end> <len_step> [<output-file>]\n" <<
            "Output file is not required. Stdout will be used if output file is not specified.\n";
        return 0;
    }

    try {
        hash_functions_benchmark bench(std::stoi(argv[1]),
                                       std::stoi(argv[2]),
                                       std::stoi(argv[3]),
                                       200,
                                       1000,
                                       {
                                           {"MurmurHash3 32", mur_mur_hasher32::hash},
                                           {"XXHash 32", xx_hasher32::hash},
                                           {"Polynomial Hash 32", poly_hasher32<111, 1000000181>::hash}
                                       });
        if (argc >= 5) {
            std::ofstream out(argv[4]);
            bench.export_csv_to(out);
        } else {
            bench.export_csv_to(std::cout);
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
    }
}
