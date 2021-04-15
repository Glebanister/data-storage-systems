#include <fstream>
#include <iostream>

#include "hash_functions_benchmark.hpp"
#include "hash_algorithms.hpp"

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
                                       1000000,
                                       1000000,
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
        return 1;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
        return 1;
    }
}
