#!/usr/bin/python3.8

from sys import argv
import csv
import matplotlib.pyplot as plt
import numpy as np


def main(args: [str]):
    if len(args) < 2:
        print('Arguments: <input_filename> <mode>')
        return

    input_filename: str = args[0]
    input_file = open(input_filename, 'r')

    algo_names = input_file.readline().split(',')[1:]
    algos = len(algo_names)
    algo_values: [[float]] = [[] for i in range(algos)]
    labels: [str] = []
    for benchmark in csv.reader(input_file):
        benchmark_filename = benchmark[0]
        labels.append(benchmark_filename)
        for algo_i, col in enumerate(benchmark[1:]):
            algo_values[algo_i].append(float(col))

    x = np.arange(len(labels))
    width = 2.0

    fig, ax = plt.subplots()
    rects = [ax.bar(x - width / len(labels) * i,
                    algo_values[i],
                    width / len(labels),
                    label=algo_names[i]) for i in range(algos)]

    ax.set_ylabel(args[1])
    ax.set_title('Compression algorithms benchmark')
    ax.set_xticks(x)
    ax.set_xticklabels(labels)
    ax.legend()
    ax.set_yscale('log')

    for rect in rects:
        ax.bar_label(rect, padding=3)

    fig.tight_layout()

    plt.show()


if __name__ == '__main__':
    main(argv[1:])
