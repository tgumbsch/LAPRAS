# LaPRAS    
Linear processing of recursvely arranged subsets.   

Objective: Given is a generalized adjecency matrix *A* of a graph. Generalized means that there are no restrictions on the form of *A*. The objective is to find the sequence of nodes that maximize the length of the path bewteen the nodes when visiting them is ascending order.

Method: `Binary` and `LAPRAS` are optimal (runime and memory) algorithms to solve that problem exactly. `Binary` is an exhaustive enumeration of the power set using efficient update formulae as described by _amortized analysis_. `LAPRAS` is a recursive version of the algorithm which is numerically more stable and a factor of 2 faster.    

## Quickstart  

To recover the runtime plot, run `example.sh`.   

## Use the Python function  

Copy `lib` to your project directory. To compile the C++ core, run.  

```
g++ -std=c++14 -c -fPIC ./lib/_main.cpp -o ./lib/LAPRAS.o
g++ -shared -Wl,-install_name,MC.so -o ./lib/LAPRAS.so ./lib/LAPRAS.o
```

To create the linked files, `-install_name` needs to be replaced by `-soname` for some OS.   

Then, in your Python code, use the module as:

```
import lib.PowerSet as P
itemset_index = P.LAPRAS(D.flatten())
```


where `D` is the distance matrix between all pairs of observations.   
