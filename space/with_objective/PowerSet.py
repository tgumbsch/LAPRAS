
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

from Stoppable_Thread import StoppableThread


class MyLibrarySniffingClass(StoppableThread):
    def __init__(self, target_lib_call, arg):
        super(MyLibrarySniffingClass, self).__init__()
        self.target_function = target_lib_call
        self.arg = arg
        self.results = None

    def startup(self):
        # Overload the startup function
        # print "Calling the Target Library Function..."
        pass

    def cleanup(self):
        # Overload the cleanup function
        # print "Library Call Complete"
        pass

    def mainloop(self):
        # Start the library Call
        self.results = self.target_function(self.arg)

        # Kill the thread when complete
        self.stop()

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
        lib.vector_get.restype = c_double
        lib.vector_get.argtypes = [c_void_p, c_int]
        lib.vector_push_back.restype = None
        lib.vector_push_back.argtypes = [c_void_p, c_double]
        lib.powerset.argtypes = [c_void_p, c_char_p, c_double * n, c_int]
        lib.powerset.restype = c_int

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

        Vector = create_lib(len(seq))
        test = Vector()

        start = time.time()
        self.mem = test.powerset("LAPRAS", seq, int(np.sqrt(len(seq))))
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
        self.mem = test.powerset("BU", seq, int(np.sqrt(len(seq))))
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
        self.mem = test.powerset("Binary", seq, int(np.sqrt(len(seq))))
        self.duration = time.time() - start

        """ #Currently not working
        number = int(test[0])

        self.itemset = []
        for n in range(number):
            self.itemset.append(int(test[n + 1]))
        """

        del test


def Single_Run(test, Set):
    mythread = MyLibrarySniffingClass(test, Set)
    mythread.start()

    start_mem = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss
    delta_mem = 0
    max_memory = 0
    memory_usage_refresh = .005  # Seconds

    while(1):
        time.sleep(memory_usage_refresh)
        delta_mem = (resource.getrusage(resource.RUSAGE_SELF).ru_maxrss) - start_mem
        if delta_mem > max_memory:
            max_memory = delta_mem

        # Uncomment this line to see the memory usuage during run-time
        # print "Memory Usage During Call: %d MB" % (delta_mem / 1000000.0)

        # Check to see if the library call is complete
        if mythread.isShutdown():
            break

    return max_memory


def Test(trials, runs, test, name):
    FullMem = []
    for t in trials:
        Set = np.random.randn(t**2)
        memory = []
        for r in range(runs):
            mem = Single_Run(test, Set)
            memory.append(mem)
        FullMem.append(memory)
    print FullMem
    np.save(name + str(trials) + str(runs) + '.npy', np.asarray(FullMem))


if __name__ == "__main__":
    runs = 3
    trials = range(6, 28, 2)
    #trials = [5, 10, 15, 20, 25, 30]
    names = ['Binary', 'BottomUp', 'LaPRAS']
    txtfile = ['PW.txt', 'BU.txt', 'LP.txt']

    from matplotlib import pyplot as plt
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')

    for n, m in zip(names, txtfile):
        with open(m) as f:
            content = f.readlines()
            content = [int(x.replace(',', '')) for x in content]
        print content
        plt.plot(trials, content, label=n)
    plt.legend(loc='best', fontsize=16)
    plt.xlabel('Set size', fontsize=16)
    plt.xticks(trials)
    plt.tick_params(axis='both', which='major', labelsize=12)
    plt.ylabel(r'Allocated bytes', fontsize=16)
    plt.title("Solving the ordered traveling-salesman", fontsize=16)
    plt.savefig('Memory_obj_raw.pdf')
    plt.semilogy()
    plt.savefig('Memory_obj_log.pdf')

    plt.close()

    for n, m in zip(names, txtfile):
        with open(m) as f:
            content = f.readlines()
            content = [int(x.replace(',', '')) for x in content]
        plt.plot(trials, [i / content[0] for i in content], label=n)
    plt.legend(loc='best', fontsize=16)
    plt.xlabel(r'Set size', fontsize=16)
    plt.ylabel(r'Normalized allocated bytes', fontsize=16)
    plt.semilogy()
    plt.xticks(trials)
    plt.tick_params(axis='both', which='major', labelsize=12)
    plt.title("Solving the ordered traveling-salesman", fontsize=16)
    plt.savefig('Memory_obj_norm.pdf')
