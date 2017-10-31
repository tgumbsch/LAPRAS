
"""
To compile it and run the test, enter:
g++ -std=c++14 -c -fPIC _main.cpp -o MC.o
g++ -shared -Wl,-install_name,MC.so -o MC.so MC.o
"""

import resource
import sys
import time
import numpy as np
import gc
from matplotlib import pyplot as plt
from ctypes import *


if __name__ == "__main__":
    runs = 3
    trials = range(6, 28, 2)
    #trials = [5, 10, 15, 20, 25, 30]
    color = ['darkblue', 'lightblue', 'green', 'red']
    names = ['Binary', 'FastBinary', 'LaPRAS']#, 'BottomUp']  # , 'LaPRAS']
    txtfile = ['SPW.txt', 'PW.txt', 'LP.txt']#, 'BU.txt']  # , 'LP.txt']
    #names = ['Binary', 'LaPRAS']
    #txtfile = ['PW.txt', 'LP.txt']

    from matplotlib import pyplot as plt
    # plt.style.use('presentation')
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')
    plt.tick_params(labelsize=16)

    i = 0
    for n, m in zip(names, txtfile):
        with open(m) as f:
            content = f.readlines()
            content = [int(x.replace(',', '')) for x in content]
        if n == 'BottomUp':
            trials_ = trials[:5]
        else:
            trials_ = trials
        content = content[:len(trials_)]
        plt.plot(trials_, content, color=color[i], linewidth=3, label=n)
        i = i + 1
    plt.legend(loc='best', fontsize=16)
    plt.xlabel('Set size', fontsize=16)
    plt.xticks(trials)
    plt.xlim((trials[0], trials[-1]))
    plt.tick_params(axis='both', which='major', labelsize=12)
    plt.ylabel(r'Total allocated bytes', fontsize=16)
    #plt.title("Iteration over power set ", fontsize=16)
    plt.savefig('Memory_plain_raw.pdf')
    plt.semilogy()
    plt.savefig('Memory_plain_log.pdf')

    plt.close()
    i = 0
    for n, m in zip(names, txtfile):
        with open(m) as f:
            content = f.readlines()
            content = [int(x.replace(',', '')) for x in content]
        if n == 'BottomUp':
            trials_ = trials[:5]
        else:
            trials_ = trials
        content = content[:len(trials_)]
        plt.plot(trials_, [float(k) / content[0] for k in content], color=color[i], linewidth=3, label=n)
        i = i + 1
    plt.legend(loc='best', fontsize=16)
    plt.xlabel(r'Set size', fontsize=16)
    plt.ylabel(r'Allocated bytes, normalized to $n='+str(trials[0])+r'$', fontsize=16)
    # plt.semilogy()
    plt.xticks(trials)
    plt.xlim((trials[0], trials[-1]))
    plt.tick_params(axis='both', which='major', labelsize=12)
    #plt.title("Iteration over power set ", fontsize=16)
    plt.savefig('Memory_plain_norm.pdf')
