# LaPRAS    
Linear processing of recursvely arranged subsets.   

This repositopry contains optimal (runtime and memory) algorithm to iterate over a power set.   

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
