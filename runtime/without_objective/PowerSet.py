
"""
To compile it and run the test, enter:
g++ -std=c++14 -c -fPIC _main.cpp -o MC.o
g++ -shared -Wl,-install_name,MC.so -o MC.so MC.o
python FracGrad.py
"""


import time
import numpy as np
import gc
from matplotlib import pyplot as plt
from ctypes import *

# A class for a C++ vector with a itemset function in Python


def create_lib(n):
    class Vector(object):
        lib = cdll.LoadLibrary('MC.so')  # class level loading lib
        lib.new_vector.restype = c_void_p
        lib.new_vector.argtypes = []
        lib.delete_vector.restype = None
        lib.delete_vector.argtypes = [c_void_p]
        lib.vector_size.restype = c_int
        lib.vector_size.argtypes = [c_void_p]
        lib.vector_get.restype = c_int
        lib.vector_get.argtypes = [c_void_p, c_int]
        lib.vector_push_back.restype = None
        lib.vector_push_back.argtypes = [c_void_p, c_int]
        lib.powerset.argtypes = [c_void_p, c_char_p, c_int * n, c_int]
        lib.powerset.restype = c_double

        def __init__(self):
            self.vector = Vector.lib.new_vector()  # pointer to new vector

        def __del__(self):  # when reference count hits 0 in Python,
            if Vector:
                Vector.lib.delete_vector(self.vector)  # call C++ vector destructor

        def __len__(self):
            return Vector.lib.vector_size(self.vector)

        def __getitem__(self, i):  # access elements in vector at index
            if 0 <= i < len(self):
                return Vector.lib.vector_get(self.vector, c_int(i))
            raise IndexError('Vector index out of range')

        def __repr__(self):
            return '[{}]'.format(', '.join(str(self[i]) for i in range(len(self))))

        def push(self, j):  # push calls vector's push_back
            Vector.lib.vector_push_back(self.vector, c_int(j))

        def powerset(self, filename, seq):  # foo in Python calls foo in C++
            arr = (c_int * len(seq))(*seq)
            return Vector.lib.powerset(self.vector, c_char_p(filename), arr, c_int(len(seq)))

    return Vector


class LAPRAS:

    def __init__(self, seq):
        gc.collect()

        Vector = create_lib(len(seq))
        test = Vector()

        start = time.time()
        self.time = test.powerset("LAPRAS", seq)
        self.duration = time.time() - start

        """ #Currently not working
        number = int(test[0])

        self.itemset = []
        for n in range(number):
            self.itemset.append(int(test[n + 1]))
        """

        del test


class BottomUp:

    def __init__(self, seq):
        gc.collect()

        Vector = create_lib(len(seq))
        test = Vector()

        start = time.time()
        self.time = test.powerset("BU", seq)
        self.duration = time.time() - start

        """ #Currently not working
        number = int(test[0])

        self.itemset = []
        for n in range(number):
            self.itemset.append(int(test[n + 1]))
        """

        del test


class Binary:

    def __init__(self, seq):
        gc.collect()

        Vector = create_lib(len(seq))
        test = Vector()

        start = time.time()
        self.time = test.powerset("Binary", seq)
        self.duration = time.time() - start

        """ #Currently not working
        number = int(test[0])

        self.itemset = []
        for n in range(number):
            self.itemset.append(int(test[n + 1]))
        """

        del test


def Test(trials, runs, test, name):
    Runtime = []
    for t in trials:
        Set = range(t)
        time = []
        for r in range(runs):
            single_run = test(Set)
            time.append(single_run.time)
        Runtime.append(time)
    np.save(name + str(trials) + str(runs) + '.npy', np.asarray(Runtime))


if __name__ == "__main__":
    runs = 3
    trials = range(8, 26, 2)
    #trials = [5,10,15,20,25]
    names = ['Binary', 'BottomUp', 'LaPRAS']
    methods = [Binary, BottomUp, LAPRAS]

    from matplotlib import pyplot as plt
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')

    for n, m in zip(names, methods):
        Test(trials, runs, m, n)

    for n, m in zip(names, methods):
        Runtime = np.load(n + str(trials) + str(runs) + '.npy')
        print np.mean(Runtime, axis=1)
        plt.errorbar(trials, np.mean(Runtime, axis=1), yerr=np.std(Runtime, axis=1), label=n)
    plt.legend(loc='best', fontsize=16)
    plt.xlabel('Set size', fontsize=16)
    plt.ylabel(r'Runtime in $s$', fontsize=16)
    plt.xticks(trials)
    plt.tick_params(axis='both', which='major', labelsize=12)
    plt.title("Iteration over power set", fontsize=16)
    plt.savefig('Runtime_plain_raw.pdf')
    plt.semilogy()
    plt.savefig('Runtime_plain_log.pdf')

    plt.close()

    for n, m in zip(names, methods):
        Runtime = np.load(n + str(trials) + str(runs) + '.npy')
        plt.plot(trials, np.mean(Runtime, axis=1) / np.mean(Runtime, axis=1)[0], label=n)
    plt.legend(loc='best', fontsize=16)
    plt.xlabel(r'Set size', fontsize=16)
    plt.ylabel(r'Normalized runtime', fontsize=16)
    plt.xticks(trials)
    plt.tick_params(axis='both', which='major', labelsize=12)
    plt.semilogy()
    plt.title("Iteration over power set", fontsize=16)
    plt.savefig('Runtime_plain_norm.pdf')
