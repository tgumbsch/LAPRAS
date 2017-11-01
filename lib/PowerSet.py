
"""
To compile it and run the test, enter:
g++ -std=c++14 -c -fPIC ./lib/_main.cpp -o ./lib/LAPRAS.o
g++ -shared -Wl,-install_name,MC.so -o ./lib/LAPRAS.so ./lib/LAPRAS.o
python ./lib/PowerSet.py
"""


import time
import numpy as np
import gc
from matplotlib import pyplot as plt
from ctypes import *

# A class for a C++ vector with a itemset function in Python


def create_lib(n):
    class Vector(object):
        lib = cdll.LoadLibrary('./lib/LAPRAS.so')  # class level loading lib
        lib.new_vector.restype = c_void_p
        lib.new_vector.argtypes = []
        lib.delete_vector.restype = None
        lib.delete_vector.argtypes = [c_void_p]
        lib.vector_size.restype = c_int
        lib.vector_size.argtypes = [c_void_p]
        lib.vector_get.restype = c_double
        lib.vector_get.argtypes = [c_void_p, c_int]
        lib.vector_push_back.restype = None
        lib.vector_push_back.argtypes = [c_void_p, c_double]
        lib.powerset.argtypes = [c_void_p, c_char_p, c_double * n, c_int]
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
            Vector.lib.vector_push_back(self.vector, c_double(j))

        def powerset(self, filename, seq, length):  # foo in Python calls foo in C++
            arr = (c_double * len(seq))(*seq)
            return Vector.lib.powerset(self.vector, c_char_p(filename), arr, c_int(length))

    return Vector


class LAPRAS:

    def __init__(self, seq):
        gc.collect()
        length = len(seq)
        Vector = create_lib(length)
        test = Vector()

        start = time.time()
        self.time = test.powerset("LAPRAS", seq, int(np.sqrt(len(seq))))
        self.duration = time.time() - start
        #no = int(test[0])
        #self.items = []
        # for num in range(no):
        #    self.items.append(test[1 + num])

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

        length = len(seq)
        Vector = create_lib(len(seq))
        test = Vector()

        start = time.time()
        self.time = test.powerset("BU", seq, int(np.sqrt(len(seq))))
        self.duration = time.time() - start
        #no = int(test[0])
        #self.items = []
        # for num in range(no):
        #    self.items.append(test[1 + num])
        """ #Currently not working
        number = int(test[0])

        self.itemset = []
        for n in range(number):
            self.itemset.append(int(test[n + 1]))
        """

        del test


class _Binary:

    def __init__(self, seq):
        gc.collect()

        length = len(seq)
        Vector = create_lib(len(seq))
        test = Vector()

        start = time.time()
        self.time = test.powerset("SlowBinary", seq, int(np.sqrt(len(seq))))
        self.duration = time.time() - start
        #no = int(test[0])
        #self.items = []
        # for num in range(no):
        #    self.items.append(test[1 + num])

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

        length = len(seq)
        Vector = create_lib(len(seq))
        test = Vector()

        start = time.time()
        self.time = test.powerset("Binary", seq, int(np.sqrt(len(seq))))
        self.duration = time.time() - start
        #no = int(test[0])
        #self.items = []
        # for num in range(no):
        #    self.items.append(test[1 + num])

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
        Set = np.random.randn(t**2)
        time = []
        for r in range(runs):
            # print(test)
            single_run = test(Set)
            time.append(single_run.time)
        Runtime.append(time)
    np.save('./lib/' + name + str(trials) + str(runs) + '.npy', np.asarray(Runtime))


if __name__ == "__main__":
    runs = 3
    trials = range(6, 30, 2)
    #trials = [5, 10, 15, 20, 25, 30]
    names = ['FastBinary', 'Binary', 'BottomUp', 'LaPRAS']
    methods = [Binary, _Binary, BottomUp, LAPRAS]

    color = ['lightblue', 'darkblue', 'red', 'green']

    from matplotlib import pyplot as plt
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')
    plt.tick_params(labelsize=16)

    for n, m in zip(names, methods):
        Test(trials, runs, m, n)
    i = 0
    for n, m in zip(names, methods):
        Runtime = np.load('./lib/' + n + str(trials) + str(runs) + '.npy')
        print(n, np.mean(Runtime, axis=1))
        plt.errorbar(trials, np.mean(Runtime, axis=1), yerr=np.std(Runtime, axis=1), color=color[i], linewidth=3, label=n)
        i = i + 1
    plt.legend(loc='best', fontsize=16)
    plt.xlabel('Set size', fontsize=16)
    plt.xticks(trials)
    plt.xlim((trials[0], trials[-1]))
    plt.tick_params(axis='both', which='major', labelsize=12)
    plt.ylabel(r'Runtime in $s$', fontsize=16)
    #plt.title("Solving the ordered traveling-salesman", fontsize=16)
    plt.savefig('Runtime_obj_raw.pdf')

    plt.close()
    i = 0
    for n, m in zip(names, methods):
        Runtime = np.load('./lib/' + n + str(trials) + str(runs) + '.npy')
        plt.plot(trials, np.mean(Runtime, axis=1) / np.asarray([np.mean(Runtime, axis=1)[0] * np.power(2, k) for k in trials]), color=color[i], linewidth=3, label=n)
        i = i + 1
    plt.legend(loc='best', fontsize=16)
    plt.xlabel(r'Set size', fontsize=16)
    plt.ylabel(r'Normalized runtime', fontsize=16)
    # plt.semilogy()
    plt.xticks(trials)
    plt.xlim((trials[0], trials[-1]))
    plt.tick_params(axis='both', which='major', labelsize=12)
    #plt.title("Solving the ordered traveling-salesman", fontsize=16)
    plt.savefig('Runtime_obj_norm.pdf')
    plt.semilogy()
    plt.savefig('Runtime_log_norm.pdf')
