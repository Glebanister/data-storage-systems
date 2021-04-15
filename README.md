# Hash algorithms benchmark

Examination of running times of different hashing algorithms on data of different lengths.

## Installation

First, make sure `git` and `cmake` are installed on your machine.

```bash
git clone --recurse-submodules https://github.com/Glebanister/data-storage-systems
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Benchmark execution

```bash
./build/hash-bench <len_begin> <len_end> <len_step> [<output_file>]
```

Output file is not required. `stdout` will be used if output file is not specified.

## Graph generation

```bash
./benchmark_graph.py <generated_file>.svg <len_begin> <len_end> <len_step>
```
