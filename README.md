# Compression algorithms benchmark

## Installation

First, make sure `cmake` and `git` are installed on your machine.
Then execute following commands

```bash
git clone --recursive https://github.com/Glebanister/data-storage-systems
git checkout hw-02-compression-bench
mkdir build && cd build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Benchmark execution

```bash
./build/compression-bench <input-dir> <output-dir>
```

## Graph generation

```bash
./benchmark_graph.py <input_filename> <mode>
```
