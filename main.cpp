#include <vector>
#include <iostream>
#include <numeric>
#include "LAPRAS.cpp"
#include "PowerSet.cpp"
#include <ctime>

int main(){
    std::clock_t start;
    std::clock_t stop;
    int it = 1;

    for(int i = 15; i<16; i++){

        std::vector<int> Set(i);
        std::iota(Set.begin(), Set.end(),0);
        /*
        start = std::clock();
        for(int j = 0; j< it;j++){
        LAPRAS LP;
        LP.Init(Set);
        LP.Fit(Set,0);
        }
        stop = std::clock();
        std::cout << i << " LAPRAS: " << ( stop - start ) / (double) CLOCKS_PER_SEC << std::endl;

        Set.resize(i);
        std::iota(Set.begin(), Set.end(),0);
        std::cout << Set.size();
        */
        start = std::clock();
        BottomUp BU;
        BU.Init(Set);
        BU.Fit(Set);
        stop = std::clock();
        std::cout << i << " Naive: " << ( stop - start ) / (double) CLOCKS_PER_SEC << std::endl;


        Set.resize(i);
        std::iota(Set.begin(), Set.end(),0);

        start = std::clock();
        for(int j = 0; j< it;j++){
        PowerSet(Set,Set.size());
        }
        stop = std::clock();
        std::cout << i << " Binary: " << ( stop - start ) / (double) CLOCKS_PER_SEC << std::endl;
    }
}


/*
Ten runs:
10 LAPRAS: 0.002606
10 Binary: 0.000903
11 LAPRAS: 0.005217
11 Binary: 0.001899
12 LAPRAS: 0.010431
12 Binary: 0.003917
13 LAPRAS: 0.021504
13 Binary: 0.008812
14 LAPRAS: 0.042922
14 Binary: 0.017435
15 LAPRAS: 0.086528
15 Binary: 0.035053
16 LAPRAS: 0.173284
16 Binary: 0.073292
17 LAPRAS: 0.341126
17 Binary: 0.149797
18 LAPRAS: 0.692259
18 Binary: 0.307259
19 LAPRAS: 1.39625
19 Binary: 0.630537
20 LAPRAS: 2.81477
20 Binary: 1.30455


*/
