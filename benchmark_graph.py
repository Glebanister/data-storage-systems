#!/usr/bin/python3.8

from sys import argv
import csv
import matplotlib.pyplot as plt


def main(args: [str]):
    if len(args) < 4:
        print('Arguments: <input_filename> <min> <max> <step>')
        return
    input_file = open(args[0], 'r')
    len_min = int(args[1])
    len_max = int(args[2])
    len_step = int(args[3])
    hasher_names = input_file.readline().split(',')
    hashers = len(hasher_names)
    hasher_averages = [[] for _ in range(hashers)]
    for benchmarks in csv.reader(input_file):
        for i, col in enumerate(benchmarks):
            hasher_averages[i].append(float(col))
    _, ax = plt.subplots()
    ax.set_xlabel('Data length (bytes)')
    ax.set_ylabel('Processor ticks')
    ax.set_title("Hash algorithms benchmark")
    for h_name, h_avgs in zip(hasher_names, hasher_averages):
        ax.plot(range(len_min, len_max, len_step), h_avgs, label=h_name)

    plt.legend()
    plt.gcf().set_size_inches(16, 9)
    plt.savefig(args[0] + '-graph.svg', dpi=199)


if __name__ == '__main__':
    main(argv[1:])
